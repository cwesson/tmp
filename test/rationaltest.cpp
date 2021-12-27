#include "CppUTest/TestHarness.h"
#include "tmp/rational.h"
#include <iostream>

TEST_GROUP(RationalTestGroup)
{

};

TEST(RationalTestGroup, RationalTest)
{
	rational<int> C;
	rational<int> z(0, 1);
	std::cout << C;
	CHECK(C == z);
	std::cout << "  PASS" << std::endl;
	
	C = C+1;
	std::cout << C;
	CHECK(C == 1);
	std::cout << "  PASS" << std::endl;
	
	rational<int> D(42, 13);
	
	std::cout << D << std::endl;
	
	D += 10;
	std::cout << D << std::endl;
	
	rational<int> R1(48, 18);
	rational<int> R2(8, 3);
	std::cout << R1;
	CHECK(R1 == R2);
	std::cout << "  PASS" << std::endl;
	
	rational<int> One(1);
	rational<int> third = One/3;
	std::cout << third << std::endl;
	
	third *= 9;
	std::cout << third;
	CHECK(third == 3);
	std::cout << "  PASS" << std::endl;
}
