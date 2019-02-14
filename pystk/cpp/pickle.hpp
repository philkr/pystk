#pragma once
#include <cctype>
#include <istream>
#include <memory>
#include <ostream>
#include <pybind11/pybind11.h>
#include <string>
#include <sstream>
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

struct PySTKGraphicsConfig;
void pickle(std::ostream & s, const PySTKGraphicsConfig & o);
void unpickle(std::istream & s, PySTKGraphicsConfig * o);
struct PySTKPlayerConfig;
void pickle(std::ostream & s, const PySTKPlayerConfig & o);
void unpickle(std::istream & s, PySTKPlayerConfig * o);
struct PySTKRaceConfig;
void pickle(std::ostream & s, const PySTKRaceConfig & o);
void unpickle(std::istream & s, PySTKRaceConfig * o);
struct PySTKRenderData;
void pickle(std::ostream & s, const PySTKRenderData & o);
void unpickle(std::istream & s, PySTKRenderData * o);
struct PySTKAction;
void pickle(std::ostream & s, const PySTKAction & o);
void unpickle(std::istream & s, PySTKAction * o);
