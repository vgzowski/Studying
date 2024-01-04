#include <iostream>
#include "CompileTime.h"

int main() {
	std::cout << is_same<int, int>::Same << std::endl;
	std::cout << is_same<int, int*>::Same << std::endl;
	std::cout << is_same<int, const int>::Same << std::endl;
	std::cout << is_same<int, char>::Same << std::endl;
	std::cout << is_same<char*, char*>::Same << std::endl;

	st <int,2> st; st.value = 5; st.pr();
	std::cout << Phi<int,1000000000>::Result << std::endl;
	std::cout << Phi<int,1000000001>::Result << std::endl;
	std::cout << Phi<int,1000000002>::Result << std::endl;
	std::cout << Phi<int,1000000003>::Result << std::endl;
	std::cout << Phi<int,1000000004>::Result << std::endl;
	std::cout << Phi<int,1000000005>::Result << std::endl;
	std::cout << Phi<int,1000000006>::Result << std::endl;
	std::cout << Phi<int,1000000007>::Result << std::endl;
	std::cout << Phi<int,1000000008>::Result << std::endl;
	std::cout << Phi<int,1000000009>::Result << std::endl;
	std::cout << Phi<int,1000000010>::Result << std::endl;

	std::cout << Factorial::factorial<5>::Result << std::endl;
	std::cout << Factorial::factorial<6>::Result << std::endl;
	std::cout << Factorial::factorial<7>::Result << std::endl;
	std::cout << Factorial::factorial<8>::Result << std::endl;
	std::cout << Factorial::factorial<9>::Result << std::endl;
	std::cout << Factorial::factorial<10>::Result << std::endl;

	check<998244353,(int)2e5>();
}
