#ifndef _SDATA
#define _SDATA

#include "textobject.h"
#include "matrix.h"
#include "point.h"


// class encpaulating the data points for the surface fitting
class Sdata : public TextObject
{
private:
	int m, n;				// number of points in u and v
	Matrix<Point3D> pts;	// data points
	Vector<double> uparam;	// u parameter values
	Vector<double> vparam;	// v parameter values
	void uniform();			// uniform parameterisation method (page 25 of the notes)
	void chord();			// chord length parameterisation method (page 26 of the notes)
	void centripetal();		// centripetal parameterisation method (page 26 of the notes)
public:
	// constructors
	Sdata();
	Sdata(int numu, int numv, const Matrix<Point3D>& data);

	// accessor methods
	int getNumU() const;
	int getNumV() const;
	Vector<double> getParamU() const;
	Vector<double> getParamV() const;
	Matrix<Point3D> getPoints() const;

	// read/write methods
	virtual void readfile(std::ifstream& ifs);
	virtual void writefile(std::ofstream& ofs) const;
	virtual void write(std::ostream& os) const;
	virtual void read(std::istream &is);
};

#endif