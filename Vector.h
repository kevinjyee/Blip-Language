
// Vector.h -- interface description for Vector ADT

#ifndef _Vector_h
#define _Vector_h 1

#include <stdint.h>
#include <assert.h>

struct Vector {
private:
	char** data;
	uint32_t capacity;
	uint32_t length;
public:

	Vector(void) {
		data = new char*[1];
		length = 0;
		capacity = 1;
	}

	Vector(const Vector& that) { copy(that); }

	Vector(uint32_t len) {
		this->length = len;
		this->capacity = len;
		if (this->capacity == 0) {
			this->capacity = 1;
		}
		this->data = new char*[capacity];
	}

	~Vector(void) { delete[] data; }

	char* operator[](uint32_t k) {
		assert(k < this->length);

		return this->data[k];
	}

	// append x to the end
	void push_back(char* x) {
		if (this->capacity == this->length) {
			this->capacity = this->capacity * 2;
			char** new_data = new char*[capacity];
			for (uint32_t k = 0; k < this->length; k += 1) {
				new_data[k] = this->data[k];
			}
			delete[] this->data;
			this->data = new_data;
		}

		this->data[this->length] = x;
		this->length += 1;
	}

	uint32_t size(void) { return length; } // return the number of elements in the vector

private:


	/* copy(char*) assumes that ptr has been allocated and holds sufficient capacity for src */
	void copy( char** src) {
		int k = length;
		while (k >= 0) {
			(data)[k] = src[k];
			k -= 1;
		}
	}

	/* copy(String&) is my "real" copy constructor. I always name this function "copy" and its purpose
	 * is to construct a "deep copy" (i.e., an independent object that shares no pointers with the original object) */
	void copy(const Vector& that) {
		length = that.length;
		capacity = that.capacity;
		data = (char**) malloc(length + 1);
		copy(that.data);
	}
};





#endif /* VECTOR_H_ */
