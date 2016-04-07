#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mtwist.h>

int* results_mt;
int* results_std;
int* results_nop;

int main(int argc, char *argv[]) {
    const int n_bins = 32;
    long long n_tests = 1000000000;
    clock_t start, end;
    double t_mt;
    double t_std;
    double t_nop;

    results_mt  = calloc(n_bins, sizeof(int));
    results_std = calloc(n_bins, sizeof(int));
    results_nop = calloc(n_bins, sizeof(int));

    mtwist *mt = NULL;
    mt = mtwist_new();
    mtwist_seed(mt, 3915467345UL);
   
    if(RAND_MAX % n_bins != 0) {
        printf("NO UNIFORM STD_RAND! RAND_MAX = %d\n", RAND_MAX);
    } 
    unsigned long long mt_max = (1LL<<32LL)-1;
    if(mt_max % n_bins != 0) {
        printf("NO UNIFORM mt_rand! mt_max = %u\n", mt_max);
    }

    start = clock();
    for(long long i=0; i<n_tests; i++) {
        unsigned long mt_rand  = mtwist_u32rand(mt);
        results_mt [mt_rand  % n_bins]++;
    }
    end = clock();
    t_mt = (end-start)/(double)CLOCKS_PER_SEC;

    start = clock();
    for(long long i=0; i<n_tests; i++) {
        unsigned long std_rand = rand();
        results_std[std_rand % n_bins]++;
    }
    end = clock();
    t_std = (end-start)/(double)CLOCKS_PER_SEC;

    start = clock();

    unsigned long nop_rand = 391546734UL; 
    for(long long i=0; i<n_tests; i++) {
        nop_rand = (nop_rand*928+9298)%3915467345UL;
        results_nop[nop_rand % n_bins]++;
    }
    end = clock();
    t_nop = (end-start)/(double)CLOCKS_PER_SEC;


    printf("results_mt = {");
    for(int i=0; i<n_bins; i++) {
        if(i != 0) printf(",");
        printf("%d", results_mt[i]);
    }
    printf("};\n");
    printf("mt ran in %f seconds!\n", t_mt);

    printf("results_std = {");
    for(int i=0; i<n_bins; i++) {
        if(i != 0) printf(",");
        printf("%d", results_std[i]);
    }
    printf("};\n");
    printf("std ran in %f seconds!\n", t_std);

    printf("nop ran in %f seconds!\n", t_nop);

    mtwist_free(mt);
    free(results_mt);
    free(results_std);

    return 0;
}
