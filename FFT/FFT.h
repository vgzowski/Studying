#pragma once
#include <iostream>
#include <cmath>
#include <vector>

namespace FFT {
	template <typename T> struct cpx {
		T r, i;
		cpx() : r(0), i(0) {}
		cpx(int x) : r(x), i(0) {}
		cpx(long long x) : r(x), i(0) {}
		cpx(double x) : r(x), i(0) {}
		cpx(long double x) : r(x), i(0) {}
		cpx(long double r, long double i) : r(r), i(i) {}

		cpx operator + (const cpx& other) const { return cpx(r + other.r, i + other.i); }
		cpx& operator += (const cpx& other) { r += other.r, i += other.i; return *this; }

		cpx operator - (const cpx& other) const { return cpx(r - other.r, i - other.i); }
		cpx& operator -= (const cpx& other) { r -= other.i, i -= other.i; return *this; }

		cpx operator * (const cpx& other) const { return cpx(r * other.r - i * other.i, r * other.i + i * other.r); }
		cpx& operator *= (const cpx& other) { *this = *this * other; return *this; }

		template <typename U> cpx& operator *= (const U& x) { r *= x, i *= x; return *this; }
		template <typename U> cpx& operator /= (const U& x) { r /= x, i /= x; return *this; }
		template <typename U> cpx operator * (const U& x) const { return cpx(r * x, i * x); }
		template <typename U> cpx operator / (const U& x) const { return cpx(r / x, i / x); }

		inline cpx conj() const { return cpx(r, -i); }
	};

	typedef cpx<long double> cplx;
	constexpr long double pi = 3.14159265358979323846264338327950;
	static inline int lg2(int n) { return 31 - __builtin_clz(n); }
	static inline int get2(int n) { return 1 << (32 - __builtin_clz(n - 1)); }

	constexpr int LG = 20;
	constexpr int N = 1 << LG;

	int reverse[N];
	cplx a[N], b[N], w[N], iw[N];
	std::vector <cplx> as, bs, ab, bb;

	inline void init() {
		w[1] = iw[1] = cplx(1);
		for (int k = 1, u = 2; k < LG; ++k, u <<= 1) {
			long double A = pi / u;
			cplx z(cos(A), sin(A)); cplx iz = z.conj();
			for (int i = u >> 1; i < u; ++i) {
				w[i << 1] = w[i]; w[i << 1 | 1] = w[i] * z;
				iw[i << 1] = iw[i]; iw[i << 1 | 1] = iw[i] * iz;
			}
		}
	}
	inline void fft(cplx *a, int n) {
		const int l = lg2(n);
		for (int i = 1; i < n; ++i) reverse[i] = (reverse[i >> 1] | ((i & 1) << l)) >> 1;
		for (int i = 0; i < n; ++i) if (i < reverse[i]) std::swap(a[i], a[reverse[i]]);
		for (int l = 1; l < n; l <<= 1) {
			for (int i = 0; i < n; i += 2 * l) {
				for (int j = 0; j < l; ++j) {
					cplx u = a[i + j + l] * w[l + j];
					a[i + j + l] = a[i + j] - u;
					a[i + j] += u;
				}
			}
		}
	}
	inline void ifft(cplx *a, int n) {
		const int l = lg2(n);
		for (int i = 1; i < n; ++i) reverse[i] = (reverse[i >> 1] | ((i & 1) << l)) >> 1;
		for (int i = 0; i < n; ++i) if (i < reverse[i]) std::swap(a[i], a[reverse[i]]);
		for (int l = 1; l < n; l <<= 1) {
			for (int i = 0; i < n; i += 2 * l) {
				for (int j = 0; j < l; ++j) {
					cplx u = a[i + j + l] * iw[l + j];
					a[i + j + l] = a[i + j] - u;
					a[i + j] += u;
				}
			}
		}
		for (int i = 0; i < n; ++i) a[i] /= n;
	}

	template <typename T>
	std::vector <long long> multiply(const std::vector <T>& A, const std::vector <T>& B) {
		const int& n = A.size(), &m = B.size();
		int s = get2(n + m);

		for (int i = 0; i < s; ++i) {
			a[i].r = (i < n ? A[i] : 0);
			a[i].i = (i < m ? B[i] : 0);
		}

		fft(a, s);
		cplx r(0, -0.25 / s);
		for (int i = 0; i <= (s >> 1); ++i) {
			int j = (s - i) & (s - 1);
			cplx z = (a[j] * a[j] - (a[i] * a[i]).conj()) * r;
			if (i != j) a[j] = (a[i] * a[i] - (a[j] * a[j]).conj()) * r;
			a[i] = z;
		}
		fft(a, s);

		std::vector <long long> result(s);
		for (int i = 0; i < s; ++i) result[i] = a[i].r + 0.5;
		return result;
	}
	std::vector <int> multiply_mod(const std::vector <int>& A, const std::vector <int>& B, const int &Mod) {
		const int& n = A.size(), &m = B.size();
		int s = get2(n + m);
		if (as.size() < s) as.resize(s);
		if (ab.size() < s) ab.resize(s);
		if (bs.size() < s) bs.resize(s);
		if (bb.size() < s) bb.resize(s);

		for (int i = 0; i < s; ++i) {
			a[i].r = (i < n ? A[i] & ((1 << 15) - 1) : 0);
			a[i].i = (i < n ? A[i] >> 15 : 0);
		}
		fft(a, s);
		for (int i = 0; i < s; ++i) {
			int j = (s - 1) & (s - i);
			as[i] = (a[i] + a[j].conj()) * 0.5;
			ab[i] = (a[j].conj() - a[i]) * cplx(0, 0.5);
		}

		for (int i = 0; i < s; ++i) {
			b[i].r = (i < m ? B[i] & ((1 << 15) - 1) : 0);
			b[i].i = (i < m ? B[i] >> 15 : 0);
		}
		fft(b, s);
		for (int i = 0; i < s; ++i) {
			int j = (s - 1) & (s - i);
			bs[i] = (b[i] + b[j].conj()) * 0.5;
			bb[i] = (b[j].conj() - b[i]) * cplx(0, 0.5);
		}

		for (int i = 0; i < s; ++i) {
			a[i] = as[i] * bs[i] + cplx(0, 1) * (as[i] * bb[i] + ab[i] * bs[i]);
			b[i] = ab[i] * bb[i];
		}

		ifft(a, s); ifft(b, s);
		std::vector <int> result(s);
		for (int i = 0; i < s; ++i) {
			int A = (long long)(a[i].r + 0.5) % Mod;
			int B = (((long long)(a[i].i + 0.5) % Mod) << 15ll) % Mod;
			int C = (((long long)(b[i].r + 0.5) % Mod) << 30ll) % Mod;
			result[i] = (((A + B) % Mod) + C) % Mod;
		}
		return result;
	}
};
