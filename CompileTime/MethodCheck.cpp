#include <iostream>
#include <type_traits>

struct A {
	int a, b, c;
	int foo() { std::cout << "A::foo()" << std::endl; return 0; }
};
struct B {
	int a;
	char foo() { std::cout << "B::foo()" << std::endl; return 'a'; }
};
struct C {
	std::string str;
	void foo() { std::cout << "C::foo()" << std::endl; return; }
};
struct D {
	std::string a;
	void bar() { std::cout << "D::bar()" << std::endl; return; }
};

template <bool B, typename T>
struct enable_if {};

template <typename T>
struct enable_if <true,T> { typedef T type; };

namespace check {
	template <class T>
	constexpr auto test(T* ptr) -> decltype(ptr->foo(), std::true_type{}) {}
	template <class>
	constexpr auto test(...) -> std::false_type;
}
template <class T>
struct hasFoo {
	static constexpr int value =
		decltype(check::test<T>(nullptr))::value;
};

template <class T>
typename enable_if< hasFoo<T>::value, void >::type
print(T x) {
	x.foo();
}
template <class T>
typename enable_if< !hasFoo<T>::value, void >::type
print(T x) {
	std::cout << "No foo method" << std::endl;
}

int main() {
	static_assert(hasFoo<A>::value);
	static_assert(hasFoo<B>::value);
	static_assert(hasFoo<C>::value);
	static_assert(!hasFoo<D>::value);
	static_assert(!hasFoo<int>::value);
	static_assert(!hasFoo<std::string>::value);

	{A x; print(x);}
	{B x; print(x);}
	{C x; print(x);}
	{D x; print(x);}
	{int x; print(x);}
	{std::string x; print(x);}
}
