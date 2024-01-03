#include <iostream>
#include <vector>

/*
Typeifier is usually used for:
Compiling and running different implementation based on some constant integral result

Every Typifier <X> generates a new distinct type for that X
Thus we can play with overloading our functions
*/

template <int Value> struct Typifier { enum { value = Value }; };

template <typename T, bool OkayForPrinting>
class Printer {
private:
	T obj;
	void print( Typifier <true> ) {
		std::cout << obj << std::endl;
	}
	void print( Typifier <false> ) {
		std::cout << "Not available for printing" << std::endl;
	}
public:
	Printer(T obj) : obj(obj) {}
	void print() { print( Typifier <OkayForPrinting>() ); }
};

// -----------------------------------------------------------

/*
Changer is usually used for:
Specific implementation for different types (when partial specialisation is needed
*/

template <typename T> struct Changer { typedef T type; };

template <typename T, typename U>
void print(T a, U b, Changer<U>* = 0) {
	std::cout << a << " " << b << std::endl;
}

/*
template<typename T>
void print<T, bool>(T a, bool b) {
	std::cout << a << " " << (b ? "true" : "false") << std::endl;
}
CE: Partial specialisation of functions is not allowed
Correct version below
*/

template <typename T>
void print(T a, bool b, Changer<bool>* = 0) {
	std::cout << a << " " << (b ? "true" : "false") << std::endl;
}

/*
Works because of overloading:
Changer<T> is a different type for different types T
Thus we get an analogue of partial template specification without increasing run-time
*/

int main() {
{
	Printer<int, true> a(5);
	Printer<char, true> b('y');
	Printer<std::vector <int>, false> c({1, 2, 3});
	Printer<int, false> d(7);
	Printer<double, true> e(7.8);

	a.print();
	b.print();
	c.print();
	d.print();
	e.print();
}
	// ---------------
{
	int a = 1;
	int b = 2;
	bool c = 3;

	print(a, b);
	print(b, c);
	print(a, c);
	print(c, b);
}
}
