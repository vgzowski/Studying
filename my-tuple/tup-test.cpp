#include <iostream>
#include <vector>
#include "tup.h"

using namespace std;

int main() {
	{
		double x = 2;
		vector <int> u{1, 2};
		tup <int, int, vector <int>> a(1, x, u);
		get_val<0>(a) = 2;
		cout << (get_val<0>(a)) << '\n';
	}
	{
		int a = 2;
		tup <int&, int> t(a, 4);
		get_val<0>(t) = 3;
		cout << a << '\n';
	}
	{
		class A {
			public:
			A() { cout << "A()" << endl; }
			~A() { cout << "~A()" << endl; }
		};
		class B {
			public:
			B() { cout << "B()" << endl; }
			~B() { cout << "~B()" << endl; }
		};
		A new_a;
		B new_b;
		tup <int, A, A, B> my(1, new_a, A(), new_b);
	}
	{
		tup t(1, 2, "asdsd");
	}
	{
		vector <int> a{1, 2};
		tup t(a, vector <int> {3, 4});
	}
	{
		int a = 1;
		int b = 2;
		int c = 3;

		cout << a << " " << b << " " << c << '\n';
		tup r(a, b, c);
		
		get_val <0> (r) = 5;
		get_val <1> (r) = 5;
		get_val <2> (r) = 5;

		cout << a << " " << b << " " << c << '\n';
		cout << (get_val <0> (r)) << " ";
		cout << (get_val <1> (r)) << " ";
		cout << (get_val <2> (r)) << '\n';
	}

	{
		int a = 1;
		int b = 2;
		int c = 3;

		cout << a << " " << b << " " << c << '\n';
		tup <int, int&, int&> r(a, b, c);
		
		get_val <0> (r) = 5;
		get_val <1> (r) = 5;
		get_val <2> (r) = 5;

		cout << a << " " << b << " " << c << '\n';
		cout << (get_val <0> (r)) << " ";
		cout << (get_val <1> (r)) << " ";
		cout << (get_val <2> (r)) << '\n';
	}

	{
		tup <int, int&&> r(1, 2);
		vector <int> vec{5, 5, 5, 5};
		tup <int, vector <int>&&> u(1, move(vec));

		auto sec = get_val <1> (u);
		for (auto x : sec) cout << x << " ";
		cout << '\n';
		for (auto x : sec) cout << x << " ";
		cout << '\n';
		for (auto x : sec) cout << x << " ";
	}
}
