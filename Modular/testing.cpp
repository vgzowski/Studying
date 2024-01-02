#include <bits/stdc++.h>
#include "Modular.h"

using namespace std;

int main() {
	ModInteger<11> a(3);
	cout << a * a.inverse() << endl;
	cout << -a << endl;

	cout << abs(a) << endl;

	cout << pow(a, 4) << endl;
	cout << a * 128 << endl;

	ModInteger<10> b(3);
	cout << b * b.inverse() << endl;

	static_assert( IsModular<ModInteger<-5>>::value );
	static_assert( IsModular<ModInteger<123>>::value );
	static_assert( IsModular<ModInteger<11>>::value );
	static_assert( IsModular<ModInteger<0>>::value );
	static_assert( !IsModular<int>::value );
}
