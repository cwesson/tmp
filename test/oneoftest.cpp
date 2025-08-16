#include "CppUTest/TestHarness.h"
#include "tmp/oneof.h"
#include <iostream>

class Test {
	public:
		Test(int a, int b, int c) :
			a(a),
			b(b),
			c(c)
		{
			std::cout << "Construct test " << a << " " << b << " " << c << std::endl;
		}
		
		~Test() {
			std::cout << "Destruct test " << a << " " << b << " " << c << std::endl;
		}
		
		Test& operator=(const Test& other) {
			this->a = other.a;
			this->b = other.b;
			this->c = other.c;
			std::cout << "Assign test " << a << " " << b << " " << c << std::endl;
			return *this;
		}

	private:
		int a;
		int b;
		int c;
};

TEST_GROUP(OneofTestGroup)
{

};

TEST(OneofTestGroup, IsOneofTest)
{
	std::cout << "is_oneof double";
	CHECK((tmp::is_oneof<double, Test, double, int>::value) == true);
	std::cout << "  PASS" << std::endl;
	std::cout << "!is_oneof float";
	CHECK((tmp::is_oneof<float, Test, double, int>::value) == false);
	std::cout << "  PASS" << std::endl;
}

TEST(OneofTestGroup, OneofTest)
{
	tmp::oneof<int, Test, double> o(42);
	std::cout << "sizeof(o) = " << sizeof(o) << std::endl;

	std::cout << "init is int";
	CHECK(o.is<int>());
	std::cout << "  PASS" << std::endl;
	std::cout << "!init is double";
	CHECK(!o.is<double>());
	std::cout << "  PASS" << std::endl;
	std::cout << "!init is Test";
	CHECK(!o.is<Test>());
	std::cout << "  PASS" << std::endl;
	
	o.make<Test>(1, 2, 3);
	std::cout << "!make is int";
	CHECK(!o.is<int>());
	std::cout << "  PASS" << std::endl;
	std::cout << "!make is double";
	CHECK(!o.is<double>());
	std::cout << "  PASS" << std::endl;
	std::cout << "make is Test";
	CHECK(o.is<Test>());
	std::cout << "  PASS" << std::endl;

	o.set<int>(42);
	std::cout << "set1 is int";
	CHECK(o.is<int>());
	std::cout << "  PASS" << std::endl;
	std::cout << "!set1 is double";
	CHECK(!o.is<double>());
	std::cout << "  PASS" << std::endl;
	std::cout << "!set1 is Test";
	CHECK(!o.is<Test>());
	std::cout << "  PASS" << std::endl;
	
	std::cout << "as int " << *o.as<int>();
	CHECK_EQUAL(42, *o.as<int>());
	std::cout << "  PASS" << std::endl;

	o.set<double>(3.14159);
	std::cout << "!set2 is int";
	CHECK(!o.is<int>());
	std::cout << "  PASS" << std::endl;
	std::cout << "set2 is double";
	CHECK(o.is<double>());
	std::cout << "  PASS" << std::endl;
	std::cout << "!set2 is Test";
	CHECK(!o.is<Test>());
	std::cout << "  PASS" << std::endl;
	
	std::cout << "as double " << *o.as<double>();
	DOUBLES_EQUAL(3.14159, *o.as<double>(), 0.001);
	std::cout << "  PASS" << std::endl;

	o = 1492;
	std::cout << "assign is int";
	CHECK(o.is<int>());
	std::cout << "  PASS" << std::endl;
	std::cout << "!assign is double";
	CHECK(!o.is<double>());
	std::cout << "  PASS" << std::endl;
	std::cout << "!assign is Test";
	CHECK(!o.is<Test>());
	std::cout << "  PASS" << std::endl;
	
	std::cout << "as int " << *o.as<int>();
	CHECK_EQUAL(1492, *o.as<int>());
	std::cout << "  PASS" << std::endl;
}

