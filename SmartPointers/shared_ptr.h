#pragma once
#include <iostream>

template <class T>
class sPtr {
public:
	sPtr(T* ptr = nullptr) : refCount_(new int(ptr != nullptr)), ptr_(ptr) {
		std::cout << "Default contructor" << std::endl;
	}

	sPtr(const sPtr &other) {
		std::cout << "Copying constructor" << std::endl;

		ptr_ = other.ptr_;
		refCount_ = other.refCount_;
		if (other.ptr_ != nullptr) {
			++(*refCount_);
		}
	}
	sPtr& operator = (const sPtr &other) {
		std::cout << "Copying assignment operator" << std::endl;

		if (this != &other) {
			ptr_ = other.ptr_;
			refCount_ = other.refCount_;
			if (other.ptr_ != nullptr) {
				++(*refCount_);
			}
		}
		return *this;
	}
	sPtr(sPtr&& other) noexcept : refCount_(other.refCount_), ptr_(other.ptr_) {
		std::cout << "Move constructor" << std::endl;

		other.ptr_ = nullptr;
		other.refCount_ = nullptr;
	}
	sPtr& operator = (sPtr&& other) noexcept {
		std::cout << "Move assignment operator" << std::endl;

		if (this != &other) {
			ptr_ = other.ptr_;
			refCount_ = other.refCount_;
			other.ptr_ = nullptr;
			other.refCount_ = nullptr;
		}
		return *this;
	}
	~sPtr() {
		std::cout << "Destructor" << std::endl;

		if (refCount_) {
			(*refCount_)--;
			if (!(*refCount_)) {
				std::cout << "Destruction" << std::endl;
				delete ptr_;
				delete refCount_;
			}
		}
	}

	T* operator -> () { return ptr_; }
	T operator * () { return *ptr_; }
	int use_count() { return (refCount_ ? *refCount_ : 0); }
private:
	int *refCount_;
	T* ptr_;
};
