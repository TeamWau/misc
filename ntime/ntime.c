#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>

int64_t getTimeDiff(struct timespec *time_A, struct timespec *time_B){
    return ((time_A->tv_sec * 1000000000) + time_A->tv_nsec) -
           ((time_B->tv_sec * 1000000000) + time_B->tv_nsec);
}

int measuretime_coarse( char* program, char** program_args ) {
    struct timespec start, end;
    pid_t pID;
    int rs;

    if( program_args == NULL ) {
        program_args[0] = " ";
    }

    clock_gettime(CLOCK_MONOTONIC, &start);

    pID = fork();
    if( pID == 0 ) {
        execvp( program, program_args );
    }
    else if( pID < 0 ) {
        return 1;
    }
    else {
        waitpid( pID, &rs, 0 );

        clock_gettime(CLOCK_MONOTONIC, &end);

        uint64_t tdiff = getTimeDiff(&end, &start);

        printf("\nApprox wall time: %llu ns\n", tdiff);
        return 0;
    }
}

int main( int argc, char **argv ) {
    if( argc == 1 ) {
        printf( "%s - precise time program\nInvocation: %s <program> <args for program>\n", argv[0], argv[0] );
    printf( "\nNOTICE: Times are _approximate_! As this is a very accurate timer, it measures the overhead time of its own execution, as well as any work done by the kernel.\nWhat this means is that the times are likely to vary heavily and should probably be averaged versus used as-is as a benchmark.\n" );
    printf( "\nError: no program specified, terminating.\n" );
        return 1;
    }

        measuretime_coarse( argv[1], argv + 1 );
        return 0;
}
