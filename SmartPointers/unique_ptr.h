#pragma once

template <class T>
class uPtr {
public:
	uPtr(T* ptr) : ptr_(ptr) {}

	uPtr(const uPtr &other) = delete;
	uPtr& operator = (const uPtr &other) = delete;

	uPtr& operator = (uPtr&& other) noexcept {
		ptr_ = other.ptr_;
		other.ptr_ = nullptr;
		return *this;
	}
	uPtr(uPtr&& other) noexcept : ptr_(other.ptr_) {
		other.ptr_ = nullptr;
	}

	~uPtr() {
		delete ptr_;
	}

	T* operator -> () { return ptr_; }
	T operator * () { return *ptr_; }
private:
	T* ptr_;
};
