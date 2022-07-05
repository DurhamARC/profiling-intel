#include <cmath>
#include <iostream>
#include <mpi.h>

void do_fancy_physics(const int n_iters, const int rank) {
  float aggregator = 0;
  for (int i = 0; i < n_iters; ++i) {
    aggregator += sin(i);
  }
  std::cout << "Result on " << rank << ": " << aggregator << std::endl;
}

/**
 * A simple nonblocking send and receive pattern designed to allow users to
 * experiment with features in the Intel Trace Analyzer and Collector
 *
 * Run with:
 *     mpirun -trace -np 2 <executable>
 * And launch the traceanalyzer:
 *     traceanalyzer <executable>.stf
 **/
int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  enum role_ranks { SENDER, RECEIVER };
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  const int first_tag = 0, second_tag = 1;
  switch (my_rank) {
    case SENDER: {
      int buffer_sent = 12345;
      MPI_Request request;
      MPI_Isend(&buffer_sent, 1, MPI_INT, 1, first_tag, MPI_COMM_WORLD, &request);
      MPI_Isend(&buffer_sent, 1, MPI_INT, 1, second_tag, MPI_COMM_WORLD,
                &request);

      const int n_iters = 2'000'000;
      do_fancy_physics(n_iters, my_rank);
      break;
    }
    case RECEIVER: {
      int received;
      const int n_iters = 2'000'000;
      do_fancy_physics(n_iters, my_rank);
      MPI_Recv(&received, 1, MPI_INT, 0, first_tag, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      do_fancy_physics(n_iters, my_rank);
      MPI_Recv(&received, 1, MPI_INT, 0, second_tag, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      break;
    }
  }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}
