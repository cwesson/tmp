
#include <assert.h>
#include <iostream>
#include "qformat.h"

int main(){
	Q3_13 a(3.14159);
	assert(sizeof(a) == 2);
	double d = a;
	std::cout << d << "  PASS" << std::endl;
	
	a *= 2;
	d = a;
	std::cout << d << "  PASS" << std::endl;
	
	a /= 2;
	d = a;
	std::cout << d << "  PASS" << std::endl;
	
	return 0;
}

