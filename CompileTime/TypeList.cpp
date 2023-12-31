#include <iostream>
#include <cassert>

/* EMPTY TYPELIST */
struct NullType;

/* DEFINITION OF TYPELIST */
template <typename... Types>
struct TypeList;

template <typename U>
struct Front;

template <typename Head, typename... Tail>
struct Front < TypeList < Head, Tail... > > {
	using Type = Head;
};

template <typename List>
using Front_t = typename Front < List > :: Type;

/* DEFINITION OF POPPING THE FIRST ELEMENT */
template <typename U>
struct Erase;

template <typename Head, typename... Tail>
struct Erase < TypeList < Head, Tail... > > {
	using Type = TypeList <Tail...>;
};
template <typename Head>
struct Erase  < TypeList <Head> > {
	using Type = NullType;
};
template <typename List>
using Erase_t = typename Erase < List > :: Type;

/* DEFINITION OF GETTING THE INDEX OF A TYPE */

template <typename U, typename V>
struct IndexOf;

template <typename T, typename... Types>
struct IndexOf < T, TypeList < Types... > > {
	static constexpr int Result =
		std::is_same < T, Front_t < TypeList <Types...> > >::value ? 1
		: IndexOf < T, Erase_t < TypeList <Types...> > >::Result == -1 ? -1
		: 1 + IndexOf < T, Erase_t < TypeList <Types...> > >::Result;
};
template <typename T>
struct IndexOf <T, NullType> {
	static constexpr int Result = -1;
};

int main() {
	static_assert(std::is_same< Front_t < TypeList<int,double> >, int>::value);
	static_assert(std::is_same< Front_t < TypeList<int> >, int>::value);

	static_assert(IndexOf < int, TypeList <int, double, char*> >::Result == 1);
	static_assert(IndexOf < int, TypeList <double, char*, int> >::Result == 3);
	static_assert(IndexOf < int, TypeList <double, char*> >::Result == -1);
	static_assert(IndexOf < int, TypeList <int> >::Result == 1);
	static_assert(IndexOf < int, TypeList <double, int, int, int> >::Result == 2);
}
