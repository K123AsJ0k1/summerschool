#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int process_rank;
    int total_processes;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processes);

    printf("Hello from %d!\n", process_rank);

    if (process_rank == 0) {
        printf("Total processes is %d!\n", total_processes);
    }
    
    if (process_rank == (total_processes-1)) {
        printf("I'm the last but not least");
    }

    if (process_rank == 42) {
        printf("I'm the Answer to the Ultimate Question, of Life, the Universe and Everything!");
    }

    MPI_Finalize();
}
