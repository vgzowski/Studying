#include <bits/stdc++.h>
#include "FFT.h"

using namespace std;

signed main() {
	FFT::init();

	int n, m;
	cin >> n >> m;
	vector <int> a(n), b(m);
	for (auto &i : a) cin >> i;
	for (auto &j : b) cin >> j;
	auto c = FFT::multiply_mod(a, b, 1000000007);
	c.resize(n + m - 1);
	for (int i = 0; i < c.size(); ++i) {
		cout << c[i];
		if (i + 1 != c.size()) cout << " ";
	}
}
