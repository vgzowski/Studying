#pragma once
#include <iostream>

template <class T>
class uPtr {
public:
	uPtr(T* ptr) : ptr_(ptr) {
		std::cout << "Default constructor" << std::endl;
	}

	uPtr(const uPtr &other) = delete;
	uPtr& operator = (const uPtr &other) = delete;

	uPtr& operator = (uPtr&& other) noexcept {
		std::cout << "Move assignment operator" << std::endl;
		if (this != &other) {
			ptr_ = other.ptr_;
			other.ptr_ = nullptr;
		}
		return *this;
	}
	uPtr(uPtr&& other) noexcept : ptr_(other.ptr_) {
		std::cout << "Move assignment constructor" << std::endl;
		other.ptr_ = nullptr;
	}

	~uPtr() {
		std::cout << "Destruction" << std::endl;
		delete ptr_;
	}

	T* operator -> () { return ptr_; }
	T operator * () { return *ptr_; }
private:
	T* ptr_;
};
