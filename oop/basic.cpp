#include <iostream>

class A {
protected:
	int a = 2, b = 1;
public:
	virtual void print() {
		std::cout << "standart";
	}
};

class B : public A {
private:
	int a;
public:
	B() : a(5) {}
	void print() override {
		std::cout << a << " " << b << " " << this->a;
	}
	void B_func() {
		std::cout << "I am a B function";
	}
};

class C {
protected:
	int AA = 2, BB = 3;
public:
	virtual void print() {
		std::cout << "AAA";
	}
};

class D : public A, public C {
public:
	void print() override {
		std::cout << "D func";
	}
};

int main() {
	A x;
	x.print();

	B y;
	A* xx = &y;
	xx->print();

	y.B_func();
//	xx->B_func(); - CE

	{
		D obj;
		obj.print();
		C* p1 = &obj;
		p1->print();
		A* p2 = &obj;
		p2->print();
	}
}
