#pragma once

#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>


struct TVector {
	TVector() : capacity{ 0 }, size{ 0 }, data{ nullptr } {};

	TVector(const char* str) {
		this->size = std::strlen(str);
		this->capacity = this->size + 1;
		this->data = new char[this->capacity];
		std::copy(str, str + this->size, this->data);
		this->data[this->size] = '\0';
	}

	TVector(const TVector& str) {
		this->capacity = str.capacity;
		this->size = str.size;
		this->data = new char[this->capacity];
		std::copy(str.data, str.data + this->size, this->data);
		this->data[this->size] = '\0';
	}

	TVector(TVector&& str) noexcept {
		this->size = str.size;
		this->capacity = str.capacity;
		this->data = str.data;
		str.data = nullptr;
	}

	TVector& operator=(const char* str) {
		delete[] this->data;
		this->size = std::strlen(str);
		this->capacity = this->size + 1;
		this->data = new char[this->capacity];
		std::copy(str, str + this->size, this->data);
		this->data[this->size] = '\0';
		return *this;
	}

	TVector& operator=(const TVector& str) {
		char* temp = new char[str.capacity];
		std::copy(str.data, str.data + str.capacity, temp);
		delete[] this->data;
		this->data = temp;
		temp = nullptr;
		this->size = str.size;
		this->capacity = str.capacity;
		return *this;
	}

	TVector& operator=(TVector&& str) {
		delete[] this->data;
		this->size = str.size;
		this->capacity = str.capacity;
		this->data = str.data;
		str.data = nullptr;
		return *this;
	}

	void CstrMove(char* str) {
		delete[] this->data;
		this->data = str;
		this->size = strlen(str);
		this->capacity = this->size + 1;
		str = nullptr;
	}

	void Swap(TVector& str) {
		std::swap(this->size, str.size);
		std::swap(this->capacity, str.capacity);
		std::swap(this->data, str.data);
	}

	void PushBack(const char& ch) {
		if (this->size + 1 == this->capacity) {
			int newStorageSize = this->capacity ? this->capacity + this->capacity : 1;
			char* newStorage = new char[newStorageSize];
			std::copy(this->data, this->data + this->capacity, newStorage);
			delete[] this->data;
			this->data = newStorage;
			this->capacity = newStorageSize;
			newStorage = nullptr;
		}
		this->data[this->size] = ch;
		++this->size;
		this->data[this->size] = '\0';
	}

	~TVector() {
		delete[] this->data;
		this->capacity = 0;
		this->size = 0;
		this->data = nullptr;
	}

	char * begin() {
		return this->data;
	}

	const char * begin() const {
		return this->data;
	}

	char * end() {
		if (data == nullptr)
			return nullptr;
		return this->data + this->size;
	}

	const char * end() const {
		if (this->data != nullptr)
			return nullptr;
		return this->data + this->size;
	}

	const char* Cstr() const {
		return this->data;
	}

	uint64_t Size() const {
		return this->size;
	}

	TVector& operator+=(const char& ch) {
		PushBack(ch);
		return *this;
	}

	const char& At(int index) const {
		if (index >= 0 && index <= this->size)
			return this->data[index];
		throw std::out_of_range("You are doing this wrong!");
	}

	char& At(int index) {
		const char& elem = const_cast<const TVector*>(this)->At(index);
		return const_cast<char&>(elem);
	}

	const char& operator[](int index) const {
		return At(index);
	}

	char& operator[](int index) {
		return At(index);
	}

	friend std::ostream& operator<<(std::ostream& os, const TVector& str);
	friend std::istream& operator>>(std::istream& is, TVector& str);

private:
	uint64_t capacity;
	uint64_t size;
	char* data;
};

std::ostream& operator<<(std::ostream& os, const TVector& str) {
	for (auto ch : str)
		os << ch;
	return os;
}

std::istream& operator>>(std::istream& is, TVector& str) {
	char buf[300];
	if (is >> buf)
		str = buf;
	return is;
}

bool operator<(const TVector& lhs, const TVector& rhs) {
	uint32_t l_size = lhs.Size();
	uint32_t r_size = rhs.Size();
	uint32_t minSize = std::min(l_size, r_size);
	for (uint32_t i = 0; i < minSize; ++i)
		if (lhs[i] != rhs[i])
			return lhs[i] < rhs[i];
	return l_size < r_size;
}

bool operator>(const TVector& lhs, const TVector& rhs) {
	return rhs < lhs;
}

bool operator==(const TVector& lhs, const TVector& rhs) {
	return !(lhs > rhs) && !(lhs < rhs);
}

bool operator!=(const TVector& lhs, const TVector& rhs) {
	return !(lhs == rhs);
}
