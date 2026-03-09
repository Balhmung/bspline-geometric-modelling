#include "bsplinesurf.h"
#include "bsplinecurve.h"


// constructors for the BsplineSUrf
BsplineSurf::BsplineSurf() : AbsSurface<Point3D>(0.0,0.0,0.0,0.0), ordu(0), ordv(0), p(0), q(0), d(), knotsu(), knotsv() {}

BsplineSurf::BsplineSurf(double u1, double u2, double v1, double v2, int k, int l, int numu, int numv, const Matrix<Point3D>& cpts, const Vector<double>& uknots, const Vector<double>& vknots) : AbsSurface<Point3D>(u1, u2, v1, v2),
ordu(k), ordv(l), p(numu), q(numv), d(cpts), knotsu(uknots), knotsv(vknots) {}


// overloaded operator for evaluation of the surface at u0, v0
Point3D BsplineSurf::operator()(double u0, double v0) const
{
	Vector<Point3D> v(p);
	// limits in v
	double v1 = knotsv[ordv - 1];
	double v2 = knotsv[q - ordv];

	// use tensor product evaluation
	// evaluate in v and create points in u
	for (int i = 0; i<p; i++) v[i] = BsplineCurve(v1, v2, ordv, q, d.getRow(i), knotsv)(v0);

	// limits in u
	double u1 = knotsu[ordu - 1];
	double u2 = knotsu[p - ordu];

	// evaluate the resulting curve
	return BsplineCurve(u1, u2, ordu, p, v, knotsu)(u0);
}

// read/write methods
void BsplineSurf::read(std::istream& is)			// read from the keyboard
{
	std::cout << "input the left and right limits in u for the surf\n";
	double umin, umax;
	is >> umin >> umax;
	std::cout << "input the left and right limits in v for the surf\n";
	double vmin, vmax;
	is >> vmin >> vmax;

	std::cout << "input the order in u and v\n";
	int k, l;
	is >> k >> l;
	std::cout << "how many control points in u, v\n";
	int numu, numv;
	is >> numu >> numv;
	std::cout << "input the points\n";
	Matrix<Point3D> cpts(numu, numv);
	is >> cpts;
	std::cout << "input the knot values in u\n";
	Vector<double> uknots(numu + k);
	is >> uknots;
	std::cout << "input the knot values in v\n";
	Vector<double> vknots(numv + l);
	is >> vknots;

	(*this) = BsplineSurf(umin, umax, vmin, vmax, k, l, numu, numv, cpts, uknots, vknots);
}


void BsplineSurf::readfile(std::ifstream& ifs)		// read from a file
{
	double umin, umax;
	ifs >> umin >> umax;

	double vmin, vmax;
	ifs >> vmin >> vmax;

	int k, l;
	ifs >> k >> l;

	int numu, numv;
	ifs >> numu >> numv;

	Matrix<Point3D> cpts(numu, numv);
	ifs >> cpts;

	Vector<double> uknots(numu + k);
	ifs >> uknots;
	Vector<double> vknots(numv + l);
	ifs >> vknots;

	(*this) = BsplineSurf(umin, umax, vmin, vmax, k, l, numu, numv, cpts, uknots, vknots);
}


void BsplineSurf::write(std::ostream& os) const		// write to the screen
{
	std::cout << "the left and right limits for the surf in u are\n";
	std::cout << getLeftLimitU() << " " << getRightLimitU() << "\n";
	std::cout << "the left and right limits for the surf in v are\n";
	std::cout << getLeftLimitV() << " " << getRightLimitV() << "\n";
	std::cout << "the order of the BsplineSurf is " << ordu << " " << ordv << "\n";
	std::cout << "there are " << p << "," << q << " control points\n";
	std::cout << "the control points are\n";
	std::cout << d;
	std::cout << "the knot values in u are\n";
	std::cout << knotsu;
	std::cout << "the knot values in v are\n";
	std::cout << knotsv;
}


void BsplineSurf::writefile(std::ofstream& ofs)	const		// write to a file
{
	ofs << "BsplineSurf\n";
	ofs << ordu << " " << ordv << " " << p << " " << q << "\n";
	ofs << "knotsu\n";
	ofs << knotsu;
	ofs << "knotsv\n";
	ofs << knotsv;
	ofs << "cpoints\n";
	ofs << d;

}
