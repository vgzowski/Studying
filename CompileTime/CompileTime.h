#pragma once
#include <iostream>
#include <cassert>

template <typename T, typename U>
struct is_same { enum { Same = false }; };
template <typename T>
struct is_same<T, T> { enum { Same = true }; };

template <typename T, T X>
struct st {
	T value;
	void pr() {
		std::cout << X + value << std::endl;
	}
};

template <class T, T X> struct IsPrime {
	static constexpr bool check() {
		for (T i = T(2); i * i <= X; ++i) {
			if (X % i == 0) {
				return false;
			}
		}
		return true;
	}
	enum { Result = check() };
};
template <class T, T X> struct Phi {
	static constexpr T getPhi() {
		T result = X, number = X;
		for (T i = T(2); i * i <= number; ++i) {
			if (number % i == 0) {
				result /= i;
				result *= i - T(1);
				while (number % i == 0) {
					number /= i;
				}
			}
		}
		return result;
	};
	enum { Result = getPhi() };
};

namespace Factorial {
	template <size_t T>
	struct factorial {
		enum { Result = T * factorial<T - 1>::Result };
	};
	template <>
	struct factorial<0> {
		enum { Result = 1 };
	};
};

template <int Mod, size_t maxN>
struct Inverses {
	int Inv[maxN + 1];
	constexpr Inverses() : Inv() {
		Inv[1] = 1;
		for (int i = 2; i <= maxN; ++i) {
			Inv[i] = (Mod - Mod / i) * 1LL * Inv[Mod % i] % Mod;
		}
	}
};
template <int Mod, int maxN>
int get_inverse(int x) {
	static constexpr Inverses<Mod, maxN> S;
	return S.Inv[x];
}

template <int Mod, int maxN>
void check() {
	for (int i = 1; i <= maxN; ++i) {
		assert( ( get_inverse<Mod, maxN>(i) * 1LL * i ) % Mod == 1 );
	}
}
