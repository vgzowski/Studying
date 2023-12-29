#include <bits/stdc++.h>
#include "FFT.h"

using namespace std;

signed main() {
	FFT::init();

	{
		vector <int> a{123341, 7452};
		vector <int> b{854126, 38855, 33};

		auto c = FFT::multiply_mod( a, b, (int)998244353 );

		for (auto &i : c) cout << i << " ";
		cout << '\n';
	}

	{
		vector <double> a{1.1, 2.3};
		vector <double> b{2.3, 4.1, 4.3};

		vector <double> c = FFT::multiply<double, double>(a, b);

		for (auto &i : c) cout << i << " ";
		cout << '\n';
	}

	{
		vector <double> a{1.1, 2.3};
		vector <double> b{2.3, 4.1, 4.3};

		vector <long long> c = FFT::multiply<double>(a, b);

		for (auto &i : c) cout << i << " ";
		cout << '\n';
	}
}
