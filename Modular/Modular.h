#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <optional>

#include "ModuloHelper.h"

template <int Mod>
class ModInteger {
private:
	int value;
	static constexpr bool PrimeModulo = ModuloHelper::IsPrime<Mod>::value;
	static constexpr int Phi = ModuloHelper::Phi<Mod>::value;
	static constexpr int G = ModuloHelper::PrimitiveRoot<Mod>::value;
	static constexpr int msqrt = int(ceil(sqrt(Mod))) + 1;

	inline static std::vector < ModInteger > _inverses = std::vector < ModInteger> {0, 1};

	static std::pair <long long, long long> gcd_ex(int a, int b) {
		if (!b) return std::make_pair(1, 0);
		std::pair <long long, long long> result = gcd_ex(b, a % b);
		return std::make_pair( result.second - (a / b) * result.first, result.first );
	}
public:
	static_assert(Mod > 0, "Mod must be a positive integer");

	enum { __mod_value = Mod };
	explicit operator int() const { return value; }

	template <int ModU> friend std::istream & operator >> (std::istream &, ModInteger<ModU> &);
	template <int ModU> friend std::ostream & operator << (std::ostream &, const ModInteger<ModU> &);

	ModInteger() { value = int(0); }
	ModInteger(size_t x) { value = x < Mod ? x : x % Mod; }
	ModInteger(int x) { value = 0 <= x && x < Mod ? x : (x % Mod + Mod) % Mod; }
	ModInteger(long long x) { value = 0 <= x && x < Mod ? x : (x % Mod + Mod) % Mod; }

	ModInteger& operator += (const ModInteger& other);
	ModInteger& operator -= (const ModInteger& other);
	ModInteger& operator *= (const ModInteger& other);
	ModInteger& operator /= (const ModInteger& other);

	ModInteger operator + (const ModInteger& other) const;
	ModInteger operator - (const ModInteger& other) const;
	ModInteger operator * (const ModInteger& other) const;
	ModInteger operator / (const ModInteger& other) const;

	ModInteger operator - () const;

	template <int M> friend ModInteger<M> abs(const ModInteger<M> &);
	template <int M, typename U> friend ModInteger<M> pow( ModInteger<M>, U );

	template <int M> friend std::optional <int> log(const ModInteger<M> &, const ModInteger<M> &);

	template <typename U> ModInteger<Mod>& operator ^= (U power);
	template <typename U> ModInteger<Mod> operator ^ (U power) const;

	ModInteger inverse() const;
	std::optional<ModInteger> sqrt() const;
	std::optional<ModInteger> kroot(int) const;

	template <int M> friend void initialiseInverse(size_t);

	bool operator != (const ModInteger& other) const;
	bool operator == (const ModInteger& other) const;
	bool operator < (const ModInteger& other) const;
	bool operator <= (const ModInteger& other) const;
	bool operator > (const ModInteger& other) const;
	bool operator >= (const ModInteger& other) const;
};

template <int ModU> std::istream & operator >> (std::istream& in, ModInteger<ModU>& other) {
	in >> other.value;
	( (other.value %= ModU) += ModU ) %= ModU;
	return in;
}
template <int ModU> std::ostream & operator << (std::ostream& out, const ModInteger<ModU>& other) {
	out << other.value;
	return out;
}

template <int Mod>
ModInteger<Mod> ModInteger<Mod>::operator - () const {
	return ModInteger<Mod>( value == 0 ? 0 : Mod - value );
}

template <int Mod>
ModInteger<Mod> abs(const ModInteger<Mod>& a) {
	return a;
}

template <int Mod>
ModInteger<Mod>& ModInteger<Mod>::operator += (const ModInteger<Mod>& other) {
	this->value += other.value;
	if (this->value >= Mod) this->value -= Mod;
	return *this;
}

template <int Mod>
ModInteger<Mod>& ModInteger<Mod>::operator -= (const ModInteger<Mod>& other) {
	this->value -= other.value;
	if (this->value < 0) this->value += Mod;
	return *this;
}

template <int Mod>
ModInteger<Mod>& ModInteger<Mod>::operator *= (const ModInteger<Mod>& other) {
	this->value = (this->value * 1LL * other.value) % Mod;
	return *this;
}

template <int Mod>
ModInteger<Mod> ModInteger<Mod>::operator + (const ModInteger<Mod>& other) const {
	ModInteger<Mod> result = *this;
	return result += other;
}

template <int Mod>
ModInteger<Mod> ModInteger<Mod>::operator - (const ModInteger<Mod>& other) const {
	ModInteger<Mod> result = *this;
	return result -= other;
}

template <int Mod>
ModInteger<Mod> ModInteger<Mod>::operator * (const ModInteger<Mod>& other) const {
	ModInteger<Mod> result = *this;
	return result *= other;
}

