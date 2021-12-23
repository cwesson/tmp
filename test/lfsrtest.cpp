#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "tmp/lfsr.h"
#include <iostream>

TEST_GROUP(LFSRTestGroup)
{

};

TEST(LFSRTestGroup, LFSRTest)
{
	unsigned int count = 0;
	tmp::lfsr::LFSR<16, 16, 14, 13, 11> lfsr16(0xACE1);
	CHECK_EQUAL(2, sizeof(lfsr16));
	CHECK_EQUAL(1, *lfsr16);
	CHECK_EQUAL(0xACE1, lfsr16.state());
	++lfsr16;
	++count;
	std::cout << std::hex << lfsr16.state() << std::endl;
	do{
		if(count == 4){
			std::cout << lfsr16.state() << std::endl;
			CHECK_EQUAL(0, *lfsr16);
			CHECK_EQUAL(0x2ACE, lfsr16.state());
		}
		lfsr16++;
		++count;
	} while(lfsr16.state() != 0xACE1);
	std::cout << "period: " << count << std::endl;
	CHECK_EQUAL(0xFFFF, count);
	
	auto shift(lfsr16 >> 4);
	std::cout << shift.state() << std::endl;
	std::cout << lfsr16.state() << std::endl;
	CHECK_EQUAL(0x2ACE, shift.state());
	CHECK_EQUAL(0xACE1, lfsr16.state());
}
