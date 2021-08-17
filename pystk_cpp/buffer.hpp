#pragma once
#include <pybind11/numpy.h>
namespace py = pybind11;

#ifndef SERVER_ONLY
class BasicPBO {
protected:
    unsigned int buffer_id_;
    int width_, height_, format_, type_, size_;
    BasicPBO(BasicPBO&) = delete;
    BasicPBO& operator=(BasicPBO&) = delete;
public:
    BasicPBO(int width, int height, int format, int type);
    virtual void read(unsigned int texture);
    virtual void write(void * mem);
    virtual ~BasicPBO();
};

class NumpyPBO: public BasicPBO {
protected:
    bool need_update_;
    py::array data_;
public:
    NumpyPBO(int width, int height, int format, int type);
    virtual void read(unsigned int texture);
    virtual py::array get();
};

#endif  // SERVER_ONLY