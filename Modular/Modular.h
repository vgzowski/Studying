#pragma once

#ifndef __MODULAR_INCLUDE
#define __MODULAR_INCLUDE

#include <iostream>

template <int Number>
struct IsPrime {
	static constexpr bool __check() {
		for (int i = 2; i * i <= Number; ++i) {
			if (Number % i == 0) return false;
		}
		return true;
	}
	enum { value = __check() };
};

template <int Mod>
class ModInteger {
private:
	int value;
	static constexpr bool PrimeModulo = IsPrime<Mod>::value;

	static std::pair <long long, long long> gcd_ex(const int &a, const int &b) {
		if (!b) return std::make_pair(1, 0);
		std::pair <long long, long long> result = gcd_ex(b, a % b);
		return std::make_pair( result.second - (a / b) * result.first, result.first );
	}
public:
	template <int ModU> friend std::istream & operator >> (std::istream &, ModInteger<ModU> &);
	template <int ModU> friend std::ostream & operator << (std::ostream &, const ModInteger<ModU> &);

	ModInteger() { value = int(0); }
	ModInteger(int x) { value = (x % Mod + Mod) % Mod; }
	ModInteger(long long x) { value = (x % Mod + Mod) % Mod; }

	ModInteger& operator += (const ModInteger& other);
	ModInteger operator + (const ModInteger& other) const;
	ModInteger& operator -= (const ModInteger& other);
	ModInteger operator - (const ModInteger& other) const;
	ModInteger& operator *= (const ModInteger& other);
	ModInteger operator * (const ModInteger& other) const;
	ModInteger& operator /= (const ModInteger& other);
	ModInteger operator / (const ModInteger& other) const;

	ModInteger operator - () const;

	template <int M> friend ModInteger<M> abs(const ModInteger<M> &);

	template <typename U> ModInteger<Mod>& operator ^= (U power);
	template <typename U> ModInteger<Mod> operator ^ (U power) const;

	ModInteger inverse() const;

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
ModInteger<Mod> ModInteger<Mod>::operator + (const ModInteger<Mod>& other) const {
	ModInteger<Mod> result = *this;
	result += other;
	return result;
}

template <int Mod>
ModInteger<Mod>& ModInteger<Mod>::operator -= (const ModInteger<Mod>& other) {
	this->value -= other.value;
	if (this->value < 0) this->value += Mod;
	return *this;
}
template <int Mod>
ModInteger<Mod> ModInteger<Mod>::operator - (const ModInteger<Mod>& other) const {
	ModInteger<Mod> result = *this;
	result -= other;
	return result;
}

template <int Mod>
ModInteger<Mod>& ModInteger<Mod>::operator *= (const ModInteger<Mod>& other) {
	this->value = (this->value * 1LL * other.value) % Mod;
	return *this;
}
template <int Mod>
ModInteger<Mod> ModInteger<Mod>::operator * (const ModInteger<Mod>& other) const {
	ModInteger<Mod> result = *this;
	result *= other;
	return result;
}

template <int Mod>
template <typename U>
ModInteger<Mod>& ModInteger<Mod>::operator ^= (U power) {
	ModInteger<Mod> result(1);
	for (; power; power >>= 1, *this *= *this) {
		if (power & 1) {
			result *= *this;
		}
	}
	return (*this = result);
}
template <int Mod>
template <typename U>
ModInteger<Mod> ModInteger<Mod>::operator ^ (U power) const {
	ModInteger<Mod> result = *this;
	result ^= power;
	return result;
}

template <int Mod>
ModInteger<Mod> ModInteger<Mod>::inverse() const {
	if (ModInteger<Mod>::PrimeModulo) {
		return *this ^ (Mod - 2);
	}
	else {
		std::pair <long long, long long> result = gcd_ex( this->value, Mod );
		return ModInteger<Mod>(result.first);
	}
}

template <int Mod>
ModInteger<Mod>& ModInteger<Mod>::operator /= (const ModInteger<Mod>& other) {
	*this *= other.inverse();
	return *this;
}
template <int Mod>
ModInteger<Mod> ModInteger<Mod>::operator / (const ModInteger<Mod>& other) const {
	ModInteger<Mod> result = *this;
	result /= other;
	return result;
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

/*
------------------------------------------------------------------------
*/

template <typename T>
struct IsModular { enum { value = false }; };
template <int Mod>
struct IsModular < ModInteger <Mod> > { enum { value = true }; };

#endif
