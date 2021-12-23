#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "tmp/compare.h"
#include <iostream>

TEST_GROUP(CompareTestGroup)
{

};

TEST(CompareTestGroup, ChainingTest)
{
	if(tmp::compare() << 5 < 10 < 100 < 100.0){
		FAIL("true");
	}else{
		CHECK(static_cast<bool>(tmp::compare() << 5 < 10 < 100 < 100.0) == false);
	}

	if(tmp::compare() << 5 < 10 < 100 < 100.1){
		CHECK(static_cast<bool>(tmp::compare() << 5 < 10 < 100 < 100.1) == true);
	}else{
		FAIL("false");
	}

	if(tmp::compare() << 5 < 10 < 100 <= 100.0){
		CHECK(static_cast<bool>(tmp::compare() << 5 < 10 < 100 <= 100.0) == true);
	}else{
		FAIL("false");
	}

	if(tmp::compare() << 5 < 1 < 100 < 100.1){
		FAIL("true");
	}else{
		CHECK(static_cast<bool>(tmp::compare() << 5 < 1 < 100 < 100.1) == false);
	}
}
