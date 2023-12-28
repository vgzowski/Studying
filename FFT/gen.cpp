#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

signed main() {
	const int N = 3e5;
	const int M = 1e9 + 7;

	int n = N / 2 + rng() % (N / 2);
	int m = N / 2 + rng() % (N / 2);
	cout << n << " " << m << '\n';

	for (int i = 0; i < n; ++i) cout << M / 2 - 5 + rng() % (M / 2) << " ";
	cout << '\n';
	for (int i = 0; i < m; ++i) cout << M / 2 - 5 + rng() % (M / 2) << " ";
}
