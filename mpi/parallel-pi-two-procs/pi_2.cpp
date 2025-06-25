#include <cstdio>
#include <cmath>
#include <mpi.h>

constexpr int n = 840;

int main(int argc, char** argv)
{
  printf("Computing approximation to pi with N=%d\n", n);

  int rank, ntasks;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (ntasks != 2) {
    printf("Please run with 2 MPI processes\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int istart;
  int istop

  if (rank == 0) {
    istart = 1
    istop = n/2; 
  } 

  if (rank == 1) {
    istart = n/2 + 1;
    istop = n
  }

  double pi = 0.0;
  for (int i=istart; i <= istop; i++) {
    double x = (i - 0.5) / n;
    pi += 1.0 / (1.0 + x*x);
  }

  int mpi_tag = 1;
  if (rank == 1) {
    MPI_Send(pi, 1, MPI_DOUBLE, 0, mpi_tag, MPI_COMM_WORLD);
  }

  if (rank == 0) {
    double received_pi;
    MPI_Recv(&received_pi, 1, MPI_DOUBLE, 1, mpi_tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    pi = pi + received_pi; 
    pi *= 4.0 / n;
    printf("Approximate pi=%18.16f (exact pi=%10.8f)\n", pi, M_PI);
  }
}
