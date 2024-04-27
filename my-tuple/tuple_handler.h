#pragma once

/*
Classes representing tuple of one element
*/

/* Generic implementation */
template <
	int Index,
	class T
>
class tuple_handler {
public:
	tuple_handler(const T& obj) : value(obj) { std::cout << "COPY" << '\n'; }
	tuple_handler(T&& obj) : value(std::move(obj)) { std::cout << "MOVE" << '\n'; }
	T& get() {
		return value;
	}
private:
	T value;
};

/* Implementation for references */
template <
	int Index,
	class T
>
class tuple_handler <Index, T&> {
public:
	tuple_handler(T& obj) : value(obj) { std::cout << "COPY_ref" << '\n'; }
	T& get() {
		return value;
	}
private:
	T& value;
};
