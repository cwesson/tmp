#include "minint.h"
#include <iostream>

int main(){
	std::cout << "1 " << minint<1>::Result << " " << sizeof(minint<1>::DataType) << std::endl;
	std::cout << "255 " << minint<255>::Result << " " << sizeof(minint<255>::DataType) << std::endl;
	std::cout << "256 " << minint<256>::Result << " " << sizeof(minint<256>::DataType) << std::endl;
	std::cout << "300 " << minint<300>::Result << " " << sizeof(minint<300>::DataType) << std::endl;
	std::cout << "65535 " << minint<65535>::Result << " " << sizeof(minint<65535>::DataType) << std::endl;
	std::cout << "65536 " << minint<65536>::Result << " " << sizeof(minint<65536>::DataType) << std::endl;
	std::cout << "66000 " << minint<66000>::Result << " " << sizeof(minint<66000>::DataType) << std::endl;
	std::cout << "5000000000 " << minint<5000000000>::Result << " " << sizeof(minint<5000000000>::DataType) << std::endl;
	std::cout << "900000000000000000 " << minint<900000000000000000>::Result << " " << sizeof(minint<900000000000000000>::DataType) << std::endl;
	return 0;
}

