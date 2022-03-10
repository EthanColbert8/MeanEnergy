#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double k = 0.0000861733034;
const double hbar = 6.58211951e-16;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Whoops, you need more arguments!\n");
        return 1;
    }

    double omega = strtod(argv[1], NULL);
    double t = strtod(argv[2], NULL);
    long n = strtol(argv[3], NULL, 10);

    double coeff = -(hbar * omega) / (k * t);

    double topSum = 0.0;
    double bottomSum = 0.0;

    for (long count = 0; count <= n; count++) {
        double temp = exp(coeff * count);
        topSum += (2*count + 1) * temp;
        bottomSum += temp;
    }

    double meanEnergy = (hbar / 2) * omega * topSum / bottomSum;

    printf("Mean energy is: %g\n", meanEnergy);

    return 0;
}
