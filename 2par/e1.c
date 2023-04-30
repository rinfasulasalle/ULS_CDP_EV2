#include <stdio.h>
#include <mpi.h>
#include <time.h>

#define num_steps 100000

int main(int argc, char* argv[]) {
    clock_t tStart = clock();
    int rank, size;
    double step = 1.0 / num_steps;
    double x, pi, sum = 0.0;
    double local_sum = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_start = rank * (num_steps / size);
    int local_end = local_start + (num_steps / size);

    for (int i = local_start; i < local_end; ++i) {
        x = (i + 0.5) * step;
        local_sum += 4.0 / (1.0 + x*x);
    }

    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi = step * sum;
        printf("PI value = %f\n", pi);
        printf("Time taken: %.4fs\n",(double)(clock()-tStart)/CLOCKS_PER_SEC);
    }
    MPI_Finalize();
    return 0;
}
