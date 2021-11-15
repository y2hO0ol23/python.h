#pragma once
#include <Windows.h>
#include <iostream>

namespace py {
	void ValueError(const char* err_message) {
		std::cout << "ValueError: " << err_message;
		exit(-1);
	}
	void IndexError(const char* err_message) {
		std::cout << "IndexError: " << err_message;
		exit(-1);
	}
	void TypeError(const char* err_message) {
		std::cout << "TypeError: " << err_message;
		exit(-1);
	}
}