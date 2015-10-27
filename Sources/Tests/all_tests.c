#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(Point);
    RUN_TEST_GROUP(Array);

    RUN_TEST_GROUP(VotingFilter);
}

int main(int argc, const char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
