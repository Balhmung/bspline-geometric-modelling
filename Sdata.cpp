
#include "sdata.h"


// constructors for Sdata
Sdata::Sdata() : m(0), n(0), pts(), uparam(), vparam() {}

Sdata::Sdata(int numu, int numv, const Matrix<Point3D>& data) : m(numu), n(numv), pts(data), uparam(m), vparam(n)
{
	uniform();
}


// accessor method
int Sdata::getNumU() const
{
	return m;
}


int Sdata::getNumV() const
{
	return n;
}

Matrix<Point3D> Sdata::getPoints() const
{
	return pts;
}

Vector<double> Sdata::getParamU() const
{
	return uparam;
}


Vector<double> Sdata::getParamV() const
{
	return vparam;
}


// computes the uniform pareameterisation in u and v
void Sdata::uniform()
{
	for (int i = 0; i<m; i++) {
		uparam[i] = (double)i;
	}
	for (int i = 0; i<n; i++) {
		vparam[i] = (double)i;
	}
}

// computes the chord length pareameterisation in u and v 
void Sdata::chord()
{
	// To DO
}

// computes the centripetal pareameterisation in u and v
void Sdata::centripetal()
{
	// To DO
}

// read/write methods
void Sdata::readfile(std::ifstream& ifs)	// reads from a file
{
	int numu, numv;
	ifs >> numu >> numv;

	Matrix<Point3D> data(numu, numv);
	ifs >> data;

	*this = Sdata(numu, numv, data);
}

void Sdata::writefile(std::ofstream& ofs) const // writes to a file
{
	ofs << m << " " << n << "\n";
	ofs << pts;
	ofs << uparam;
	ofs << vparam;
}

void Sdata::write(std::ostream& os) const	// writes to the screen
{
	os << m << " " << n << "\n";
	os << pts;
	os << uparam;
	os << vparam;
}

void Sdata::read(std::istream &is)		// reads from the keyboarf
{
	std::cout << "number of points in u and v\n";
	int numu, numv;
	is >> numu >> numv;

	std::cout << "input points\n";
	Matrix<Point3D> data(numu, numv);
	is >> data;

	*this = Sdata(numu, numv, data);
}
