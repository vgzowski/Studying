#pragma once

template <class T>
class sPtr {
public:
	sPtr(T* ptr) : refCount_(new int(1)), ptr_(ptr) {}
	sPtr(const sPtr &other) {
		ptr_ = other.ptr_;
		refCount_ = other.refCount_;
		if (other.ptr_ != nullptr) {
			++(*refCount_);
		}
	}
	sPtr& operator = (const sPtr &other) {
		if (this != &other) {
			ptr_ = other.ptr_;
			refCount_ = other.refCount_;
			if (other.ptr_ != nullptr) {
				++(*refCount_);
			}
		}
		return *this;
	}
	sPtr(sPtr&& other) noexcept : ptr_(other.ptr_), refCount_(other.refCount_) {
		other.ptr_ = other.refCount_ = nullptr;
	}
	sPtr& operator = (sPtr&& other) noexcept {
		ptr_ = other.ptr_;
		refCount_ = other.refCount_;
		other.ptr_ = other.refCount_ = nullptr;
		return *this;
	}
	~sPtr() {
		if (refCount_ && !(*refCount_)) {
			delete ptr_;
		}
	}

	T* operator -> () { return ptr_; }
	T operator * () { return *ptr_; }
private:
	int *refCount_;
	T* ptr_;
};
