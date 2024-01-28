#pragma once
#include "VectorEraserPolicies.h"

template <
	class A,
	class B,
	typename VectorEraserPolicy = SafeVectorEraser
>
class VectorStoringPolicy {
private:
	std::vector < std::pair <A, B> > values;
public:
	void __insert(const A& __key, const B& __value) { values.emplace_back(__key, __value); }
	void __erase(const A& __key) { VectorEraserPolicy::erase( values, std::make_pair( __key, B() ) ); }

	B __get_by_key(const A& __key) {
		for (size_t i = 0; i < values.size(); ++i) {
			if (values[i].first == __key) return __values[i].second;
		}
		return B();
	}
	bool __is_present(const A& __key) {
		for (size_t i = 0; i < values.size(); ++i) {
			if (values[i].first == __key) return true;
		}
		return false;
	}
};

template <
	class A,
	class B
>
class MapStoringPolicy {
private:
	std::map <A, B> values;
public:
	void __insert(const A& __key, const B& __value) { values[A] = B; }
	void __erase(const A& __key) { values.erase(__key); }
	B __get_by_key(const A& __key) {
		return values.count(__key) ? values[__key] : B();
	}
	bool __is_present(const A& __key) {
		return values.count(__key);
	}
};

template <
	class A,
	class B
>
class MapStoringPolicy {
private:
	std::unordered_map <A, B> values;
public:
	void __insert(const A& __key, const B& __value) { values[A] = B; }
	void __erase(const A& __key) { values.erase(__key); }
	B __get_by_key(const A& __key) {
		return values.count(__key) ? values[__key] : B();
	}
	bool __is_present(const A& __key) {
		return values.count(__key);
	}
};

template <
	class A,
	class B
>
class SingleElementPolicy {
private:
	A key;
	B value;
public:
	void __insert(const A& __key, const B& __value) {
		key = __key;
		value = __value;
	}
	void __erase(const A& __key) {
	}
	B __get_by_key(const A& __key) {
		return (__key == key ? value : B());
	}
	bool __is_present(const A& __key) {
		return (__key == key);
	}
};
