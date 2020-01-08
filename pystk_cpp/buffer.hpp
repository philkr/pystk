#pragma once

class BasicPBO {
    unsigned int buffer_id_;
    int width_, height_, format_, type_, size_;
    BasicPBO(BasicPBO&) = delete;
    BasicPBO& operator=(BasicPBO&) = delete;
public:
    BasicPBO(int width, int height, int format, int type);
    void read(unsigned int texture);
    void write(void * mem);
    ~BasicPBO();
};
