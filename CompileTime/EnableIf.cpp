#include <iostream>
#include "TypeList.H"

template <bool B, typename T>
struct enable_if {};

template <typename T>
struct enable_if <true, T> { typedef T type; };

typedef TypeList <int, long long, short> IntList;
typedef TypeList <double, float, long double> FloatList;

template <typename T>
struct st {
	T a, b;
	template <typename U = char> void print( typename enable_if< IndexOf<T, IntList>::Result != -1, U >::type * = 0 ) {
		std::cout << a << " " << b << '\n';
	}
	template <typename U = char> void print( typename enable_if< IndexOf<T, IntList>::Result == -1, U >::type * = 0 ) {
		std::cout << "{" << a << " " << b << "}" << '\n';
	}

	template <typename U = char> st combine(const st& other, typename enable_if< IndexOf<T, IntList>::Result == -1, U >::type * = 0 ) const {
		return st{a - other.a, b - other.b};
	}
	template <typename U = char> st combine(const st& other, typename enable_if< IndexOf<T, IntList>::Result != -1, U >::type * = 0 ) const {
		return st{a + other.a, b + other.b};
	}

	st operator + (const st& other) const { return this->combine(other); }
};

template <typename T, typename U = char>
void func(T a, T b, typename enable_if< !std::is_same<T, double>::value, U >::type* = 0) {
	std::cout << a + b << '\n';
}

int main() {
	st<int> a{1, 2}, aa{2, 3};
	a.print();
	st<double> b{1, 2}, bb{2, 3};
	b.print();

	auto c = a + aa;
	auto d = b + bb;
	c.print();
	d.print();

	func((int)1, (int)2);
	func((long double)1, (long double)2);
//	func((double)1, (double)2); COMPILATION ERROR, NOT DEFINED FUNCTION FOR DOUBLE
}
