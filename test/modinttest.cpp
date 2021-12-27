#include "CppUTest/TestHarness.h"
#include "tmp/modint.h"
#include <iostream>

TEST_GROUP(ModintTestGroup)
{

};

TEST(ModintTestGroup, ModintTest)
{
	tmp::modint<5> C;
	const tmp::modint<5> z(0);
	std::cout << C;
	CHECK(C == z);
	std::cout << "  PASS" << std::endl;
	
	C++;
	std::cout << C;
	CHECK(C == 1);
	std::cout << "  PASS" << std::endl;
	
	C += 1;
	std::cout << C;
	CHECK(C == 2);
	std::cout << "  PASS" << std::endl;
	
	C = C + 1;
	std::cout << C;
	CHECK(C == 3);
	std::cout << "  PASS" << std::endl;
	
	C++;
	std::cout << C;
	CHECK(C == 4);
	std::cout << "  PASS" << std::endl;
	
	C++;
	std::cout << C;
	CHECK(C == z);
	std::cout << "  PASS" << std::endl;
}

