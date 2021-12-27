#include "CppUTest/TestHarness.h"
#include "tmp/complex.h"
#include <iostream>

TEST_GROUP(ComplexTestGroup)
{

};

TEST(ComplexTestGroup, ComplexTest)
{
	complex<int> C;
	complex<int> z(0, 0);
	std::cout << C;
	CHECK(C == z);
	std::cout << "  PASS" << std::endl;
	
	C = C+1;
	std::cout << C;
	CHECK(C == 1);
	std::cout << "  PASS" << std::endl;
	
	complex<int> D(42, 13);
	std::cout << D << std::endl;
	complex<int> E(21, 6);
	complex<int> F = D + E;
	std::cout << F;
	CHECK(F == complex<int>(63, 19));
	std::cout << "  PASS" << std::endl;
	
	#if __cplusplus >= 201103L
	complex<unsigned long long> I = 1_i;
	#else
	complex<unsigned long long> I(0, 1);
	#endif
	std::cout << I;
	CHECK(I != 1);
	std::cout << "  PASS" << std::endl;
	I += 10;
	std::cout << I;
	complex<unsigned long long> I2(10,1);
	CHECK(I == I2);
	std::cout << "  PASS" << std::endl;
}

