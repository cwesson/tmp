#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "tmp/minint.h"
#include <iostream>

TEST_GROUP(MinintTestGroup)
{

};

TEST(MinintTestGroup, SizeTest)
{
	std::cout << "1 " << tmp::minint<1>::result << " " << sizeof(tmp::minint<1>::type) << std::endl;
	CHECK_EQUAL(1, tmp::minint<1>::result);
	CHECK_EQUAL(1, sizeof(tmp::minint<1>::type));

	std::cout << "255 " << tmp::minint<255>::result << " " << sizeof(tmp::minint<255>::type) << std::endl;
	CHECK_EQUAL(1, tmp::minint<255>::result);
	CHECK_EQUAL(1, sizeof(tmp::minint<255>::type));

	std::cout << "256 " << tmp::minint<256>::result << " " << sizeof(tmp::minint<256>::type) << std::endl;
	CHECK_EQUAL(2, tmp::minint<256>::result);
	CHECK_EQUAL(2, sizeof(tmp::minint<256>::type));

	std::cout << "300 " << tmp::minint<300>::result << " " << sizeof(tmp::minint<300>::type) << std::endl;
	CHECK_EQUAL(2, tmp::minint<300>::result);
	CHECK_EQUAL(2, sizeof(tmp::minint<300>::type));
	
	std::cout << "65535 " << tmp::minint<65535>::result << " " << sizeof(tmp::minint<65535>::type) << std::endl;
	CHECK_EQUAL(2, tmp::minint<65535>::result);
	CHECK_EQUAL(2, sizeof(tmp::minint<65535>::type));
	
	std::cout << "65536 " << tmp::minint<65536>::result << " " << sizeof(tmp::minint<65536>::type) << std::endl;
	CHECK_EQUAL(3, tmp::minint<65536>::result);
	CHECK_EQUAL(4, sizeof(tmp::minint<65536>::type));

	std::cout << "66000 " << tmp::minint<66000>::result << " " << sizeof(tmp::minint<66000>::type) << std::endl;
	CHECK_EQUAL(3, tmp::minint<66000>::result);
	CHECK_EQUAL(4, sizeof(tmp::minint<66000>::type));

	std::cout << "5000000000 " << tmp::minint<5000000000>::result << " " << sizeof(tmp::minint<5000000000>::type) << std::endl;
	CHECK_EQUAL(5, tmp::minint<5000000000>::result);
	CHECK_EQUAL(8, sizeof(tmp::minint<5000000000>::type));

	std::cout << "900000000000000000 " << tmp::minint<900000000000000000>::result << " " << sizeof(tmp::minint<900000000000000000>::type) << std::endl;
	CHECK_EQUAL(8, tmp::minint<900000000000000000>::result);
	CHECK_EQUAL(8, sizeof(tmp::minint<900000000000000000>::type));
}
