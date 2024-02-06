#pragma once
#include <optional>
#include <unordered_map>

template <
	class key_t,
	class value_t,
	template <class, int> class CachePolicy,
	int MAX_SIZE
>
class Container {
public:
	void insert( const key_t& key, const value_t& value ) {
		if (cache_.full() && !cache_.present(key)) {
			iterator latest = cache_.latest();
			values_.erase(*latest);
		}
		cache_.refer( key );
		values_[key] = value;
	}
	std::optional < value_t > get( const key_t& key ) {
		if (cache_.present(key)) {
			cache_.refer(key);
			return std::optional < value_t > {values_[key]};
		}
		else {
			return std::nullopt;
		}
	}
private:
	CachePolicy < key_t, MAX_SIZE > cache_;
	std::unordered_map < key_t, value_t > values_;
	typedef typename CachePolicy < key_t, MAX_SIZE>::iterator iterator;
};
