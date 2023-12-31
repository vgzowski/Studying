#pragma once
#ifndef __TYPELIST_INCLUDE
#define __TYPELIST_INCLUDE
#endif

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
