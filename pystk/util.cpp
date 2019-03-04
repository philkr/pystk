#include "util.hpp"
// #include <immintrin.h>
#include <cstdint>
#include <cstdio>
#include <algorithm>

// inline static size_t ls(void*v) { return *(size_t*)v; }
// inline static uint8_t lb(void*v) { return *(uint8_t*)v; }
// inline static void s(void*v, size_t x) { *(size_t*)v=x; }
// inline static void s(void*v, uint8_t x) { *(uint8_t*)v=x; }
// 
// static void swap(uint8_t * a, uint8_t * b, size_t n) {
// 	size_t i=0;
// #define SWAP(T, L, S) \
// 	for(; i+sizeof(T)<=n; i+=sizeof(T)) {\
// 		T t = L((float*)(a + i));\
// 		S((float*)(a + i), L((float*)(b + i)));\
// 		S((float*)(b + i), t);\
// 	}
// #ifdef __AVX512F__
// 	SWAP(__m512, _mm512_loadu_ps, _mm512_storeu_ps);
// #endif
// #ifdef __AVX__
// 	SWAP(__m256, _mm256_loadu_ps, _mm256_storeu_ps);
// #endif
// #ifdef __SSE__
// 	SWAP(__m128, _mm_loadu_ps, _mm_storeu_ps);
// #endif
// 	SWAP(size_t, ls, s);
// 	SWAP(uint8_t, lb, s);
// }

void _yflip(void * data, size_t height, size_t row_bytes) {
	uint8_t * D = static_cast<uint8_t*>(data);
	for( size_t i=0; 2*i+1<height; i++ )
// std::swap_ranges with -O3 is equally fast (or faster), -O2 is slow
		std::swap_ranges(D+i*row_bytes, D+(i+1)*row_bytes, D+(height-1-i)*row_bytes);
// 		swap(D+i*row_bytes, D+(height-1-i)*row_bytes, row_bytes);
}