template <int Mod, typename U>
ModInteger<Mod> pow(ModInteger<Mod> a, U power) {
	ModInteger<Mod> result(1);
	for (; power; power >>= 1, a *= a) {
		if (power & 1) result *= a;
	}
	return result;
}

template <int Mod>
template <typename U>
ModInteger<Mod>& ModInteger<Mod>::operator ^= (U power) {
	return (*this = pow(*this, power));
}
template <int Mod>
template <typename U>
ModInteger<Mod> ModInteger<Mod>::operator ^ (U power) const {
	ModInteger<Mod> result = *this;
	return result ^= power;
}

template <int Mod>
ModInteger<Mod> ModInteger<Mod>::inverse() const {
	if (this->value < _inverses.size()) {
		return _inverses[this->value];
	}
	if (ModInteger<Mod>::PrimeModulo) {
		return pow(*this, Phi);
	}
	else {
		std::pair <long long, long long> result = gcd_ex( this->value, Mod );
		return ModInteger<Mod>(result.first);
	}
}

template <int Mod>
std::optional<int> log(const ModInteger<Mod>& a, const ModInteger<Mod>& b) {
	ModInteger<Mod> an = pow(a, ModInteger<Mod>::msqrt);
	ModInteger<Mod> pw = an;
	std::unordered_map <int, int> used;

	for (int p = 1; p <= (Mod + ModInteger<Mod>::msqrt - 1) / ModInteger<Mod>::msqrt; ++p) {
		if (used.find(pw.value) == used.end()) used[pw.value] = p;
		pw *= an;
	}
	pw = b;
	for (int q = 0; q <= ModInteger<Mod>::msqrt; ++q) {
		int cur = pw.value;
		if (used.find(cur) != used.end()) {
			int ans = used[cur] * ModInteger<Mod>::msqrt - q;
			if (ans < Mod) return ans;
		}
		pw *= a;
	}
	return std::nullopt;
}

template <int Mod>
std::optional<ModInteger<Mod>> ModInteger<Mod>::kroot(int k) const {
	static_assert(ModInteger<Mod>::PrimeModulo, "Not a prime modulo");
	static_assert(ModInteger<Mod>::G != -1, "Primitive root not found, please report to @vgzowksi");
	ModInteger<Mod> g(ModInteger<Mod>::G);
	ModInteger<Mod> gk = pow(g, k);
	auto __lg = log(gk, *this);
	if (!__lg.has_value()) return std::nullopt;
	return pow(g, __lg.value());
}

template <int Mod>
std::optional<ModInteger<Mod>> ModInteger<Mod>::sqrt() const {
	return kroot(2);
}

template <int Mod>
ModInteger<Mod>& ModInteger<Mod>::operator /= (const ModInteger<Mod>& other) {
	*this *= other.inverse();
	return *this;
}
template <int Mod>
ModInteger<Mod> ModInteger<Mod>::operator / (const ModInteger<Mod>& other) const {
	ModInteger<Mod> result = *this;
	return result /= other;
}

template <int Mod>
bool ModInteger<Mod>::operator == (const ModInteger<Mod>& other) const {
	return this->value == other.value;
}
template <int Mod>
bool ModInteger<Mod>::operator != (const ModInteger<Mod>& other) const {
	return this->value != other.value;
}
template <int Mod>
bool ModInteger<Mod>::operator < (const ModInteger<Mod>& other) const {
	return this->value < other.value;
}
template <int Mod>
bool ModInteger<Mod>::operator <= (const ModInteger<Mod>& other) const {
	return *this == other || *this < other;
}
template <int Mod>
bool ModInteger<Mod>::operator > (const ModInteger<Mod>& other) const {
	return !(*this <= other);
}
template <int Mod>
bool ModInteger<Mod>::operator >= (const ModInteger<Mod>& other) const {
	return !(*this < other);
}

template <int Mod>
void initialiseInverse(size_t n) {
	static_assert( ModInteger<Mod>::PrimeModulo );
	size_t _prev_size = ModInteger<Mod>::_inverses.size();
	ModInteger<Mod>::_inverses.resize(n + 1);

	if (!_prev_size) {
		ModInteger<Mod>::_inverses[1] = 1;
	}
	for (size_t i = std::max(2, (int)_prev_size); i <= n; ++i) {
		ModInteger<Mod>::_inverses[i] = ModInteger<Mod>::_inverses[Mod % i] * ModInteger<Mod>(Mod - Mod / i);
	}
}

/*
------------------------------------------------------------------------
*/

template <typename T>
struct IsModular { enum { value = false }; };
template <int Mod>
struct IsModular < ModInteger <Mod> > { enum { value = true }; };
