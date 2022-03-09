#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <mpi.h>
#include <time.h>

using namespace std;

int main()
{
	int n, rank, size;
	long double w;
	long double t;
	long double E;
	long double a;
	long double r;
	long double x;
	long double y,Newy;
	long double z,Newz;
	const long double e = 2.718281828;
	const long double h = 4.14E-15;
	const long double k = 8.62E-5;
	time_t seconds;

	MPI::Init();
	MPI::Status status;
	rank = MPI::COMM_WORLD.Get_rank();
	size = MPI::COMM_WORLD.Get_size();

	if(rank ==0) {
		cout << "Provide values for angular frequency, temperature (in K), and quantum number in this order.\n";
		cin >> w >> t >> n;
		a = ((h*w)/2);
		seconds = time (NULL);
	}

	MPI_Bcast(&w, 1, MPI::LONG_DOUBLE, 0,MPI_COMM_WORLD);
	MPI_Bcast(&t, 1, MPI::LONG_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Bcast(&n, 1, MPI::INT, 0,MPI_COMM_WORLD);

	x = 0;
	y = 0;
	z = 0;

	for(x=rank;x<=n;x+=size){
		r = ((x*h*w)/(k*t));
		y = (y+(((2*x)+1)*(1/(pow(e,r)))));
		z = (z+(1/(pow(e,r))));
	}

	MPI_Reduce(&y, &Newy,1, MPI::LONG_DOUBLE,MPI::SUM,0, MPI_COMM_WORLD);
	MPI_Reduce(&z, &Newz,1, MPI::LONG_DOUBLE,MPI::SUM,0, MPI_COMM_WORLD);

	if(rank==0) {
		E = ((a*Newy)/Newz);
		cout << "The mean energy is " << E << "eV.\n";
		cout << "\nThe computation took : " << 0-seconds+time(NULL)<< " seconds." <<endl;
	}

	MPI::Finalize();
	return 0;
}
