#include "CppUTest/TestHarness.h"
#include "tmp/tmath.h"
#include <iostream>

TEST_GROUP(TmathTestGroup)
{

};

TEST(TmathTestGroup, TmathTest)
{
	std::cout << "max(5, 2, 9, 1, 3, 4)";
	CHECK_EQUAL(9, tmp::max(5, 2, 9, 1, 3, 4));
	std::cout << "  PASS" << std::endl;
	
	std::cout << "min(5, 2, 9, 1, 3, 4)";
	CHECK_EQUAL(1, tmp::min(5, 2, 9, 1, 3, 4));
	std::cout << "  PASS" << std::endl;
	
	std::cout << "max(2, 6, 3, 8)";
	CHECK_EQUAL(8, tmp::max(2, 6, 3, 8));
	std::cout << "  PASS" << std::endl;
	
	std::cout << "min(2, 6, 3, 8)";
	CHECK_EQUAL(2, tmp::min(2, 6, 3, 8));
	std::cout << "  PASS" << std::endl;
	
	std::cout << "sum(5, 3, 4, 6)";
	CHECK_EQUAL(18, tmp::sum(5, 3, 4, 6));
	std::cout << "  PASS" << std::endl;
	
	std::cout << "product(5, 3, 4, 6)";
	CHECK_EQUAL(360, tmp::product(5, 3, 4, 6));
	std::cout << "  PASS" << std::endl;
}

