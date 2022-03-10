#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

const double k = 0.0000861733034;
const double hbar = 6.58211951e-16;

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double startTime = MPI_Wtime();

    if (argc < 4) {
        if (rank == 0) printf("Whoops, you need more arguments!\n");
        return 1;
    }

    double omega = strtod(argv[1], NULL);
    double t = strtod(argv[2], NULL);
    long n = strtol(argv[3], NULL, 10);

    double coeff = -(hbar * omega) / (k * t);

    double topSum = 0.0;
    double bottomSum = 0.0;

    /* I tried using integer division, but it resulted in most of the nodes
     * doing no work because start and end would round off to the same value. */
    long start = rank == 0 ? 0 : ((double) rank / size) * n + 1;
    long end = ((double) (rank + 1) / size) * n;

    for (long count = start; count <= end; count++) {
        double temp = exp(coeff * count);
        topSum += (2*count + 1) * temp;
        bottomSum += temp;
    }

    double completeTopSum, completeBottomSum;
    MPI_Reduce(&topSum, &completeTopSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&bottomSum, &completeBottomSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double meanEnergy = (hbar / 2) * omega * completeTopSum / completeBottomSum;
        printf("Mean energy is: %g\n", meanEnergy);
        printf("Computation took %g seconds to complete.\n", MPI_Wtime());
    }

    MPI_Finalize();
    return 0;
}
