#include "buffer.hpp"
#include "graphics/gl_headers.hpp"
#include "utils/log.hpp"
#include "util.hpp"

#ifndef SERVER_ONLY
int n_channel(int format) {
    switch(format) {
    case GL_DEPTH_COMPONENT: return 1;
    case GL_RED_INTEGER:
    case GL_RED:
    case GL_GREEN:
    case GL_BLUE: return 1;
    case GL_RGB:
    case GL_BGR: return 3;
    case GL_RGBA:
    case GL_BGRA: return 4;
    }
    Log::fatal("buffer", ("Unsupported OpenGL format "+std::to_string(format)+".\n").c_str());
    return 1;
}
int type_size(int format) {
    switch(format) {
    case GL_UNSIGNED_BYTE:
    case GL_BYTE: return 1;
    case GL_UNSIGNED_SHORT:
    case GL_SHORT: return 2;
    case GL_UNSIGNED_INT:
    case GL_INT: return 4;
    case GL_HALF_FLOAT: return 2;
    case GL_FLOAT: return 4;
    }
    Log::fatal("buffer", "Unsupported OpenGL type.\n");
    return 1;
}

BasicPBO::BasicPBO(int width, int height, int format, int type): width_(width), height_(height), format_(format), type_(type) {
    size_ = width*height*n_channel(format)*type_size(type);
    glGenBuffers(1, &buffer_id_);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, buffer_id_);
    glBufferData(GL_PIXEL_PACK_BUFFER, size_, NULL, GL_STREAM_COPY);
}
BasicPBO::~BasicPBO() {
    glDeleteBuffers(1, &buffer_id_);
}
void BasicPBO::read(GLuint texture) {
    glBindBuffer(GL_PIXEL_PACK_BUFFER, buffer_id_);
    if (GLEW_VERSION_4_5) {
        glGetTextureImage(texture, 0, format_, type_, size_, 0);
    } else {
        glBindTexture(GL_TEXTURE_2D, texture);
        glGetTexImage(GL_TEXTURE_2D, 0, format_, type_, 0);
    }
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
}
void BasicPBO::write(void * mem) {
    glBindBuffer(GL_PIXEL_PACK_BUFFER, buffer_id_);
    glGetBufferSubData(GL_PIXEL_PACK_BUFFER, 0, size_, mem);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
}



py::array make(py::array::ShapeContainer shape, int gl_type) {
    switch(gl_type) {
        case GL_UNSIGNED_BYTE:  return py::array_t<unsigned char, py::array::c_style>(shape);
        case GL_BYTE:           return py::array_t<signed char, py::array::c_style>(shape);
        case GL_UNSIGNED_SHORT: return py::array_t<unsigned short, py::array::c_style>(shape);
        case GL_SHORT:          return py::array_t<signed short, py::array::c_style>(shape);
        case GL_UNSIGNED_INT:   return py::array_t<unsigned int, py::array::c_style>(shape);
        case GL_INT:            return py::array_t<signed int, py::array::c_style>(shape);
        case GL_FLOAT:          return py::array_t<float, py::array::c_style>(shape);
    }
    Log::fatal("buffer", "Unsupported OpenGL type.\n");
    return py::array();
}

NumpyPBO::NumpyPBO(int width, int height, int format, int type): BasicPBO(width, height, format, type)
{
    py::array::ShapeContainer shape = {height, width};
    int c = n_channel(format);
    if (c > 1)
        shape->push_back(c);
    data_ = make(shape, type);
}

void NumpyPBO::read(unsigned int texture)
{
    BasicPBO::read(texture);
    need_update_ = true;
}

py::array NumpyPBO::get()
{
    if (need_update_) {
        // Copy data_ here to preveny any nasty surprises...
        data_ = make(py::array::ShapeContainer(data_.shape(), data_.shape() + data_.ndim()), type_);
        BasicPBO::write(data_.mutable_data());
        _yflip(data_.mutable_data(), data_.shape()[0], data_.strides()[0]);
    }
    return data_;
}

#endif  // SERVER_ONLY
