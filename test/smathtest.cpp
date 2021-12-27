#include "CppUTest/TestHarness.h"
#include "tmp/smath.h"
#include <iostream>

TEST_GROUP(SmathTestGroup)
{

};

TEST(SmathTestGroup, SmathLogTest)
{
	std::cout << "log(63)=" << tmp::smath<63>::log << std::endl;
	CHECK_EQUAL(6, (tmp::smath<63>::log));

	std::cout << "log2(20)=" << tmp::smath<20, 2>::log << std::endl;
	CHECK_EQUAL(5, (tmp::smath<20, 2>::log));

	std::cout << "log2(3)=" << tmp::smath<3, 2>::log << std::endl;
	CHECK_EQUAL(2, (tmp::smath<3, 2>::log));

	std::cout << "log3(20)=" << tmp::smath<20, 3>::log << std::endl;
	CHECK_EQUAL(2, (tmp::smath<20, 3>::log));
}
