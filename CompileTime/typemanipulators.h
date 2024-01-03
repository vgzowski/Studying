#pragma once
#include <type_traits>

template <int Value>
struct Int2Type { enum { value = Value }; };

template <typename T>
struct Type2Type { typedef T type; };

template <typename T> struct IsReference { enum { value = false }; };
template <typename T> struct IsReference<T&> { enum { value = true }; };

template <typename T>
struct NeedToAddReference {
	enum { value = !IsReference<T>::value & !std::is_scalar<T>::value };
};

template <bool B, typename T> struct TypeChanger { typedef T type; };
template <typename T> struct TypeChanger <true, T> { typedef T& type; };

template <typename T>
struct TypeOfPassing {
	// for standart variables - by value
	// for references - by refernece (as &&T is forbidden in C++
	// for other types - by reference
	typedef typename TypeChanger < NeedToAddReference <T> :: value, T >::type type_t;
};
template <typename T>
using typePass_t = typename TypeOfPassing<T>::type_t;
