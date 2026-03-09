#include "bsplinesdata.h"
using namespace std;

int main()
{
	// 1. declare an Sdata object named sdat using the default constructor
	Sdata sdat;

	// 2. declare an ifstream object connected to the file containing the data points (pointset2.dat)
	std::ifstream ifs("datapoints4.dat");

	// 3. declare an ofstream object connected to output file for writing the evaluated points (BsplineSurf.dat)
	std::ofstream ofs("4_10BsplineSurf.dat");

	// 4. read the data points from the file into sdat
	ifs >> sdat;

	// 5. get from the user the number of segments in u and v and the order in u and v
	int nsegu, nsegv, ordu, ordv;

	cout << "Enter the number of segments in u: ";
	cin >> nsegu;

	cout << "Enter the number of segments in v: ";
	cin >> nsegv;

	cout << "Enter the order in u: ";
	cin >> ordu;

	cout << "Enter the order in v: ";
	cin >> ordv;

	// 6. declare a BsplineSdata object named bsp and initialise with sdat and the values from 5 
	BsplineSdata bsp(sdat, nsegu, nsegv, ordu, ordv);

	// 6. Use the ofstream object to write to the output file BsplineSurf.dat the BsplineSurf object returned by calling the method getBspline() for bsp
	ofs << bsp.getBspline();

	//	cout << "the least squares error is: " << bspline.computeLSQError() << "\n";
	cout << "The least squares error is: " << bsp.computeLSQError() << "\n";
	return 0;
}

// 4 fichiers avec u et v = 5 , ordre 4
// 4 fichiers avec u et v = 10



	