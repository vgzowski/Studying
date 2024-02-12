#include <iostream>
#include "unique_ptr.h"

struct My {
	void foo() {
		std::cout << "HAHA GOT YOU" << std::endl;
	}
};

int main() {
	uPtr<int> a = new int(5);
	std::cout << *a << std::endl;

	uPtr<int> b = std::move(a);
	std::cout << *b << std::endl;
//	std::cout << *a << std::endl; RE

//	a = b; CE
	uPtr<int> c = std::move(b);
	std::cout << *c << std::endl;

	uPtr<My> d = new My();
	d->foo();

	uPtr<My> e = std::move(d);
	e->foo();
}
