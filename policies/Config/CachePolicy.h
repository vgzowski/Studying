#pragma once
#include <string>

struct LRUPolicy {
	const std::string str = "LRU";
};
struct FIFOPolicy {
	const std::string str = "FIFO";
};
struct NoCachePolicy {
	const std::string str = "No cache";
};
