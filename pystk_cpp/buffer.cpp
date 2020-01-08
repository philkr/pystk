#include "buffer.hpp"
#include "graphics/gl_headers.hpp"
#include "utils/log.hpp"

int n_channel(int format) {
    switch(format) {
    case GL_DEPTH_COMPONENT: return 1;
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
void BasicPBO::read() {
    glBindBuffer(GL_PIXEL_PACK_BUFFER, buffer_id_);
    glReadPixels(0, 0, width_, height_, format_, type_, 0);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
}
void BasicPBO::write(void * mem) {
    glBindBuffer(GL_PIXEL_PACK_BUFFER, buffer_id_);
    glGetBufferSubData(GL_PIXEL_PACK_BUFFER, 0, size_, mem);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
}

