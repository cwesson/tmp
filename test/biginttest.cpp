#include "CppUTest/TestHarness.h"
#include "tmp/bigint.h"
#include "tmp/rotate.h"
#include <iostream>

TEST_GROUP(BigintTestGroup)
{

};

TEST(BigintTestGroup, BigintTest)
{
	printf("sizeof(uint128)  ==  %d", sizeof(uint128));
	CHECK(sizeof(uint128) == 128/8);
	printf("  PASS\n");
	printf("sizeof(uint256)  ==  %d", sizeof(uint256));
	CHECK(sizeof(uint256) == 256/8);
	printf("  PASS\n");
	printf("sizeof(uint512)  ==  %d", sizeof(uint512));
	CHECK(sizeof(uint512) == 512/8);
	printf("  PASS\n");
	printf("sizeof(uint1024) == %d", sizeof(uint1024));
	CHECK(sizeof(uint1024) == 1024/8);
	printf("  PASS\n");
	printf("sizeof(uint2048) == %d", sizeof(uint2048));
	CHECK(sizeof(uint2048) == 2048/8);
	printf("  PASS\n");
	printf("sizeof(uint4096) == %d", sizeof(uint4096));
	CHECK(sizeof(uint4096) == 4096/8);
	printf("  PASS\n");
	
	uint32_t a = 0x87654321;
	
	uint32_t b = tmp::rol<uint32_t>(a, 8);
	printf("0x%X", b);
	CHECK(b == 0x65432187);
	printf("  PASS\n");
	
	uint32_t c = tmp::ror<uint32_t>(a, 8);
	printf("0x%X", c);
	CHECK(c == 0x21876543);
	printf("  PASS\n");
	
	uint128 big1(0x1234567890ABCDEFull, 0xAABBCCDDEEFF3355ull);
	
	uint128 ba = big1 << 112;
	printf("0x%s", ba.hex().c_str());
	CHECK(ba.hex() == "33550000000000000000000000000000");
	printf("  PASS\n");
	uint128 bb = big1 << 16;
	printf("0x%s", bb.hex().c_str());
	CHECK(bb.hex() == "567890ABCDEFAABBCCDDEEFF33550000");
	printf("  PASS\n");
	uint128 bc = big1 >> 112;
	printf("0x%s", bc.hex().c_str());
	CHECK(bc.hex() == "00000000000000000000000000001234");
	printf("  PASS\n");
	uint128 bd = big1 >> 16;
	printf("0x%s", bd.hex().c_str());
	CHECK(bd.hex() == "00001234567890ABCDEFAABBCCDDEEFF");
	printf("  PASS\n");
	
	uint128 bl = tmp::rol(big1, 32);
	printf("0x%s", bl.hex().c_str());
	CHECK(bl.hex() == "90ABCDEFAABBCCDDEEFF335512345678");
	printf("  PASS\n");
	
	uint128 br = tmp::ror(big1, 32);
	printf("0x%s", br.hex().c_str());
	CHECK(br.hex() == "EEFF33551234567890ABCDEFAABBCCDD");
	printf("  PASS\n");
	
	uint128 sum = big1 + big1;
	printf("0x%s", sum.hex().c_str());
	CHECK(sum.hex() == "2468ACF121579BDF557799BBDDFE66AA");
	printf("  PASS\n");
	
	uint128 big10 = big1 + uint128(0x10);
	printf("0x%s", big10.hex().c_str());
	CHECK(big10.hex() == "1234567890ABCDEFAABBCCDDEEFF3365");
	printf("  PASS\n");
	
	uint128 big11 = uint128(0x10) + big1;
	printf("0x%s", big11.hex().c_str());
	CHECK(big11.hex() == "1234567890ABCDEFAABBCCDDEEFF3365");
	printf("  PASS\n");
	
	uint128 neg = -big1;
	printf("0x%s\n", neg.hex().c_str());
	
	uint128 diff = big1 - big1;
	printf("0x%s", diff.hex().c_str());
	CHECK(diff == uint128(0));
	printf("  PASS\n");
	
	printf("big1 == big1");
	CHECK(big1 == big1);
	printf("  PASS\n");
	
	uint256 big2(big1, big1);
	printf("0x%s\n", big2.hex().c_str());
	
	CHECK(uint256(big1) < big2);
	
	uint128 bigpp(0x1234567890ABCDEFull, 0xFFFFFFFFFFFFFFFFull);
	bigpp++;
	printf("0x%s", bigpp.hex().c_str());
	CHECK_EQUAL("1234567890ABCDF00000000000000000", bigpp.hex());
	printf("  PASS\n");
	
	bigpp = uint128(0x1234567890ABCDEFull, 0xFFFFFFFFFFFFFFFFull);
	++bigpp;
	printf("0x%s", bigpp.hex().c_str());
	CHECK_EQUAL("1234567890ABCDF00000000000000000", bigpp.hex());
	printf("  PASS\n");
	
	uint128 zero(0x0ull, 0x0ull);
	CHECK_EQUAL("00000000000000000000000000000000", zero.hex());
	printf(" A | B | A||B | A&&B \n");
	printf("---+---+------+------\n");
	printf(" 0 | 0 |   0  |   0  ");
	CHECK_EQUAL(false, (zero || zero));
	CHECK_EQUAL(false, (zero && zero));
	printf("  PASS\n");
	printf(" 0 | 1 |   1  |   0  ");
	CHECK_EQUAL(true, (zero || big1));
	CHECK_EQUAL(false, (zero && big1));
	printf("  PASS\n");
	printf(" 1 | 0 |   1  |   0  ");
	CHECK_EQUAL(true, (big1 || zero));
	CHECK_EQUAL(false, (big1 && zero));
	printf("  PASS\n");
	printf(" 1 | 1 |   1  |   1  ");
	CHECK_EQUAL(true, (big1 || big2));
	CHECK_EQUAL(true, (big1 && big2));
	printf("  PASS\n");
	
	uint128 small(8);
	uint256 prod = small * small;
	printf("0x%s\n", prod.hex().c_str());
	
	
	uint128 bign(0x1234567890ABCDEFull, 0xAABBCCDDEEFF3355ull);
	uint128 bigd(0x0009811098570195ull, 0x9420958450205250ull);
	uint128 quo = bign / bigd;
	printf("0x%s\n", quo.hex().c_str());
	
	std::cout << std::numeric_limits<uint128>::digits << "    " << std::numeric_limits<uint128>::digits10 << std::endl;
}
