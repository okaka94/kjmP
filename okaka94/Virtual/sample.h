#pragma once
#include <iostream>
#include "child.h"
class sample
{
public:
	child m_c;
	void test() {
		std::cout << "parent" << std::endl;
	}
};

