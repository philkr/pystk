#pragma once
#include <pybind11/pybind11.h>

namespace pybind11 {
class readonly_memoryview : public pybind11::object {
public:
	template<typename T>
    explicit readonly_memoryview(const T * v, const std::vector<Py_ssize_t> & shape) {
		// Compute the stride
		static std::vector<Py_ssize_t> stride;
		stride.resize( shape.size() );
		Py_ssize_t itemsize = sizeof(T), s = 1;
		for(int i=stride.size()-1; i>=0; i--) {
			stride[i] = s * itemsize;
			s *= shape[i];
		}
		static std::string fmt;
		fmt = pybind11::format_descriptor<T>::format();
		
		static Py_buffer buf { };
		buf.buf = const_cast<T *>(v);
		buf.itemsize = itemsize;
		buf.format = const_cast<char *>(fmt.c_str());
		buf.ndim = (int) shape.size();
		buf.len = s;
		buf.strides = stride.data();
		buf.shape = const_cast<Py_ssize_t *>(shape.data());
		buf.suboffsets = nullptr;
		buf.readonly = true;
		buf.internal = nullptr;

		m_ptr = PyMemoryView_FromBuffer(&buf);
		if (!m_ptr)
			pybind11::pybind11_fail("Unable to create memoryview from buffer descriptor");
    }

    PYBIND11_OBJECT_CVT(readonly_memoryview, object, PyMemoryView_Check, PyMemoryView_FromObject)
};
typedef readonly_memoryview ro_view;
}
