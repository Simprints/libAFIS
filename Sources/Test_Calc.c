#include "General/Calc.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Calc);

TEST_SETUP(Calc)
{
}

TEST_TEAR_DOWN(Calc)
{
}


TEST(Calc, Calc_CountBits)
{
	TEST_ASSERT_EQUAL_INT_MESSAGE(1, Calc_CountBits(1), "Population count of 1 is 1");
}