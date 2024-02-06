#pragma once
#include <list>
#include <unordered_map>

template <
	class key_t,
	int MAX_SIZE = 0
>
class NOCache {
public:
	static_assert(MAX_SIZE == 0);
	typedef key_t* iterator;

	NOCache() {}
	bool full() const {
		return true;
	}
	bool present(const key_t& key) {
		return false;
	}

	iterator latest() const {
		return &default_key;
	}

	bool refer(const key_t& key) {
		return false;
	}
private:
	static inline key_t default_key = key_t();
};
