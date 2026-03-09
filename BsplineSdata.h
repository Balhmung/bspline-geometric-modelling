#ifndef _BSPLINESDATA
#define _BSPLINESDATA

#include "bsplinesurf.h"
#include "sdata.h"



// class for encapsulating an interpolating or approximating Bspline surface
class BsplineSdata {
private:
	Sdata sdat;		// the Sdata object containing the data points and parameterisations
	BsplineSurf s;	// the underlying Bspline surface
public:
	// constructors
	BsplineSdata();
	BsplineSdata(const Sdata& data);
	BsplineSdata(const Sdata& data, int nsegu, int nsegv, int ordu, int ordv);

	// accessor method
	BsplineSurf getBspline() const;

	// methods to compute the interpolating and approximating surface
	void computeBsplineInterp();
	void computeBsplineLeastSq(int nsegu, int nsegv, int ordu, int ordv);
	double computeLSQError() const;
};

#endif
