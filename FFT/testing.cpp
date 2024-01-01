#include <bits/stdc++.h>
#include "FFT.h"

using namespace std;

signed main() {
	{
		vector <int> a{123341, 7452};
		vector <int> b{854126, 38855, 33};

		auto c = a;

		for (auto &i : c) cout << i << " ";
		cout << '\n';
	}

	{
		vector <double> a{1.1, 2.3};
		vector <double> b{2.3, 4.1, 4.3};

		vector <double> c = FFT::multiply<double>(a, b);

		for (auto &i : c) cout << i << " ";
		cout << '\n';
	}

	{
		vector <int> a{1, 3};
		vector <int> b{2, 4, 1};

		vector <int> c = FFT::multiply(a, b);

		for (auto &i : c) cout << i << " ";
		cout << '\n';
	}
}
