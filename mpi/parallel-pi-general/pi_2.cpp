#include <cstdio>
#include <cmath>
#include <mpi.h>

constexpr int n = 840;

int main(int argc, char** argv)
{
  int rank, ntasks;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (0 == rank) {
    printf("Computing approximation to pi with N=%d\n", n);
    printf("Using %d MPI processes\n", ntasks);
  }

  int chunksize = n / ntasks;
  int istart = rank * chunksize + 1;
  int istop = (rank + 1) * chunksize;
  
  int remainder = n % ntasks;
  if (remainder > 0) {
    if (rank < remainder) {
      istart += rank;
      istop += rank + 1;
    } else {
      istart += remainder;
      istop += remainder;
    }
  }
  
  double localpi = 0.0;
  for (int i=istart; i <= istop; i++) {
    double x = (i - 0.5) / n;
    localpi += 1.0 / (1.0 + x*x);
  }

  if (rank == 0) {
    double pi = localpi;
    for (int j=1; j < ntasks; j++) {
      MPI_Recv(&localpi, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      pi += localpi; 
    }
    pi *= 4.0 / n;
    printf("Approximate pi=%18.16f (exact pi=%10.8f)\n", pi, M_PI);
  } else {
    MPI_Send(&localpi, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
  
  MPI_Finalize();
}
