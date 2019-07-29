#import re
#from sys import stdin

#r_func = re.compile(r'(\w+) (\w+) *[=;]')
#r_struct = re.compile(r'struct (\w*)\W*\{([^{}]*)\}', re.M | re.S)
#r_enum = re.compile(r'enum (\w*)\W*\{([^{}]*)\}', re.M | re.S)

#class_def = stdin.read()
#class_def_no_enum = r_enum.sub("", class_def)
#for name, code in r_struct.findall(class_def_no_enum):
    #print( name )
    #print( r_func.findall(code) )
##print( class_def_no_enum)
##print( r_struct.findall(class_def) )

from argparse import ArgumentParser
import clang.cindex
from os import path
clang.cindex.Config.set_library_file('libclang-8.so')

parser = ArgumentParser()
parser.add_argument('header')
parser.add_argument('hpp_output', nargs='?')
parser.add_argument('cpp_output', nargs='?')
args = parser.parse_args()

from sys import stdout, stderr
if args.hpp_output is None:
    hpp_file = stderr
else:
    hpp_file = open(args.hpp_output, 'w')
if args.cpp_output is None:
    cpp_file = stdout
else:
    cpp_file = open(args.cpp_output, 'w')

CPP_HEADER = """#include "%s"
#include "%s"

void pickle(std::ostream & s, const std::string & o) {
    uint32_t n = o.size();
    s.write((const char*)&n, sizeof(n));
    s.write(o.data(), n);
}
void unpickle(std::istream & s, std::string * o) {
    uint32_t n;
    s.read((char*)&n, sizeof(n));
    o->resize(n);
    s.read(&(*o)[0], n);
}
""" % (path.basename(args.hpp_output if args.hpp_output is not None else ""), path.basename(args.header))

HPP_HEADER = """#pragma once
#include <cctype>
#include <istream>
#include <memory>
#include <ostream>
#include <pybind11/pybind11.h>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

template<typename T>
void pickle(std::ostream & s, const T & o) {
    static_assert(std::is_fundamental<T>::value || std::is_enum<T>::value, "Can only template pickle fundamental values");
    s.write((char*)&o, sizeof(o));
}
template<typename T>
void pickle(std::ostream & s, const std::vector<T> & o) {
    uint32_t n = o.size();
    s.write((const char*)&n, sizeof(n));
    for(uint32_t i = 0; i < n; i++)
        pickle(s, o[i]);
}
void pickle(std::ostream & s, const std::string & o);
template<typename T>
void unpickle(std::istream & s, T * o) {
    static_assert(std::is_fundamental<T>::value || std::is_enum<T>::value, "Can only template unpickle fundamental values");
    s.read((char*)o, sizeof(T));
}
template<typename T>
void unpickle(std::istream & s, std::vector<T> * o) {
    uint32_t n;
    s.read((char*)&n, sizeof(n));
    o->resize(n);
    for(uint32_t i = 0; i < n; i++)
        unpickle(s, &(*o)[i]);
}
void unpickle(std::istream & s, std::string * o);

template<typename T>
void add_pickle(pybind11::class_<T, std::shared_ptr<T> > & c) {
	c.def(pybind11::pickle(
		[](const T & o){
			std::ostringstream s;
			pickle(s, o);
			std::string data = s.str();
			return pybind11::make_tuple(pybind11::handle(PyBytes_FromStringAndSize(&data[0], data.size())));
		},[](pybind11::tuple state){
			if (len(state) != 1 || !PyBytes_Check(pybind11::object(state[0]).ptr())) {
				PyErr_SetObject(PyExc_ValueError, pybind11::str("Unable to unpickle {}").format(state).ptr());
				throw pybind11::error_already_set();
			}
			auto r = std::make_shared<T>();
			std::istringstream s(std::string(PyBytes_AsString(state[0].ptr()), PyBytes_Size(state[0].ptr())));
			unpickle(s, r.get());
			return r;
		}));
}
"""

print(HPP_HEADER, file=hpp_file)
print(CPP_HEADER, file=cpp_file)

def find_decl(node):
    fields = [c for c in node.get_children() if c.kind == c.kind.FIELD_DECL]
    print('struct %s;'%node.displayname, file=hpp_file)
    print('void pickle(std::ostream & s, const %s & o);'%node.displayname, file=hpp_file)
    print('void unpickle(std::istream & s, %s * o);'%node.displayname, file=hpp_file)
    
    print('void pickle(std::ostream & s, const %s & o) {'%node.displayname, file=cpp_file)
    for c in fields:
        print('    pickle(s, o.%s);'%c.displayname, file=cpp_file)
    print('}', file=cpp_file)
    print('void unpickle(std::istream & s, %s * o) {'%node.displayname, file=cpp_file)
    for c in fields:
        print('    unpickle(s, &o->%s);'%c.displayname, file=cpp_file)
    print('}', file=cpp_file)
    

def find_classes(node):
    for c in node.get_children():
        if c.kind == c.kind.STRUCT_DECL and c.location.file.name == args.header:
            find_decl(c)
        #find_classes(c)

index = clang.cindex.Index.create()
tu = index.parse(args.header, ['-x', 'cpp-output', '-std=c++11', '-D__CODE_GENERATOR__'])
find_classes(tu.cursor)
