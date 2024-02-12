#define TESTING

#include <iostream>

#ifdef TESTING
#include "unique_ptr.h"
#include "shared_ptr.h"
#else
#include <memory>
#include <utility>
#define uPtr std::unique_ptr
#define sPtr std::shared_ptr
#endif

struct My {
	void foo() {
		std::cout << "HAHA GOT YOU" << std::endl;
	}
};

int main() {
{ // unique pointer
std::cout << "line 1:" << std::endl;
	uPtr<int> a(new int(5));
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 2:" << std::endl;
	std::cout << *a << std::endl;
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 3:" << std::endl;
	a = std::move(a);
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 4:" << std::endl;
	std::cout << *a << std::endl;
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 5:" << std::endl;
	a = uPtr<int>(std::move(a));
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 6:" << std::endl;
	std::cout << *a << std::endl;
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 7:" << std::endl;
	uPtr<int> b = std::move(a);
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 8:" << std::endl;
	std::cout << *b << std::endl;
std::cout << std::endl << "-----------" << std::endl;
//	std::cout << *a << std::endl; RE

//	a = b; CE

std::cout << "line 9:" << std::endl;
	uPtr<int> c = std::move(b);
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 10:" << std::endl;
	std::cout << *c << std::endl;
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 11:" << std::endl;
	uPtr<My> d(new My());
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 12:" << std::endl;
	d->foo();
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 13:" << std::endl;
	uPtr<My> e = std::move(d);
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 14:" << std::endl;
	e->foo();
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 15:" << std::endl;
	d = std::move(e);
std::cout << std::endl << "-----------" << std::endl;

std::cout << "line 16:" << std::endl;
	d->foo();
std::cout << std::endl << "-----------" << std::endl;
}

	std::cout << std::endl << "---------------------------------------------" << std::endl;
	return 0;

{ // shared pointer
	sPtr<int> a(new int(7));
	std::cout << *a << std::endl;

	sPtr<int> b = std::move(a);
	std::cout << *b << std::endl;
	
//	std::cout << *a << std::endl; RE

	std::cout << "count b is: " << b.use_count() << std::endl;

	a = b;

	std::cout << "count b is: " << b.use_count() << std::endl;
	std::cout << "count a is: " << a.use_count() << std::endl;

	{
		sPtr<int> c = a;
		std::cout << "count a is: " << a.use_count() << std::endl;
	}
	std::cout << "count a is: " << a.use_count() << std::endl;

	a = sPtr<int>(new int(4));

	sPtr<int> c = std::move(b);
	std::cout << *c << std::endl;
	std::cout << *a << std::endl;

	sPtr<My> d(new My());
	d->foo();

	sPtr<My> e = std::move(d);
	e->foo();
}
}
