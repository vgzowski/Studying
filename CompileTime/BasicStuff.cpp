#include <iostream>
#include <cassert>

template <typename T, typename U>
struct is_same { enum { Same = false }; };
template <typename T>
struct is_same<T, T> { enum { Same = true }; };

template <typename T, T X>
struct st {
	T value;
	void pr() {
		std::cout << X + value << std::endl;
	}
};

int main() {
	std::cout << is_same<int, int>::Same << std::endl;
	std::cout << is_same<int, int*>::Same << std::endl;
	std::cout << is_same<int, const int>::Same << std::endl;
	std::cout << is_same<int, char>::Same << std::endl;
	std::cout << is_same<char*, char*>::Same << std::endl;

	st <int,2> st; st.value = 5; st.pr();
}
