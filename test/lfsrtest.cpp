#include "CppUTest/TestHarness.h"
#include "tmp/lfsr.h"
#include <iostream>

TEST_GROUP(LFSRTestGroup)
{

};

TEST(LFSRTestGroup, LFSRTest)
{
	typedef tmp::lfsr::LFSR<16, 16, 14, 13, 11> test_lfsr_t;
	unsigned int count = 0;
	test_lfsr_t lfsr16(0xACE1);
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
	
	test_lfsr_t shift(lfsr16 >> 4);
	std::cout << shift.state() << std::endl;
	std::cout << lfsr16.state() << std::dec << std::endl;
	CHECK_EQUAL(0x2ACE, shift.state());
	CHECK_EQUAL(0xACE1, lfsr16.state());
}
