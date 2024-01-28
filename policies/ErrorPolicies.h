#pragma once
struct ThrowNoErrorPolicy {
	static void error_check(const bool& expr, const string& message = "Error") {}
};
struct ThrowRuntimeErrorPolicy {
	static void error_check(const bool& expr, const string& message = "Error") {
		if (!expr) {
			throw std::runtime_error(message);
		}
	}
};

