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
	uPtr<int> a(new int(5));
	std::cout << *a << std::endl;

	uPtr<int> b = std::move(a);
	std::cout << *b << std::endl;
//	std::cout << *a << std::endl; RE

//	a = b; CE
	uPtr<int> c = std::move(b);
	std::cout << *c << std::endl;

	uPtr<My> d(new My());
	d->foo();

	uPtr<My> e = std::move(d);
	e->foo();
}
{ // sahred pointer
	sPtr<int> a(new int(7));
	std::cout << *a << std::endl;

	sPtr<int> b = std::move(a);
	std::cout << *b << std::endl;
	
//	std::cout << *a << std::endl; RE

	std::cout << "count b is: " << b.use_count() << std::endl;

	a = b;

	std::cout << "count b is: " << b.use_count() << std::endl;
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
