#include <iostream>
#include <math.h>

using namespace std;

const double k = 0.0000861733034;
const double hbar = 6.58211951e-16;

int main(int argc, char* argv[]) {

    if (argc < 4) {
        cout << "Whoops, you need more arguments!" << endl;
        return 1;
    }

    double omega = strtod(argv[1], nullptr);
    double t = strtod(argv[2], nullptr);
    long n = strtol(argv[3], nullptr, 10);

    double coeff = (-1 * (hbar * omega) / (k * t));

    double topSum = 0.0;
    double bottomSum = 0.0;
    double temp;

    for (long count = 0; count <= n; count++) {
        temp = exp(coeff * count);
        topSum += ((2*count + 1) * temp);
        bottomSum += temp;
    }
    
    double meanEnergy = ((hbar / 2) * omega * topSum / bottomSum);

    cout << "Mean energy is: " << meanEnergy << endl;
    
    return 0;
}