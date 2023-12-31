#include <iostream>
#include <cassert>

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

int main() {
	std::cout << Phi<int,1000000000>::Result << std::endl;
	std::cout << Phi<int,1000000001>::Result << std::endl;
	std::cout << Phi<int,1000000002>::Result << std::endl;
	std::cout << Phi<int,1000000003>::Result << std::endl;
	std::cout << Phi<int,1000000004>::Result << std::endl;
	std::cout << Phi<int,1000000005>::Result << std::endl;
	std::cout << Phi<int,1000000006>::Result << std::endl;
	std::cout << Phi<int,1000000007>::Result << std::endl;
	std::cout << Phi<int,1000000008>::Result << std::endl;
	std::cout << Phi<int,1000000009>::Result << std::endl;
	std::cout << Phi<int,1000000010>::Result << std::endl;

	std::cout << Factorial::factorial<5>::Result << std::endl;
	std::cout << Factorial::factorial<6>::Result << std::endl;
	std::cout << Factorial::factorial<7>::Result << std::endl;
	std::cout << Factorial::factorial<8>::Result << std::endl;
	std::cout << Factorial::factorial<9>::Result << std::endl;
	std::cout << Factorial::factorial<10>::Result << std::endl;

	check<998244353,(int)2e5>();
}
