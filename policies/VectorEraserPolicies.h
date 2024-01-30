#pragma once
#include "ErrorPolicies.h"

template <
	class T
>
struct LinearVectorSearch {
	static std::vector<T>::iteartor search(const std::vector <T>& values, const T& obj) {
		for (std::vector<T>::iterator it = values.begin(); it != values.end(); ++it) {
			if ((*it) == obj) return it;
		}
		return values.end();
	}
};

template <
	class T
}
struct BinaryVectorSearch {
	static std::vector<T>::iteartor search(const std::vector <T>& values, const T& obj) {
		std::vector <T>::iterator it = lower_bound(values.begin(), values.end(), obj);
		if (it != values.end() && (*it) == obj) {
			return it;
		}
		return values.end();
	}
};

template <
	class T,
	typename SearchPolicy,
	typename ErrorPolicy
>
struct SafeVectorEraser {
	static void erase(std::vector <T>& values, const T& obj) {
		std::vector <T>::iterator __it = SearchPolicy::search( values, obj );
		ErrorPolicy::error_check( __it != values.end() && __it->first == obj, "Element not in vector" );
		values.erase(__it);
	}
};

template <class T>
struct ForceVectorEraser {
	static void erase(std::vector <T>& values, const T& obj) {
		values.erase( SearchPolicy::search( values, obj ) );
	}
};
