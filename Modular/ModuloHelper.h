#pragma once

#include <array>
#include <utility>

namespace ModuloHelper {
	template <int Mod>
	struct IsPrime {
		static constexpr bool __check() {
			if ((Mod & 1) ^ 1) return false;
			for (int i = 3; i * i <= Mod; i += 2) {
				if (Mod % i == 0) return false;
			}
			return true;
		}
		enum { value = __check() };
	};
	template <int Mod>
	struct Phi {
		static constexpr int __phi() {
			int Number = Mod, Result = Mod;
			for (int i = 2; i * i <= Number; ++i) {
				if (Number % i == 0) {
					(Result /= i) *= i - 1;
					while (Number % i == 0) Number /= i;
				}
			}
			if (Number > 1) (Result /= Number) *= Number - 1;
			return Result;
		}
		static constexpr int value = __phi();
	};

	template <int Mod>
	struct PrimeDivisorsCount {
		static constexpr int __count() {
			int Number = Mod, Result = 0;
			for (int i = 2; i * i <= Number; ++i) {
				if (Number % i == 0) {
					++Result;
					while (Number % i == 0) Number /= i;
				}
			}
			return (Result += (Number > 1));
		}
		static constexpr int value = __count();
	};
	template <int Mod>
	constexpr int divAtIndex(size_t index) {
		int Number = Mod;
		for (int i = 2; i * i <= Number; ++i) {
			if (Number % i == 0) {
				if (index == 0) return i;
				--index;
				while (Number % i == 0) Number /= i;
			}
		}
		return Number;
	}
	template <typename Generator, size_t ... Indices>
	constexpr auto generateArrayHelper(Generator generator, std::index_sequence<Indices...>) {
		return std::array<decltype(std::declval<Generator>()(size_t{})), sizeof...(Indices) > { generator(Indices)... };
	}
	template <size_t Size, typename Generator>
	constexpr auto generateArray(Generator generator) {
		return generateArrayHelper(generator, std::make_index_sequence<Size>());
	}
	template <int Mod>
	struct PrimeDivisors {
		static constexpr auto value = generateArray< PrimeDivisorsCount<Mod>::value >(divAtIndex<Mod>);
	};

	template <int Mod, int A, int P>
	struct BinPow {
		static constexpr int __pow() {
			int Result = 1;
			int a = A, p = P;
			for (; p; p >>= 1, a = (a * 1ll * a) % Mod) {
				if (p & 1) Result = (Result * 1ll * a) % Mod;
			}
			return Result;
		}
		static constexpr int value = __pow();
	};

	template <int Mod, int g, int Index>
	struct IsPrimitiveRoot {
		static constexpr bool value = 
			BinPow
				<Mod,
				 g,
				 Phi<Mod>::value / PrimeDivisors< Phi<Mod>::value >::value[Index]
				>::value == 1 ? false :
			IsPrimitiveRoot<Mod, g, Index - 1>::value;
	};
	template <int Mod, int g>
	struct IsPrimitiveRoot <Mod, g, -1> {
		static constexpr bool value = true;
	};
	template <int Mod, int g = 2>
	struct PrimitiveRoot {
		static constexpr int value =
			IsPrimitiveRoot
				<Mod,
				 g,
				 PrimeDivisorsCount< Phi<Mod>::value >::value - 1
				>::value ? g :
			PrimitiveRoot<Mod, g + 1>::value;
	};
	template <int Mod>
	struct PrimitiveRoot <Mod, 101> {
		static constexpr int value = -1;
	};
};
