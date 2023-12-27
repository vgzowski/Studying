#include <bits/stdc++.h>
using namespace std;

namespace FFT {
	template <typename T> struct cplx {
		T r, i;
		cplx() : r(T(0)), i(T(0)) {}
		cplx(int x) : r(static_cast<T>(x)), i(T(0)) {}
		cplx(long long x) : r(static_cast<T>(x)), i(T(0)) {}
		cplx(double x) : r(static_cast<T>(x)), i(T(0)) {}
		cplx(long double x) : r(static_cast<T>(x)), i(T(0)) {}

		cplx(T r, T i) : r(r), i(i) {}

		cplx operator + (const cplx& other) const { return cplx(r + other.r, i + other.i); }
		cplx& operator += (const cplx& other) { r += other.r, i += other.i; return *this; }

		cplx operator - (const cplx& other) const { return cplx(r - other.r, i - other.i); }
		cplx& operator -= (const cplx& other) { r -= other.i, i -= other.i; return *this; }

		cplx operator * (const cplx& other) const { return cplx(r * other.r - i * other.i, r * other.i + i * other.r); }
		cplx& operator *= (const cplx& other) { *this = *this * other; return *this; }

		cplx& operator *= (const T& x) { r *= x, i *= x; return *this; }
		cplx& operator /= (const T& x) { r /= x, i /= x; return *this; }

		inline cplx conj() {
			return cplx(r, -i);
		}
	};

	static inline int lg2(int n) { return 31 - __builtin_clz(n); }
	static inline int get2(int n) { return 1 << (32 - __builtin_clz(n - 1)); }

	typedef cplx<long double> cp;
	constexpr long double pi = 3.14159265358979323846264338327950;

	const int N = 1 << 22;

	int reverse[N];
	cp a[N], w[N];

	inline void init() {
		for (int k = 0; k <= 21; ++k) {
			int t = 1 << k;
			long double ang = 2 * pi / t;
			cp root( cos(ang), sin(ang) ); w[t] = cp(1);
			for (int u = t + 1; u < (t << 1); ++u) {
				w[u] = w[u - 1] * root;
			}
		}
	}

	inline void fft(cp *a, int n) {
		const int l = lg2(n);
		for (int i = 1; i < n; ++i) reverse[i] = (reverse[i >> 1] | ((i & 1) << l)) >> 1;
		for (int i = 0; i < n; ++i) if (i < reverse[i]) std::swap(a[i], a[reverse[i]]);
		for (int l = 1; l < n; l <<= 1) {
			for (int i = 0; i < n; i += 2 * l) {
				for (int j = 0; j < l; ++j) {
					cp a1 = a[i + j], a2 = a[i + j + l] * w[2 * l + j];
					a[i + j] = a1 + a2, a[i + j + l] = a1 - a2;
				}
			}
		}
	}

	template <typename T>
	std::vector <long long> multiply(const std::vector <T>& A, const std::vector <T>& B) {
		const int& n = A.size();
		const int& m = B.size();

		int s = get2(n + m);
		for (int i = 0; i < s; ++i) {
			a[i].r = (i < n ? A[i] : 0);
			a[i].i = (i < m ? B[i] : 0);
		}

		fft(a, s);
		cp r(0, -0.25 / s);
		for (int i = 0; i <= (s >> 1); ++i) {
			int j = (s - i) & (s - 1);
			cp z = (a[j] * a[j] - (a[i] * a[i]).conj()) * r;
			if (i != j) a[j] = (a[i] * a[i] - (a[j] * a[j]).conj()) * r;
			a[i] = z;
		}
		fft(a, s);

		std::vector <long long> result(s);
		for (int i = 0; i < s; ++i) {
			result[i] = a[i].r + 0.5;
		}
		return result;
	}
	std::vector <long long> multiply_mod(const std::vector <int>& A, const std::vector <int>& B, const int &Mod) {
		const int& n = A.size();
		const int& m = B.size();

		std::vector <long long> A1(n), A2(n);
		std::vector <long long> B1(m), B2(m);
		for (int i = 0; i < n; ++i) {
			A1[i] = A[i] & ((1 << 15) - 1);
			A2[i] = A[i] >> 15;
		}
		for (int i = 0; i < m; ++i) {
			B1[i] = B[i] & ((1 << 15) - 1);
			B2[i] = B[i] >> 15;
		}

		std::vector <long long> result = multiply(A1, B1);
		std::vector <long long> temp1 = multiply(A1, B2),
					temp2 = multiply(A2, B1),
					temp3 = multiply(A2, B2);

		for (int i = 0; i < result.size(); ++i) {
			long long a = result[i] % Mod, b = temp1[i] % Mod, c = temp2[i] % Mod, d = temp3[i] % Mod;
			b <<= 15ll; b %= Mod;
			c <<= 15ll; c %= Mod;
			d <<= 30ll; c %= Mod;
			result[i] = (a + b + c + d) % Mod;
		}

		return result;
	}
};

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
