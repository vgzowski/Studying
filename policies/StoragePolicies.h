#pragma once
#include "VectorEraserPolicies.h"

template <
	class A,
	class B,
	typename VectorEraserPolicy = SafeVectorEraser < std::make_pair <A, B> >
>
class VectorStoringPolicy {
private:
	std::vector < std::pair <A, B> > values;
public:
	typedef std::vector < std::pair <A, B> >::iterator iterator_t;

	iterator_t find(const A& __key) const {
		for (iterator_t it = values.begin(); it != values.end(); ++it) {
			if (it->first == __key) return it;
		}
		return values.end();
	}
	std::pair <A, B> front() const {
		return *values.begin();
	}
	sdt::pair <A, B> back() const {
		return *--values.end();
	}
	size_t size() const {
		return values.size();
	}

	void erase(const A& __key) {
		values.erase(find(__key));
	}
	void push_back(const A& __key, const B& __value) {
		values.emplace_back( __key, __value );
	}
	void push_front(const A& __key, const B& __value) {
		values.insert(0, std::make_pair( __key, __value ));
	}
	void pop_back() {
		values.pop_back();
	}
	void pop_front() {
		values.erase(values.begin());
	}

	void set(const A& __key, const B& __value) {
		iterator_t it = find(__key);
		if (it != values.end()) it->second = __value;
		else push_front( __key, __value );
	}

	iterator_t end() const { return values.end(); }
	iterator_t begin() const { return values.begin(); }
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
