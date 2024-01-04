#pragma once

template <class A, class B>
struct is_same { enum { value = false }; };
template <class A>
struct is_same <A, A> { enum { value = true }; }; // HELPER is_same<A, B> is true iff type A == type B

struct NullType; // DEFINITOIN OF EMPTY TYPELIST

template <class V, class U> // DEFINITION OF TYPELIST
struct TypeList {
	typedef V Head;
	typedef U Tail;
};

template <class T> // LENGTH OF TYPELIST
struct Length;

template <>
struct Length < NullType > {
	enum { value = 0 };
};

template <class Head, class Tail>
struct Length < TypeList <Head, Tail> > {
	enum { value = 1 + Length <Tail>::value };
};

template <int Index, class T> // GETTING TYPE AT INDEX <Index> IN THE TYPELIST
struct TypeIndex;

template <int Index>
struct TypeIndex <Index, NullType> {
	typedef NullType type;
};
template <class Head, class Tail>
struct TypeIndex < 0, TypeList <Head, Tail> > {
	typedef Head type;
};
template <int Index, class Head, class Tail>
struct TypeIndex < Index, TypeList <Head, Tail> > {
	typedef typename TypeIndex< Index - 1, Tail>::type type;
};

template <class T, class V> // GETTING INDEX OF A TYPE IN THE TYPPELIST
struct IndexOf;

template <class T>
struct IndexOf < T, NullType > {
	enum { value = -1 };
};
template <class T, class Head, class Tail>
struct IndexOf < T, TypeList <Head, Tail> > {
	enum { value = 
		is_same<T, Head>::value ? 0 : 
		IndexOf<T, Tail>::value == -1 ? -1 : 1 + IndexOf<T, Tail>::value
	};
};

template <class T, class V> // APPENDING AN ELEMENT TO A TYPELIST
struct Append;

template <class T>
struct Append <T, NullType> {
	typedef TypeList <T, NullType> type;
};

template <class T, class Head, class Tail>
struct Append < T, TypeList <Head, Tail> > {
	typedef TypeList < Head, typename Append <T, Tail>::type > type;
};

template <class T, class V> // ERASING ALL OCCURANCES OF A TYPE IN THE TYPELIST
struct Erase;

template <class T>
struct Erase < T, NullType > {
	typedef NullType type;
};

template <class T, class Tail>
struct Erase < T, TypeList <T, Tail> > {
	typedef typename Erase <T, Tail>::type type;
};

template <class T, class Head, class Tail>
struct Erase < T, TypeList <Head, Tail> > {
	typedef TypeList < Head, typename Erase <T, Tail>::type > type;
};

template <class T, class V> // SAME AS ERASE, BUT DELETES ONLY THE FIRST OCCURANCE
struct EraseOne;

template <class T>
struct EraseOne < T, NullType > {
	typedef NullType type;
};

template <class T, class Tail>
struct EraseOne < T, TypeList <T, Tail> > {
	typedef Tail type;
};

template <class T, class Head, class Tail>
struct EraseOne < T, TypeList <Head, Tail> > {
	typedef TypeList < Head, typename EraseOne <T, Tail>::type > type;
};

template <class T> // REMOVES DUPLICATES FROM THE TYPELIST
struct EraseDuplicates;

template <>
struct EraseDuplicates < NullType > {
	typedef NullType type;
};

template <class Head, class Tail>
struct EraseDuplicates < TypeList <Head, Tail> > {
	typedef TypeList < Head, typename EraseDuplicates < typename Erase <Head, Tail>::type >::type > type;
};

template <class A, class B, class T> // REPLACES FIRST OCCURANCE OF A TO B (CE IF A IS NOT PRESENT)
struct Replace;

template <class A, class B, class Tail>
struct Replace < A, B, TypeList <A, Tail> > {
	typedef TypeList <B, Tail> type;
};

template <class A, class B, class Head, class Tail>
struct Replace < A, B, TypeList <Head, Tail> > {
	typedef TypeList <Head, typename Replace <A, B, Tail>::type> type;
};

template <class... Args>
struct typelist_t;

template <class Head>
struct typelist_t <Head> {
	typedef TypeList <Head, NullType> type;
};
template <class Head, class... Tail>
struct typelist_t <Head, Tail...> {
	typedef TypeList <Head, typename typelist_t <Tail...>::type > type;
};
template <class ...Args>
using typelist = typename typelist_t <Args...>::type;
