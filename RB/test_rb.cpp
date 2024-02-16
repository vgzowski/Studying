#include <iostream>
#include "rb_tree.h"

using namespace RB;
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <random>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace __gnu_pbds;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void test_random(int ITERATIONS, int MAXSIZE) {
	for (int iter = 0; iter < ITERATIONS; ++iter) {

		int N = 1 + rng() % MAXSIZE;
		std::vector <int> vec(N);
		for (int i = 0; i < N; ++i) {
			vec[i] = rng() % INT_MAX;
		}

		double tst = clock();

		rb_tree <int> t;
		for (int i = 0; i < N; ++i) t.insert(vec[i]);

		double ten = clock();

		cout << fixed << setprecision(3) << "Iteration " << iter << ": " << (ten - tst) / 1000.0 << " s" << endl;
	}
}

int main() {
	test_random(1, 1000);
	test_random(1, 10000);
	test_random(1, 100000);
	test_random(1, 1000000);
	test_random(1, 10000000);
}
