#include <iostream>
#include <string>
#include <optional>

#include "NOCache.h"
#include "LRUCache.h"
#include "FIFOCache.h"
#include "CacheContainer.h"

template <class T>
void popt( const std::optional <T> &value ) {
	if (!value.has_value()) std::cout << "No value" << std::endl;
	else std::cout << value.value() << std::endl;
}

int main() {
{
	Container
		< int, int, LRUCache, 100 >
	cont;

	cont.insert(1, 2);
	cont.insert(100, 5);
	
	auto gt1 = cont.get(1);
	auto gt2 = cont.get(5);
	cont.insert(5, 4);
	auto gt3 = cont.get(5);

	popt(gt1);
	popt(gt2);
	popt(gt3);
}
	std::cout << std::endl;
{
	Container
		< int, std::string, LRUCache, 2 >
	cont;

	cont.insert(1, "one");
	cont.insert(100, "hundred");
	
	auto gt1 = cont.get(1);
	auto gt2 = cont.get(5);

	cont.insert(5, "five");

	auto gt3 = cont.get(5);
	auto gt4 = cont.get(1);
	auto gt5 = cont.get(100);

	popt(gt1);
	popt(gt2);
	popt(gt3);
	popt(gt4);
	popt(gt5);
}
	std::cout << std::endl;
{
	Container
		< int, std::string, FIFOCache, 2 >
	cont;

	cont.insert(1, "one");
	cont.insert(100, "hundred");
	
	auto gt1 = cont.get(1);
	auto gt2 = cont.get(5);

	cont.insert(5, "five");

	auto gt3 = cont.get(5);
	auto gt4 = cont.get(1);
	auto gt5 = cont.get(100);

	popt(gt1);
	popt(gt2);
	popt(gt3);
	popt(gt4);
	popt(gt5);
}
	std::cout << std::endl;
{
	Container
		< int, std::string, NOCache, 0 >
	cont;

	cont.insert(1, "one");
	cont.insert(100, "hundred");
	
	auto gt1 = cont.get(1);
	auto gt2 = cont.get(5);

	cont.insert(5, "five");

	auto gt3 = cont.get(5);
	auto gt4 = cont.get(1);
	auto gt5 = cont.get(100);

	popt(gt1);
	popt(gt2);
	popt(gt3);
	popt(gt4);
	popt(gt5);
}
}
