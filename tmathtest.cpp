
#include <assert.h>
#include <iostream>
#include "tmath.h"

int tmathtest(){
	std::cout << "max(5, 2, 9, 1, 3, 4)";
	assert(max(5, 2, 9, 1, 3, 4) == 9);
	std::cout << "  PASS" << std::endl;
	
	std::cout << "min(5, 2, 9, 1, 3, 4)";
	assert(min(5, 2, 9, 1, 3, 4) == 1);
	std::cout << "  PASS" << std::endl;
	
	std::cout << "max(2, 6, 3, 8)";
	assert(max(2, 6, 3, 8) == 8);
	std::cout << "  PASS" << std::endl;
	
	std::cout << "min(2, 6, 3, 8)";
	assert(min(2, 6, 3, 8) == 2);
	std::cout << "  PASS" << std::endl;
	
	std::cout << "sum(5, 3, 4, 6)";
	assert(sum(5, 3, 4, 6) == 18);
	std::cout << "  PASS" << std::endl;
	
	std::cout << "product(5, 3, 4, 6)";
	assert(product(5, 3, 4, 6) == 360);
	std::cout << "  PASS" << std::endl;
	
	return 0;
}

