#pragma once
#include <iostream>

class ICreator {
public:
	virtual void print() = 0;
};

template <
	typename SizePolicy,
	typename CachePolicy,
	typename ErrorPolicy
>
class Creator : ICreator {
public:
	void print() override {
		std::cout << "SizePolicy is: " << sizePolicy.str << std::endl;
		std::cout << "CachePolicy is: " << cachePolicy.str << std::endl;
		std::cout << "ErrorPolicy is: " << errorPolicy.str << std::endl;
	}
private:
	SizePolicy sizePolicy;
	CachePolicy cachePolicy;
	ErrorPolicy errorPolicy;
};
