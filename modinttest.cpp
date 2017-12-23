
#include <assert.h>
#include <iostream>
#include "modint.h"

int modinttest(){
	modint<5> C;
	modint<5> z(0);
	std::cout << C;
	assert(C == z);
	std::cout << "  PASS" << std::endl;
	
	C++;
	std::cout << C;
	assert(C == 1);
	std::cout << "  PASS" << std::endl;
	
	C += 1;
	std::cout << C;
	assert(C == 2);
	std::cout << "  PASS" << std::endl;
	
	C = C + 1;
	std::cout << C;
	assert(C == 3);
	std::cout << "  PASS" << std::endl;
	
	C++;
	std::cout << C;
	assert(C == 4);
	std::cout << "  PASS" << std::endl;
	
	C++;
	std::cout << C;
	assert(C == z);
	std::cout << "  PASS" << std::endl;
	
	return 0;
}

