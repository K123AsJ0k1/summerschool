#include <cstdio>
#include <omp.h>
#include <unistd.h>
int main()
{
    int omp_threads;
    int omp_rank;
    omp_threads = omp_get_num_threads();
    printf("Running with %d!\n", omp_threads);
#pragma omp parallel private(omp_rank)
    {
        omp_rank = omp_get_thread_num();
        sleep(1);
        printf("Hello world! by thread %d\n", omp_rank);
    }
    return 0;
}
