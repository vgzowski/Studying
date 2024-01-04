#include <iostream>
#include "typelist.H"

int main() {
	static_assert(IndexOf < int, typelist <int, double, char*> >::value == 0);
	static_assert(IndexOf < int, typelist <double, char*, int> >::value == 2);
	static_assert(IndexOf < int, typelist <double, char*> >::value == -1);
	static_assert(IndexOf < int, typelist <int> >::value == 0);
	static_assert(IndexOf < int, typelist <double, int, int, int> >::value == 1);

	static_assert( std::is_same< typename EraseOne <int, typelist <double, char, int&, int, long>>::type,
					typelist <double, char, int&, long>>::value );
	static_assert( std::is_same< typename EraseOne <int, typelist <double, char, int&, int, int, long>>::type,
					typelist <double, char, int&, int, long>>::value );

	static_assert( std::is_same< typename Erase <int, typelist <double, char, int&, int, int, long>>::type,
					typelist <double, char, int&, long>>::value );

	static_assert( std::is_same< typename EraseDuplicates <typelist <double, char, double, double, int&, int, int, long, double, char, int&, int&>>::type,
					typelist <double, char, int&, int, long>>::value );

	static_assert( std::is_same< typename Replace <int, char, typelist <double, char, int&, int, int, long>>::type,
					typelist <double, char, int&, char, int, long>>::value );

//	static_assert( std::is_same< typename Replace <long long, char, typelist <double, char, int&, int, int, long>>::type,
//					typelist <double, char, int&, long>>::value );
//	CE (long long is not in the typelist)

	static_assert( std::is_same< typename Append <int, typelist <double, char, int&, int, long>>::type,
					typelist <double, char, int&, int, long, int>>::value );

	static_assert( std::is_same <typename Erase <int, typelist <int, int, int> >::type, NullType>::value );

	static_assert( Length <typelist <double, char, int&, int, long>>::value == 5 );
}
