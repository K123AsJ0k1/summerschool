#include <cstdio>
#include <omp.h>
#include <unistd.h>
int main()
{
    int tid, nthreads;
    
    printf("Hello world!\n");
    #pragma omp parallel private(tid) shared(nthreads)
    {
        tid = omp_get_thread_num();
        #pragma omp single
        nthreads = omp_get_num_threads()
        #pragma omp critical
        printf("Thread %d\n", tid);
    }
    printf("Amount of threads %d\n", nthreads);
    return 0;
}
