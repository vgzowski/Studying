#include <iostream>
#include <vector>
#include "typemanipulators.h"

int main() {
	struct Foo {
		int a, b;
	};

	static_assert( !IsReference<int>::value );
	static_assert( IsReference<int&>::value );
	static_assert( !IsReference<const int>::value );
	static_assert( !IsReference<Foo>::value );
	static_assert( IsReference<const Foo&>::value );

	static_assert( std::is_scalar<int>::value );

	static_assert( !NeedToAddReference<int>::value );
	static_assert( !NeedToAddReference<int&>::value );
	static_assert( !NeedToAddReference<const int>::value );
	static_assert( NeedToAddReference<std::vector <int>>::value );
	static_assert( NeedToAddReference<Foo>::value );
	static_assert( !NeedToAddReference<const Foo&>::value );

	static_assert( std::is_same < typePass_t<int>, int >::value );
	static_assert( std::is_same < typePass_t<const int>, const int >::value );
	static_assert( std::is_same < typePass_t<Foo>, Foo& >::value );
	static_assert( std::is_same < typePass_t<const Foo &>, const Foo & >::value );
	static_assert( std::is_same < typePass_t< std::vector <char*> >, std::vector <char*> & >::value );
}
