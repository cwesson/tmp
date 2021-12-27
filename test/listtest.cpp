#include "CppUTest/TestHarness.h"
#include "tmp/list.h"
using namespace tmp;

typedef List<Int<1>,
	List< Int<2>,
	List< Int<4>,
	List< Int<8>
> > > > list;

TEST_GROUP(ListTestGroup)
{

};

TEST(ListTestGroup, LengthTest)
{
	CHECK_EQUAL(4, Length<list>::result);
}

TEST(ListTestGroup, SumTest)
{
	CHECK_EQUAL(15, Sum<list>::result);
}

TEST(ListTestGroup, ProductTest)
{
	CHECK_EQUAL(64, Product<list>::result);
}

TEST(ListTestGroup, NthTest)
{
	CHECK_EQUAL(8, (Nth<list, 3>::result));
}

TEST(ListTestGroup, IncludesTest)
{
	CHECK_EQUAL(true, (Includes<list, Int<2> >::result));
	CHECK_EQUAL(false, (Includes<list, Int<32> >::result));
}

TEST(ListTestGroup, FindTest)
{
	CHECK_EQUAL(0, (Find<list, Int<1> >::result));
	CHECK_EQUAL(2, (Find<list, Int<4> >::result));
	CHECK_EQUAL(3, (Find<list, Int<8> >::result));
	//CHECK_EQUAL(-1, (Find<list, Int<32> >::result));
}

