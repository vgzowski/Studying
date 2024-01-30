#pragma once
#include <string>

struct ThrowREPolicy {
	const std::string str = "Runtime error";
};
struct WarningPolicy {
	const std::string str = "CERR Warning";
};
struct NoErrorPolicy {
	const std::string str = "No Error";
};
