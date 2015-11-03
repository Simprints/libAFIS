#ifdef _MSC_VER
	#include <io.h>
#else
	#include <unistd.h>
#endif
#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(Point);
    RUN_TEST_GROUP(Array);
    RUN_TEST_GROUP(BinaryMap);

    RUN_TEST_GROUP(VotingFilter);
    RUN_TEST_GROUP(LocalHistogram);
    
    RUN_TEST_GROUP(DataStructures);
}

int main(int argc, const char * argv[])
{
    if (argc == 2)      
    {       
        chdir(argv[1]);     
    } 
    return UnityMain(argc, argv, RunAllTests);
}
