#pragma once
#include <cstdlib>

void _yflip(void * data, size_t height, size_t row_width);

template<typename T> void yflip(T* data, size_t height, size_t width, size_t channels=1) {
	_yflip(static_cast<void*>(data), height, width*channels*sizeof(T));
}
