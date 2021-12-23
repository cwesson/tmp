#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "tmp/fixed.h"
#include <iostream>

static const double pi = 3.14159265359;
static const double m12 = 0.000244140625; // 2^-12
static const double m3 = 0.125; // 2^-3

TEST_GROUP(FixedTestGroup)
{

};

TEST(FixedTestGroup, ArithmeticTest)
{
	tmp::fixed<4,12,signed> a(pi);
	static_assert(sizeof(a) == 4);
	double d = a;
	std::cout.precision(10);
	DOUBLES_EQUAL(pi, d, m12);
	std::cout << "pi=" << d << "  PASS" << std::endl;
	
	a *= 2;
	d = a;
	DOUBLES_EQUAL(pi*2.0, d, m12);
	std::cout << "2pi=" << d << "  PASS" << std::endl;
	
	a /= 2;
	d = a;
	DOUBLES_EQUAL(pi, d, m12);
	std::cout << "2pi/2=" << d << "  PASS" << std::endl;
	d = a + a;
	DOUBLES_EQUAL(pi+pi, d, m12);
	std::cout << "pi+pi=" << d << "  PASS" << std::endl;
	d = a - a;
	DOUBLES_EQUAL(0, d, m12);
	std::cout << "pi-pi=" << d << "  PASS" << std::endl;
	d = a * a;
	DOUBLES_EQUAL(pi*pi, d, m12);
	std::cout << "pi*pi=" << d << "  PASS" << std::endl;
	d = a / a;
	DOUBLES_EQUAL(pi/pi, d, m12);
	std::cout << "pi/pi=" << d << "  PASS" << std::endl;

	tmp::Q3_12 b = a * tmp::fixed<4,12,signed>(-2.0);
	d = b;
	DOUBLES_EQUAL(pi*-2.0, d, m12);
	std::cout << "-2pi=" << d << "  PASS" << std::endl;
}

TEST(FixedTestGroup, ConversionTest)
{
	double d;
	{
		tmp::fixed<3,12,unsigned> c(pi);
		tmp::fixed<7,15,unsigned> e(c);
		d = e;
		DOUBLES_EQUAL(pi, d, m12);
		std::cout << d << std::endl;
	}
	{
		tmp::fixed<3,15,unsigned> c(pi);
		tmp::fixed<7,12,unsigned> e(c);
		d = e;
		DOUBLES_EQUAL(pi, d, m12);
		std::cout << d << std::endl;
	}
	{
		tmp::fixed<15,3,unsigned> c(pi);
		tmp::fixed<3,3,unsigned> e(c);
		d = e;
		DOUBLES_EQUAL(pi, d, m3);
		std::cout << d << std::endl;
	}
	{
		tmp::fixed<3,3,unsigned> c(pi);
		tmp::fixed<15,3,unsigned> e(c);
		d = e;
		DOUBLES_EQUAL(pi, d, m3);
		std::cout << d << std::endl;
	}
}
