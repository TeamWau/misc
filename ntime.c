#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main( int argc, char **argv ) {
    long starttime;
    struct timespec res;
    int ctime = clock_getres( CLOCK_MONOTONIC_COARSE, &res ); 
    int ret;

    ctime = clock_gettime( CLOCK_MONOTONIC_COARSE, &res );
    starttime = res.tv_nsec;
    printf( "Begin execution at approx: %ldns\n", starttime );
    ret = execv( argv[1], argv + 1 );

    if( ret == 0 ) {
    
    ctime = clock_gettime( CLOCK_MONOTONIC_COARSE, &res );
    long endtime = res.tv_nsec;
    printf( "End execution at approx: %ldns\n", endtime );

    printf( "\nTotal approx. runtime: %ldns\n", endtime - starttime );


    return 0;
    }

    else {
        printf( "Program failed, returned %d.\n", ret );
        return 1;
    }
}
