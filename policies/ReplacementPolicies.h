#pragma once

template <
	class A,
	class B,
	typename KVStoringPolicy,
	typename TMStoringPolicy
>
class LRU {
public:
	B refer(const A& key) {
		order::iterator_t it = order.find(key);
		if (it == order.end()) return B();

		B value = it->second->second;
		keys.set();
		return value;
	}
	void update(const A& key, const B& value) {

	}
private:
	KVStroingPolicy <A, B> keys;
	TMStoringPolicy <A, keys::iterator_t> order;
};
