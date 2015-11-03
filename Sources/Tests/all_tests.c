#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(Point);
    RUN_TEST_GROUP(Array);
    RUN_TEST_GROUP(BinaryMap);

    RUN_TEST_GROUP(VotingFilter);
    RUN_TEST_GROUP(LocalHistogram);
}

int main(int argc, const char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
