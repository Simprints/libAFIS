#ifdef _MSC_VER
	#include <io.h>
#else
	#include <unistd.h>
#endif
#include "unity_fixture.h"

static void RunAllTests(void)
{
    printf("\nOrientation tests\n");
    RUN_TEST_GROUP(HillOrientation);

    printf("\nOriented smoother tests\n");
    RUN_TEST_GROUP(OrientedSmoother); 
    
    printf("\nPoint tests\n");
    RUN_TEST_GROUP(Point);

    printf("\nArray tests\n");
    RUN_TEST_GROUP(Array);

    printf("\nBinaryMap tests\n");
    RUN_TEST_GROUP(BinaryMap);

    printf("\nCalc tests\n");
    RUN_TEST_GROUP(Calc);

    printf("\nPgm tests\n");
    RUN_TEST_GROUP(Pgm);

    printf("\nVoting filter tests\n");
    RUN_TEST_GROUP(VotingFilter);

    printf("\nLocal histogram tests\n");
    RUN_TEST_GROUP(LocalHistogram);

    printf("\nLines by orientation tests\n");
    RUN_TEST_GROUP(LinesByOrientation);
    
    printf("\nEnsure we an load serialised binary data\n");
    RUN_TEST_GROUP(DataStructures);

    printf("\nEqualizer tests\n");
    RUN_TEST_GROUP(Equalizer);

    printf("\nThinner tests\n");
    RUN_TEST_GROUP(Thinner);

    printf("\nDot remover tests\n");
    RUN_TEST_GROUP(DotRemover);

    printf("\nBestMatchSkipper tests\n");
    RUN_TEST_GROUP(BestMatchSkipper);
}

int main(int argc, const char * argv[])
{
    if (argc == 2)
    {
        chdir(argv[1]);
    }
    return UnityMain(argc, argv, RunAllTests);
}
