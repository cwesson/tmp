
#include <assert.h>
#include <iostream>
#include "rational.h"

int rationaltest(){
	rational<int> C;
	rational<int> z(0, 1);
	std::cout << C;
	assert(C == z);
	std::cout << "  PASS" << std::endl;
	
	C = C+1;
	std::cout << C;
	assert(C == 1);
	std::cout << "  PASS" << std::endl;
	
	rational<int> D(42, 13);
	
	std::cout << D << std::endl;
	
	D += 10;
	std::cout << D << std::endl;
	
	rational<int> R1(48, 18);
	rational<int> R2(8, 3);
	std::cout << R1;
	assert(R1 == R2);
	std::cout << "  PASS" << std::endl;
	
	rational<int> One(1);
	rational<int> third = One/3;
	std::cout << third << std::endl;
	
	third *= 9;
	std::cout << third;
	assert(third == 3);
	std::cout << "  PASS" << std::endl;
	
	return 0;
}

