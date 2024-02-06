#pragma once
#include <list>
#include <unordered_map>

template <
	class key_t,
	int MAX_SIZE
>
class FIFOCache {
public:
	static_assert(MAX_SIZE > 0);
	typedef typename std::list < key_t >::const_iterator iterator;

	FIFOCache() : sz_(0) {}

	bool full() const {
		return cache_.size() == MAX_SIZE;
	}
	bool present(const key_t& key) {
		return iters_.find(key) != iters_.end();
	}

	iterator latest() const {
		return --cache_.end();
	}

	void refer(const key_t& key) {
		if (!present(key)) {
			if (full()) {
				iterator last = latest();
				iters_.erase(*last);
				cache_.erase(last);
			}

			cache_.push_front(key);
			iters_[key] = cache_.begin();
		}
	}
private:
	std::list < key_t > cache_;
	std::unordered_map < key_t, iterator > iters_;
	int sz_;
};
