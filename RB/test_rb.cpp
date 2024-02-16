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
	for (int iter = 1; iter <= ITERATIONS; ++iter) {

		int N = 1 + rng() % MAXSIZE;
		std::vector <int> vec(N);
		for (int i = 0; i < N; ++i) {
			vec[i] = rng() % INT_MAX;
		}

		double tst = clock();

		rb_tree <int> t;
		for (int i = 0; i < N; ++i) {
//			cout << "Start inserting " << i << " (" << vec[i] << ")" << endl;
			t.insert(vec[i]);
//			cout << "End inserting " << i << endl;
		}

		t.check_validity();

		double ten = clock();

		cout << fixed << setprecision(3) << "Iteration " << iter << ": " << (ten - tst) / 1000.0 << " s" << endl;
	}
	cout << "---";
}

void test_random_output(int ITERATIONS, int MAXSIZE) {
	for (int iter = 1; iter <= ITERATIONS; ++iter) {

		int N = 1 + rng() % MAXSIZE;
		std::vector <int> vec(N);
		for (int i = 0; i < N; ++i) {
			vec[i] = rng() % 100;
		}

		double tst = clock();

		rb_tree <int> t;
		for (int i = 0; i < N; ++i) t.insert(vec[i]);

		double ten = clock();

		cout << fixed << setprecision(3) << "Iteration " << iter << " " << (ten - tst) / 1000.0 << " s:" << endl;
		for (auto &el : vec) cout << el << " ";
		cout << endl;
		cout << t << endl;
	}
	cout << "---";
}

int main() {
	test_random(100, 1000);
//	test_random(3, 10000);
//	test_random(3, 100000);
	test_random(1, 1000000);
//	test_random(5, 10000000);

	test_random_output(10, 12);
}
