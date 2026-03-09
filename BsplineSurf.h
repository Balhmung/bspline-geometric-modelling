#ifndef _BSPLINE_SURFACE
#define _BSPLINE_SURFACE

#include "point.h"
#include "abssurf.h"

// class encapuslating a Bspline surface
class BsplineSurf : public AbsSurface<Point3D>
{
private:
	int ordu, ordv;			// order in u and v
	int p, q;				// dimension in u and v
	Matrix<Point3D> d;		// control points
	Vector<double> knotsu;	// knot vector in u 
	Vector<double> knotsv;	// knot vector in v
public:
	//constructors
	BsplineSurf();
	BsplineSurf(double u1, double u2, double v1, double v2, int k, int l, int dimu, int dimv, const Matrix<Point3D>& cpts, const Vector<double>& uknot, const Vector<double>& vknot);

	// overloaded operator for surface evaluation at (u0,v0)
	Point3D operator()(double u0, double v0) const;

	// read/write methods
	void readfile(std::ifstream& ifs);
	void writefile(std::ofstream& ofs) const;
	void write(std::ostream& os) const;
	void read(std::istream &is);
};



#endif