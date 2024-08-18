#include "Vector.h"
#include <iostream>

using namespace std;

Vector::Vector(const ValueType* rawArray, const size_t size, float coef) {
	_size = size;
	_multiplicativeCoef = coef;
	_capacity = size;
	_data = new ValueType[_capacity];
	for (int i = 0; i < size; i++) {
		_data[i] = rawArray[i];
	}
}

Vector::Vector(const Vector& other){
	_size = other._size;
	_multiplicativeCoef = other._multiplicativeCoef;
	_capacity = other._size;
	for (int i = 0; i < other._size; i++) {
		_data[i] = other._data[i];
	}
}

Vector& Vector::operator=(const Vector& other) {
	_size = other._size;
	_multiplicativeCoef = other._multiplicativeCoef;
	_capacity = other._capacity;
	for (int i = 0; i < other._size; i++) {
		_data[i] = other._data[i];
	}
	return *this;
}

void Vector::pushFront(const ValueType& value) {
	this->reserve(this->_size);
	for (int i = this->_size; i > 0; i--) {
		this->_data[i] = this->_data[i - 1];
	}
	this->_size += 1;
	this->_data[0] = value;
}

void Vector::printer() {
	for (int i = 0; i < this->_size; i++) {
		cout << this->_data[i] << " ";
	}
}

void Vector::pushBack(const ValueType& value) {
	this->reserve(this->_size);
	this->_data[this->_size] = value;
	this->_size += 1;
}

void Vector::popBack() {
	this->_size -= 1;
	this->_data[this->_size] = NULL;
	if (this->_size * 2 <= this->_capacity) {
		this->_data = (ValueType*)realloc(this->_data, this->_size*sizeof(ValueType));
		this->_capacity = this->_size;
	}
}

void Vector::popFront() {
	for (int i = 0; i < this->_size - 1; i++) {
		this->_data[i] = this->_data[i + 1];
	}
	this->_size -= 1; 
	if (this->_size * 2 <= this->_capacity) {
		this->_data = (ValueType*)realloc(this->_data, this->_size * sizeof(ValueType));
		this->_capacity = this->_size;
	}
}

void Vector::reserve(size_t capacity)
{
	if (capacity == this->_capacity)
	{
		this->_data = (ValueType*)realloc(this->_data, sizeof(ValueType) * capacity);
		this->_capacity = capacity;
	}
}

size_t Vector::capacity() const {
	return this->_capacity;
}

size_t Vector::size() const{
	return this->_size;
}

double Vector::loadFactor() const {
	return (this->_size / this->_capacity);
}

void Vector::shrinkToFit() {
	this->_data = (ValueType*)realloc(this->_data, sizeof(ValueType) * this->_size);
	this->_capacity = this->_size;
}

long long Vector::find(const ValueType& value) const {
	for (int i = 0; i < this->_size; i++) {
		if (this->_data[i] == value) {
			return i;
		}
	}
	return -1;
}

ValueType& Vector::operator[](size_t idx) {
	return this->_data[idx];
}

const ValueType& Vector::operator[](size_t idx) const {
	return this->_data[idx];
}

void Vector::insert(const ValueType& value, size_t pos) {
	if (pos < this->_size && pos >= 0) {
		this->reserve(this->_size);
		for (int i = this->_size; i > pos; i--) {
			this->_data[i] = this->_data[i - 1];
		}
		this->_size += 1;
		this->_data[pos] = value;
	}
}

void Vector::insert(const ValueType* values, size_t size, size_t pos) {
	if (this->_size + size <= this->_capacity){
		this->_capacity = size + this->_size;
		this->_data = (ValueType*)realloc(this->_data, this->_capacity * sizeof(ValueType));
	}
	ValueType *temp = new ValueType[this->_size + size];
	for (int i = 0; i < pos; i++){
		temp[i] = this->_data[i];
	}
	for (int i = pos; i < pos + size; i++){
		temp[i] = values[i - pos];
	}
	for (int i = pos; i < this->_size; i++){
		temp[i + size] = this->_data[i];
	}
	this->_data = temp;
	this->_size += size;
}

void Vector::insert(const Vector& vector, size_t pos){
	if (this->_size + vector._size <= this->_capacity) {
		this->_capacity = vector._size + this->_size;
		this->_data = (ValueType*)realloc(this->_data, this->_capacity * sizeof(ValueType));
	}
	ValueType* temp = new ValueType[this->_size + vector._size];
	for (int i = 0; i < pos; i++) {
		temp[i] = this->_data[i];
	}
	for (int i = pos; i < pos + vector._size; i++) {
		temp[i] = vector[i - pos];
	}
	for (int i = pos; i < this->_size; i++) {
		temp[i + vector._size] = this->_data[i];
	}
	this->_data = temp;
	this->_size += vector._size;
}

void Vector::erase(size_t pos, size_t count) {
	int end = 0;
	if (pos + count >= this->_size) {
		
		this->_size = pos;
	}
	else {
		end = pos + count;
		for (int i = pos; i <= end; i++) {
			this->_data[i] = this->_data[i + count];
		}
		this->_size -= count;
	}
	if (this->_size * 2 <= this->_capacity) {
		this->_data = (ValueType*)realloc(this->_data, this->_size * sizeof(ValueType));
		this->_capacity = this->_size;
	}
}