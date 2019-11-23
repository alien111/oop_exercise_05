#ifndef D_CONTAINERS_DOBRIYARRAY_H_
#define D_CONTAINERS_DOBRIYARRAY_H_ 1

#include <iterator>
#include <memory>
#include <cstddef>
#include "vertex.h"
#include "rectangle.h"

namespace containers { 

template<class T>
class DobriyArray {

public:
	DobriyArray();
	DobriyArray(int sz);

	struct forward_iterator {
		using value_type = T;
    	using reference = T&;
    	using pointer = T*;
    	using difference_type = ptrdiff_t;
    	using iterator_category = std::forward_iterator_tag;

    	forward_iterator(T *ptr);
    	forward_iterator() = default;
    	T& operator*();

    	forward_iterator& operator++();

    	bool operator== (const forward_iterator& o) const;
    	bool operator!= (const forward_iterator& o) const;

    private:
    	T *p;
    	friend DobriyArray;

	};

	forward_iterator begin();
	forward_iterator end();

	T& operator[](int index);
	void reSize(int newSize);
	void push_back(T object);
	void addOnOutOfRange(int position, T object);
	int getSize();
	int getUsed();
	forward_iterator insert(forward_iterator it, T object);
	void erase(forward_iterator it);

private:

	std::unique_ptr<T[]> data;
	int size;
	int used;

};

template<class T>
DobriyArray<T>::DobriyArray() {
	
	data = nullptr;
	size = 0;
	used = 0;

}

template<class T>
void DobriyArray<T>::reSize(int newSize) {
	if (size == newSize) return;
	std::unique_ptr<T[]> resizing = std::unique_ptr<T[]>(new T[newSize]);

	for (int i = 0; i < std::min(size, newSize); i++) {
		resizing[i] = data[i];
	}
	size = newSize;
	data = std::move(resizing);
}

template<class T>
DobriyArray<T>::DobriyArray(int sz) {

	data = std::unique_ptr<T[]>(new T[sz]);
	size = sz;
	used = 0;

}

template<class T>
void DobriyArray<T>::push_back(T object) {

	if (used >= size) reSize(size++);
	data[used] = object;
	used++;

}

template<class T>
void DobriyArray<T>::addOnOutOfRange(int position, T object) {

	reSize(position + 1);

	data[position] = object;
	used++;

}

template<class T>
DobriyArray<T>::forward_iterator::forward_iterator(T *ptr) {
	p = ptr;
}

template<class T>
T& DobriyArray<T>::forward_iterator::operator*() {
	return *p;
}

template<class T>
typename DobriyArray<T>::forward_iterator& DobriyArray<T>::forward_iterator::operator++() {
	++p;
	return *this; 
}

template<class T>
bool DobriyArray<T>::forward_iterator::operator== (const forward_iterator& o) const {
	return p == o.p;
}


template<class T>
bool DobriyArray<T>::forward_iterator::operator!= (const forward_iterator& o) const {
	return p != o.p;
}

template<class T>
typename DobriyArray<T>::forward_iterator DobriyArray<T>::begin() {
	return &data[0];
}

template<class T>
typename DobriyArray<T>::forward_iterator DobriyArray<T>::end() {
	return &data[size];
}

template<class T>
T& DobriyArray<T>::operator[](int index) {
	if (index > size - 1) throw std::logic_error("index is out of range!\n");
	T& result = data[index];
	return result;
}

template<class T>
int DobriyArray<T>::getSize() {
	return size;
}

template<class T>
int DobriyArray<T>::getUsed() {
	return used;
}

template<class T>
typename DobriyArray<T>::forward_iterator DobriyArray<T>::insert(forward_iterator it, T object) {
	for (int i = 0; i < size; i++) {
		if (it == &data[i]) {
			if (used == size) reSize(size + 1);
			for (int j = size - 1; j > i; j--) {
				data[j] = data[j - 1];
			}
			data[i] = object;
			used++;
			return &data[i];
		}
	}
	throw std::logic_error("Place doesn't exist!\n");
}

template<class T>
void DobriyArray<T>::erase(forward_iterator it) {
	for (int i = 0; i < size; i++) {
		if (it == &data[i]) {
			for (int j = i; j < size - 1; j++) {
				data[j] = data[j + 1];
			}
			reSize(size - 1);
			used--;
			return;
		}
	}

	throw std::logic_error("Place doesn't exist!\n");
} 

}


#endif