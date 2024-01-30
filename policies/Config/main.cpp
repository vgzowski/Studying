#include <iostream>
#include "RuntimeCreator.h"
#include "ObjectCreator.h"
#include "config.h"

int main() {
	{
		config c{"Fixed", "None", "RE"};
		std::unique_ptr < ICreator > runner = create(c);
		runner->print();
		std::cout << std::endl << std::endl;
	}
	{
		config c{"Dynamic", "LRU", "Warning"};
		std::unique_ptr < ICreator > runner = create(c);
		runner->print();
		std::cout << std::endl << std::endl;
	}
	{
		config c{"One", "FIFO", "Warning"};
		std::unique_ptr < ICreator > runner = create(c);
		runner->print();
		std::cout << std::endl << std::endl;
	}

/*
	THIS PART EXPECTEDLY GIVES RE DUE TO UNKNOWN ERROR POLICY
	{
		config c{"One", "FIFO", "AJAKLSD"};
		std::unique_ptr < ICreator > runner = create(c);
		runner->print();
		std::cout << std::endl << std::endl;
	}
*/
}
