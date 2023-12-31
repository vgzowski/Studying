#include <iostream>
#include "TypeList.H"

int main() {
	static_assert(std::is_same< Front_t < TypeList<int,double> >, int>::value);
	static_assert(std::is_same< Front_t < TypeList<int> >, int>::value);

	static_assert(std::is_same< Erase_t < TypeList<int> >, NullType>::value);
	static_assert(std::is_same< Erase_t < TypeList<int, char*> >, TypeList <char*> >::value);

	static_assert(IndexOf < int, TypeList <int, double, char*> >::Result == 1);
	static_assert(IndexOf < int, TypeList <double, char*, int> >::Result == 3);
	static_assert(IndexOf < int, TypeList <double, char*> >::Result == -1);
	static_assert(IndexOf < int, TypeList <int> >::Result == 1);
	static_assert(IndexOf < int, TypeList <double, int, int, int> >::Result == 2);
}
