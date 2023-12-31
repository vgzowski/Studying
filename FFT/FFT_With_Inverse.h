#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include "../CompileTime/TypeList.H"

typedef typelist <short int, int, long, long long> __FFT_IntegerList;

namespace FFT_Inverse {
	constexpr long double pi = acos(-1);

	template <typename T>
	struct cpx {
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

		cpx operator - () const { return cpx(-r, -i); }
		cpx conj() const { return cpx(r, -i); }
	};

	typedef cpx <long double> cplx;

	inline int lg2(int n) { return 31 - __builtin_clz(n); }
	inline int get2(int n) { return 1 << (32 - __builtin_clz(n - 1)); }

	int LG = 1;
	int N = 2;

	std::vector <int> reverse(N);
	std::vector <cplx> a(N), b(N), w{cplx(0), cplx(1)}, iw = w;

	void update_size(int _N) {
		if (_N <= N) return;
		int _LG = lg2(_N);

		w.resize(_N);
		iw.resize(_N);
		reverse.resize(_N);

		a.resize(_N);
		b.resize(_N);
		
		for (int k = LG, u = 1 << LG; k < _LG; ++k, u <<= 1) {
			long double A = pi / u;

			cplx z(cos(A), sin(A));
			cplx iz = z.conj();
			for (int i = u >> 1; i < u; ++i) {
				w[i << 1] = w[i];
				w[i << 1 | 1] = w[i] * z;

				iw[i << 1] = iw[i];
				iw[i << 1 | 1] = iw[i] * iz;
			}
		}
		N = _N;
		LG = _LG;
	}

	void fft(std::vector <cplx>& a, int n) {
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
	void ifft(std::vector <cplx>& a, int n) {
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

	template <typename T, typename Dummy = char>
	std::vector <T> multiply(const std::vector <T>& A, const std::vector <T>& B,
				typename std::enable_if < IndexOf <T, __FFT_IntegerList>::value == -1, Dummy >::type* = 0) {

		const int& n = A.size(), &m = B.size();

		int s = get2(n + m);
		update_size(s);

		for (int i = 0; i < s; ++i) {
			a[i].r = i < n ? A[i] : 0;
			a[i].i = i < m ? B[i] : 0;
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

		s = n + m - 1;
		std::vector <T> result(s);
		for (int i = 0; i < s; ++i) result[i] = a[i].r;
		return result;
	}
	template <typename T, typename Dummy = char>
	std::vector <T> multiply(const std::vector <T>& A, const std::vector <T>& B,
				typename std::enable_if < IndexOf <T, __FFT_IntegerList>::value != -1, Dummy >::type* = 0) {

		const int& n = A.size(), &m = B.size();

		int s = get2(n + m);
		update_size(s);

		for (int i = 0; i < s; ++i) {
			a[i].r = i < n ? A[i] : 0;
			a[i].i = i < m ? B[i] : 0;
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

		s = n + m - 1;
		std::vector <T> result(s);
		for (int i = 0; i < s; ++i) result[i] = T(a[i].r + 0.5);
		while (result.size() > 1 && result.back() == 0) result.pop_back();
		return result;
	}

	std::vector <int> multiply_mod(const std::vector <int>& A, const std::vector <int>& B, const int &Mod) {
		const int& n = A.size(), &m = B.size();

		int s = get2(n + m);
		update_size(s);

		for (int i = 0; i < s; ++i) {
			a[i].r = (i < n ? A[i] & ((1 << 15) - 1) : 0);
			a[i].i = (i < n ? A[i] >> 15 : 0);
		} fft(a, s);

		for (int i = 0; i < s; ++i) {
			b[i].r = (i < m ? B[i] & ((1 << 15) - 1) : 0);
			b[i].i = (i < m ? B[i] >> 15 : 0);
		} fft(b, s);

		for (int i = 0; i <= (s >> 1); ++i) {
			int j = (s - 1) & (s - i);

			cplx asi = (a[i] + a[j].conj()) * 0.5;
			cplx abi = (a[j].conj() - a[i]) * cplx(0, 0.5);

			cplx bsi = (b[i] + b[j].conj()) * 0.5;
			cplx bbi = (b[j].conj() - b[i]) * cplx(0, 0.5);

			if (i != j) {
				cplx asj = (a[j] + a[i].conj()) * 0.5;
				cplx bsj = (b[j] + b[i].conj()) * 0.5;
				cplx abj = (a[i].conj() - a[j]) * cplx(0, 0.5);
				cplx bbj = (b[i].conj() - b[j]) * cplx(0, 0.5);

				a[j] = (asj * bsj + cplx(0, 1) * (asj * bbj + abj * bsj));
				b[j] = abj * bbj;
			}
			a[i] = (asi * bsi + cplx(0, 1) * (asi * bbi + abi * bsi));
			b[i] = abi * bbi;
		}

		ifft(a, s);
		ifft(b, s);

		s = n + m - 1;
		std::vector <int> result(s);
		for (int i = 0; i < s; ++i) {
			int A = (long long)(a[i].r + 0.5) % Mod;
			A += (((long long)(a[i].i + 0.5) % Mod) << 15ll) % Mod; if (A >= Mod) A -= Mod;
			A += (((long long)(b[i].r + 0.5) % Mod) << 30ll) % Mod; if (A >= Mod) A -= Mod;
			result[i] = A;
		}
		while (result.size() > 1 && result.back() == 0) result.pop_back();
		return result;
	}
};
