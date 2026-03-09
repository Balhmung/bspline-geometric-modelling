#ifndef _ABS_SURFACE
#define _ABS_SURFACE

#include "textobject.h"
#include "matrix.h"

// abstract base curve template class encapsulating a generic surface defined by two limits in u and two in v
// pure virtual methods are the read/write functions and the overloaded operator for evaluation of the surface at a point
template<class T>
class AbsSurface : public TextObject
{
private:
	double u1; // left limitu
	double u2; // right limitu
	double v1; // left limitv
	double v2; // right limitv
public:
	// constructors
	AbsSurface();
	AbsSurface(double umin, double umax, double vmin, double vmax);

	// pure virtual overloaded opeator for evaluation of the surface at a point
	virtual T operator()(double, double) const = 0;

	// compute a matrix of points over the surface
	virtual Matrix<T> computePoints(int m, int n) const;

	// accessor methods
	virtual double getLeftLimitU() const;
	virtual double getRightLimitU() const;
	virtual double getLeftLimitV() const;
	virtual double getRightLimitV() const;

	// pure virtual read/write methods
	virtual void read(std::istream& is) = 0;
	virtual void readfile(std::ifstream& ifs) = 0;
	virtual void writefile(std::ofstream& ofs) const = 0;
	virtual void write(std::ostream& os) const = 0;
};


// implementation of the constructors
template<class T>
AbsSurface<T>::AbsSurface<T>() : u1(0.0), u2(0.0), v1(0.0), v2(0.0) {}


template<class T>
AbsSurface<T>::AbsSurface<T>(double umin, double umax, double vmin, double vmax): u1(umin), u2(umax), v1(vmin), v2(vmax) {} 


// compute a matrix of points across the surface using the overloaded operator for evaluation
template<class T>
Matrix<T> AbsSurface<T>::computePoints(int m, int n) const
{
	Matrix<T> mat(m,n);

	double stepu = (u2-u1)/(double)(m-1);
	double stepv = (v2-v1)/(double)(n-1);
	
	// evaluate
	double valu, valv;
	
	for (int i=0; i<m; i++) {
		valu = u1+i*stepu;
		for (int j=0; j<n; j++) {
			valv = v1+j*stepv;
			mat[i][j] = (*this)(valu,valv);
		}
	}
	return mat;
}

// accessor methods
template<class T>
double AbsSurface<T>::getLeftLimitU() const
{
	return u1;
}


template<class T>
double AbsSurface<T>::getRightLimitU() const
{
	return u2;
}

template<class T>
double AbsSurface<T>::getLeftLimitV() const
{
	return v1;
}


template<class T>
double AbsSurface<T>::getRightLimitV() const
{
	return v2;
}

#endif