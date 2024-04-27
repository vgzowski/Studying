#pragma once

/* Extracting i-th type out of typenames list */

template <
	int Index,
	class T,
	class... Args
>
struct typer {
	typedef typename typer <Index - 1, Args...>::type type;
};
template <
	class T,
	class... Args
>
struct typer <0, T, Args...> {
	typedef T type;
};

template <
	int Index,
	class... Args
>
using typer_t = typename typer <Index, Args...>::type;
