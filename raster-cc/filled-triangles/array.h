#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

template<typename T>
struct Array {
	int64_t len, cap;
	T* ptr;

	T& operator[] (size_t idx) {
		return ptr[idx];
	};

	const T& operator[] (size_t idx) const {
		return ptr[idx];
	}
};

template<typename T>
void array_create(Array<T> *a, int64_t cap) {
	assert(cap >= 0);
	assert(a->ptr == nullptr);
	a->ptr = (T*)calloc(cap, sizeof(T));
	a->cap = cap;
	a->len = 0;
}

template<typename T>
void array_delete(Array<T> *a) {
	assert(a->ptr);
	if (a->ptr != nullptr) {
		free(a->ptr);
		a->ptr = nullptr;
	}
	a->cap = 0;
	a->len = 0;
}

template<typename T>
void array_resize(Array<T> *a, int64_t new_cap) {
	T* n = (T*)realloc(a->ptr, sizeof(T)*new_cap);
	if (n == nullptr) {
		n = (T*)calloc(new_cap, sizeof(T));
		assert(n);
		memcpy(n, a->ptr, a->cap);
		free(a->ptr);
		a->ptr = nullptr;
	}
	a->cap = new_cap;
	a->ptr = n;
}

template<typename T>
Array<T> array_concatenate(Array<T> first, Array<T> second) {
	Array<T> n = {0};
	size_t elem_size = sizeof(T);
	n.cap = first.len + second.len;
	n.len = n.cap;
	n.ptr = (T*)calloc(n.cap, elem_size);
	memcpy(n.ptr, first.ptr, first.len*elem_size);
	memcpy(n.ptr + first.len, second.ptr, second.len*elem_size);
	return n;
}

template<typename T>
void array_append(Array<T> *a, T item) {
	if (a->len >= a->cap) {
		array_resize(a, a->cap*2);
	}
	a->ptr[a->len++] = item;
}
