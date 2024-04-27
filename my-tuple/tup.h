#pragma once
#include "typer.h"
#include "tuple_handler.h"

template <
	int Index,
	class... Args
>
class tuple_recursive {};

template <
	int Index,
	class T,
	class... Rest
>
class tuple_recursive <Index, T, Rest...> :
	public
		tuple_handler <Index, T>,
	public
		tuple_recursive <Index + 1, Rest...>
{
public:
	template <
		class V,
		class... U
	>
	tuple_recursive(V&& head_obj, U&&... rest_obj) :
		tuple_handler <Index, T> ( std::forward <V> (head_obj) ),
		tuple_recursive < Index + 1, Rest... > ( std::forward <U> (rest_obj)... ) {}
};

template <
	class T,
	class... Rest
>
class tup : public tuple_recursive <0, T, Rest...> {
public:
	template <
		class... V
	>
	tup(V&&... args) : tuple_recursive <0, T, Rest...> ( std::forward <V> (args)... ) {}
};

template <class... Args>
tup(Args...) -> tup <Args...>;

template <
	int Index,
	class... Args
>
auto& get_val(tup < Args... > &tuple) {
	return ( static_cast < tuple_handler < Index, typer_t < Index, Args... > >& > (tuple) ).get();
}
