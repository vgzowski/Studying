#pragma once
#include "ErrorPolicies.h"

template <
	class T,
	typename ErrorPolicy = ThrowRuntimeErrorPolicy
>
struct SafeVectorEraser {
	static void erase(std::vector <T>& values, const T& obj) {
		std::vector <T>::iterator __it = lower_bound(values.begin(),
							values.end(),
							obj);
		ErrorPolicy::error_check( __it != values.end() && __it->first == obj, "Element not in vector" );
		values.erase(__it);
	}
};

template <class T>
struct ForceVectorEraser {
	static void erase(std::vector <T>& values, const T& obj) {
		values.erase(lower_bound(values.begin(), values.end(), obj));
	}
};

