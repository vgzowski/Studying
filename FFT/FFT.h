#pragma once
#include <iostream>
#include <cmath>
#include <vector>

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

	cp *a, *b;
	cp *w, *iw;

	int *reverse;

	int N = 0;

	void init(int _N) {
		w = new cp[_N];
		iw = new cp[_N];
		for (int k = 0; (1 << (k + 1)) <= _N; ++k) {
			int t = 1 << k;

			long double ang = 2 * pi / t;

			cp root( cos(ang), sin(ang) );
			cp iroot = root.conj();

			w[t] = cp(1);
			iw[t] = cp(1);
			for (int u = t + 1; u < (t << 1); ++u) {
				w[u] = w[u - 1] * root;
				iw[u] = iw[u - 1] * iroot;
			}
		}

		a = new cp[_N];
		b = new cp[_N];
		reverse = new int[_N];

		N = _N;
	}

	void fft(cp *a, int n, bool inverse) {
		const int l = lg2(n);
		for (int i = 1; i < n; ++i) reverse[i] = (reverse[i >> 1] >> 1) | ((i & 1) << (l - 1));
		for (int i = 0; i < n; ++i) if (i < reverse[i]) std::swap(a[i], a[reverse[i]]);

		for (int l = 1; l < n; l <<= 1) {
			for (int i = 0; i < n; i += 2 * l) {
				for (int j = 0; j < l; ++j) {
					cp a1 = a[i + j], a2 = a[i + j + l] * (inverse ? iw[2 * l + j] : w[2 * l + j]);
					a[i + j] = a1 + a2, a[i + j + l] = a1 - a2;
				}
			}
		}
		if (inverse) {
			for (int i = 0; i < n; ++i) {
				a[i] /= (long double)n;
			}
		}
	}

	template <typename U> inline int transform( U x ) { return (int)round(x); }

	template <typename T>
	std::vector <T> multiply(const std::vector <T>& A, const std::vector <T>& B) {
		const int& n = A.size();
		const int& m = B.size();

		int s = get2(n + m + 10);

		for (int i = 0; i < s; ++i) a[i] = cp(0);
		for (int i = 0; i < n; ++i) a[i] = cp(A[i]);

		for (int i = 0; i < s; ++i) b[i] = cp(0);
		for (int i = 0; i < m; ++i) b[i] = cp(B[i]);

		fft(a, s, 0);
		fft(b, s, 0);
		for (int i = 0; i < s; ++i) {
			a[i] *= b[i];
		}
		fft(a, s, 1);
		std::vector <T> result(s);
		for (int i = 0; i < s; ++i) {
			result[i] = transform(a[i].r);
		}
		while (result.size() > 1 && result.back() == T(0)) result.pop_back();
		return result;
	}
	std::vector <int> multiply_mod(const std::vector <int>& A, const std::vector <int>& B, const int &Mod) {
		const int C = (int)sqrt(Mod);

		const int& n = A.size();
		const int& m = B.size();
		std::vector <int> A1(n), A2(n);
		std::vector <int> B1(m), B2(m);
		for (int i = 0; i < n; ++i) {
			A1[i] = A[i] % C;
			A2[i] = A[i] / C;
		}
		for (int i = 0; i < m; ++i) {
			B1[i] = B[i] % C;
			B2[i] = B[i] / C;
		}

		std::vector <int> result = multiply<int>(A1, B1);
		std::vector <int> 	temp1 = multiply(A1, B2),
					temp2 = multiply(A2, B1),
					temp3 = multiply(A2, B2);

		for (int i = 0; i < result.size(); ++i) {
			result[i] += (temp1[i] * 1LL * C) % Mod;
			if (result[i] >= Mod) result[i] -= Mod;

			result[i] += (temp2[i] * 1LL * C) % Mod;
			if (result[i] >= Mod) result[i] -= Mod;

			result[i] += (temp3[i] * 1LL * C * 1LL * C) % Mod;
			if (result[i] >= Mod) result[i] -= Mod;
		}

		while (result.size() > 1 && result.back() == 0) result.pop_back();
		return result;
	}
};
