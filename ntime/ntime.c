#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

long measuretime_coarse( char** program, char** program_args ) {
    struct timespec res;
    int ctime, rs;
    long starttime, endtime;
    pid_t pID;

    if( program_args == NULL ) {
        program_args = " ";
    }

    ctime = clock_getres( CLOCK_MONOTONIC_COARSE, &res );
    ctime = clock_gettime( CLOCK_MONOTONIC_COARSE, &res );
    starttime = res.tv_nsec;
    printf( "Begin execution at approx: %ldns\n", starttime );

    pID = fork();

    if( pID == 0 ) {
        execvp( program, program_args );
    } 
    else if( pID < 0 ) {
        return 1;   
    } 
    else {
        waitpid( pID, &rs, 0 );
        ctime = clock_gettime( CLOCK_MONOTONIC_COARSE, &res );
        endtime = res.tv_nsec;

        printf( "End execution at approx: %ldns\n", endtime );
        
        return endtime - starttime;
    }
}

int main( int argc, char **argv ) {
    if( argc == 1 ) {
        printf( "%s - precise time program\nInvocation: %s <program> <args for program>\n", argv[0], argv[0] );
    printf( "\nNOTICE: Times are _approximate_! As this is a very accurate timer, it measures the overhead time of its own execution, as well as any work done by the kernel.\nWhat this means is that the times are likely to vary heavily and should probably be averaged versus used as-is as a benchmark.\n" );
    printf( "\nError: no program specified, terminating.\n" );
        return 1;
    }

        long timeret = measuretime_coarse( argv[1], argv + 1 );
        printf( "\nTotal approx. runtime: %dns\n", timeret ) ;
        return 0;
}
