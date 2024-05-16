#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test.h"

void printUsage()
{
    printf("Usage: ./pcg [OPTIONS]\n");
    printf("Options:\n");
    printf("  --test\tTests correctness of the PCG.\n");
    printf("  --bench\tBenchmarks the PCG on conservative and aggressive parameters.\n");
}

void runBenchmarks(size_t n, size_t t, int num_trials, size_t c)
{
    double time = 0;

    for (int i = 0; i < num_trials; i++)
    {
        time += bench_pcg_c(n, t,c);
        printf("Done with trial %i of %i\n", i + 1, num_trials);
    }
    printf("******************************************\n");
    printf("Avg time (N=3^%zu, c=%zu, t=%zu): %0.4f ms\n", n, c, t, time / num_trials);
    printf("******************************************\n\n");
}

int main(int argc, char **argv)
{
    int num_trials = 5;
    size_t params[][2] = {
        {12,5},
        {9,6},
        {13,5},
        {10,6},
        {11,6},
        {14,5},
        {20,4},
        {18,4},
    };
    int params_len = sizeof(params) / sizeof(params[0]);
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--bench") == 0)
        {
            for (int p = 0 ; p < params_len ; p++)
            {
                size_t t = params[p][0];
                size_t c = params[p][1];
                printf("******************************************\n");
                printf("Benchmarking PCG with conservative parameters (c=%zu, t=%zu)\n", c,t);
                runBenchmarks(14, t, num_trials,c);
                runBenchmarks(16, t, num_trials,c);
                runBenchmarks(18, t, num_trials,c);
            }

            // printf("******************************************\n");
            // printf("Benchmarking PCG with aggressive parameters (c=4, t=18)\n");
            // runBenchmarks(14, 18, num_trials,c);
            // runBenchmarks(16, 18, num_trials,c);
            // runBenchmarks(18, 18, num_trials,c);
        }
        else if (strcmp(argv[i], "--test") == 0)
        {
            printf("******************************************\n");
            printf("Testing PCG\n");
            test_pcg();
            printf("******************************************\n");
            printf("PASS\n");
            printf("******************************************\n\n");
        }
        else
        {
            printUsage();
        }
    }

    if (argc == 1)
        printUsage();
}
