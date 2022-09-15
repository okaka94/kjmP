#include "sample.h"
#include <iostream>
#include <vector>


int main() {
	std::vector<int*> test;

	int* a = new int;
	*a = 1;
	int* b = new int;
	*b = 2;
	int* c = new int;
	*c = 3;
	

	test.push_back(a);
	test.push_back(b);
	test.push_back(nullptr);
	test.push_back(b);
	test.push_back(nullptr);
	test.push_back(b);
	test.push_back(c);
	test.push_back(nullptr);
	
	std::cout << *test[0] << std::endl;
	std::cout << *test[1] << std::endl;
	//std::cout << *test[2] << std::endl;
	std::cout << *test[3] << std::endl;
	//std::cout << *test[4] << std::endl;

	if (test[0]	!= nullptr){				//*test[0] != NULL) {
		delete test[0];
		//test[0] = nullptr;
	}
		
	if (test[1] != nullptr) {
		delete test[1];
		//test[1] = nullptr;
	}
		
	if (test[2] != nullptr) {
		delete test[2];
		//test[2] = nullptr;
	}
		
	if (test[3] != nullptr) {
		delete test[3];
		//test[3] = nullptr;
	}
		
	if (test[4] != nullptr) {
		delete test[4];
		//test[4] = nullptr;
	}
		

	return 0;
}