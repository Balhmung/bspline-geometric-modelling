#include "bsplinesdata.h"
#include "bsplinecdata.h"
#include "cdata.h"

// constructors for the BsplineSdata class
BsplineSdata::BsplineSdata() : sdat(), s() {}

BsplineSdata::BsplineSdata(const Sdata& data) : sdat(data), s() 
{
	computeBsplineInterp();
}

BsplineSdata::BsplineSdata(const Sdata& data, int nsegu, int nsegv, int ordu, int ordv) : sdat(data)
{
	computeBsplineLeastSq(nsegu, nsegv, ordu, ordv);
}

// accessor method
BsplineSurf BsplineSdata::getBspline() const
{
	return s;
}


// computes the BsplineSurf interpolating to the data set 
void BsplineSdata::computeBsplineInterp()
{
	// step 1 (orders)
	// declare two int variables called ordu and ordv and set them equal to 4
	int ordu = 4;
	int ordv = 4;

	// step 2 (parameterisation)
	// declare two Vector<double> variables called paramu and paramv and set them equal to
	// the result of calling the methods getParamU() and getParamV() for the sdat data object
	Vector<double> paramu = sdat.getParamU();
	Vector<double> paramv = sdat.getParamV();



	// step 3 (number of points in u and v)
	// declare two int variables called numu and numv and set them equal to the result of 
	// calling the methods getNumU() and getNumV() on the sdat data object
	int numu = sdat.getNumU();
	int numv = sdat.getNumV();

	// step 4 (dimension in u and v)
	// declare two int variables called dimu and dimv and set them equal to the dimension in each direction
	int dimu = (numu - 1) * ordu - (numu - 2) * (ordu - 1);
	int dimv = (numv - 1) * ordv - (numv - 2) * (ordv - 1);


	// step 5 (get the data points)
	// declare a Matrix<Point3D> variable called data and set it equal to the result of calling
	// the method getPoints on the sdat data object
	Matrix<Point3D> datapts = sdat.getPoints();

	// step 6 (matrices to hold the control points from the two interpolation steps)
	// declare two Matrix<Point3D> variables called temp and final of size (numu, dimv) and 
	// (dimu, dimv) respectively
	Matrix<Point3D> temp(numu, dimv);
	Matrix<Point3D> final(dimu, dimv);

	// step 7 (knots)
	// delcare two Vector<double> variables called knotsu and knotsv with default constructor
	Vector<double> knotsu, knotsv;

	// step 8 
	// declare two BsplineCurve objects called b1 and b2 (default constructor) 
	BsplineCurve b1, b2;

	// first interpolation step
	// interpolate to the data set in the v direction for varying u
	for (int i = 0; i<numu; i++) {
		
		// step 9
		// declare a Vector<Point3D> variables called vpts of size numv
		Vector<Point3D> vpts(numv);

		// step 10 (get the data for the curve interpolation)
		// using a for loop from j=0 to j<numv copy the data[i][j] into vpts[j]
		for (int j = 0; j < numv; j++) vpts[j] = datapts[i][j];

		// step 11
		// declare a Cdata object called cdat intialised with numv and vpts
		Cdata cdat(numv, vpts);


		// step 12
		// declare a BsplineCdata object called curve initialised with cdat
		BsplineCdata curve(cdat);

		// step 13
		// set the BsplineCurve object b1 equal to the result of calling
		// getBspline() on the BsplineCdata object curve
		b1 = curve.getBspline();

		// step 14
		// declare a Vector<Point3D> variables called cpts and set it equal to the result of calling
		// getCpoints() on the BsplineCurve object b1
		Vector<Point3D> cpts = b1.getCpoints();

		// step 15
		// use a for loop from j=0, j<dimv to copy the elements cpts[j] into temp[i][j]
		for (int j = 0; j < dimv; j++) temp[i][j] = cpts[j];
	}

	// step 16 (knot set in v)
	// set knotsv equal to the result of calling getKnots() on the BsplineCurve object b1
	knotsv = b1.getKnots();

	// interpolate to the control points obtained from the first loop 
	for (int j = 0; j<dimv; j++) {
		
		// step 17
		// declare a Vector<Point3D> variable called upts of size numu
		Vector<Point3D> upts(numu);

		// step 18
		// use a for loop from i=0, i<numu to copy temp[i][j] into upts[i]		
		for (int i = 0; i < numu; i++) upts[i] = temp[i][j];

		// step 19
		// declare an object of Cdata called cdat with upts and numu as arguments to the constructor
		Cdata cdat(numu, upts);

		// step 20
		// declare a BsplineCdata object called curve initialised with cdat
		BsplineCdata curve(cdat);

		// step 21
		// set the BsplineCurve object b2 equal to the result of calling
		// getBspline() on the BsplineCdata object curve
		b2 = curve.getBspline();

		// step 22
		// declare a Vector<Point3D> variables called cpts and set it equal to the result of calling
		// getCpoints() on the BsplineCurve object b2
		Vector<Point3D> cpts = b2.getCpoints();

		// step 23
		// use a for loop from i=0, i<dimu to copy the elements cpts[i] into final[i][j]
		for (int i = 0; i < dimu; i++) final[i][j] = cpts[i];
	}

	// step 24 (knot set in u)
	// set knotsu equal to the result of calling getKnots() on the BsplineCurve object b2
	knotsu = b2.getKnots();

	// step 25
	// assign the BsplineSurf object s to BsplineSurf(paramu[0], paramu[numu - 1], paramv[0], paramv[numv - 1], ordu, ordv, dimu, dimv, final, knotsu, knotsv);
	s = BsplineSurf(paramu[0], paramu[numu - 1], paramv[0], paramv[numv - 1], ordu, ordv, dimu, dimv, final, knotsu, knotsv);
}




// computes the least squares BsplineSurf approoximation ot the data set consisting of nsegu, nsegv segemnts in u and v and orders ordu, ordv in u and v
void BsplineSdata::computeBsplineLeastSq(int nsegu, int nsegv, int ordu, int ordv)
{
	// TO DO
	// step 1 (orders)
	// this step is not required as the ordu, ordv are assed into this function


	// step 2 (parameterisation)
	// declare two Vector<double> variables called paramu and paramv and set them equal to
	// the result of calling the methods getParamU() and getParamV() for the sdat data object
	Vector<double> paramu = sdat.getParamU();
	Vector<double> paramv = sdat.getParamV();


	// step 3 (number of points in u and v)
	// declare two int variables called numu and numv and set them equal to the result of 
	// calling the methods getNumU() and getNumV() on the sdat data object
	int numu = sdat.getNumU();
	int numv = sdat.getNumV();


	// step 4 (dimension in u and v)
	// declare two int variables called dimu and dimv and set them equal to the dimension in each direction (you need to compute these
	// based on the number of segments in u and v and the order in u and v)
	int dimu = (nsegu * ordu) - (nsegu - 1) * (ordu - 1);
	int dimv = (nsegv * ordv) - (nsegv - 1) * (ordv - 1);

	// step 5 (get the data points)
	// declare a Matrix<Point3D> variable called data and set it equal to the result of calling
	// the method getPoints on the sdat data object
	Matrix<Point3D> datapts = sdat.getPoints();

	// step 6 (matrices to hold the control points from the two interpolation steps)
	// declare two Matrix<Point3D> variables called temp and final of size (numu, dimv) and 
	// (dimu, dimv) respectively
	Matrix<Point3D> temp(numu, dimv);
	Matrix<Point3D> final(dimu, dimv);

	// step 7 (knots)
	// delcare two Vector<double> variables called knotsu and knotsv with default constructor
	Vector<double> knotsu, knotsv;

	// step 8 
	// declare two BsplineCurve objects called b1 and b2 (default constructor) 
	BsplineCurve b1, b2;

	// first approximation step
	// approximate to the data set in the v direction for varying u
	for (int i = 0; i < numu; i++) {
		// step 9
		// declare a Vector<Point3D> variables called vpts of size numv
		Vector<Point3D> vpts(numv);

		// step 10 (get the data for the curve interpolation)
		// using a for loop from j=0 to j<numv copy the data[i][j] into vpts[j]
		for (int j = 0; j < numv; j++) vpts[j] = datapts[i][j];

		// step 11
		// declare a Cdata object called cdat intialised with numv and vpts
		Cdata cdat(numv, vpts);

		// step 12
		// declare a BsplineCdata object called curve initialised with cdat, number of segments in v, order in v
		BsplineCdata curve(cdat,nsegv,ordv);

		// step 13
		// set the BsplineCurve object b1 equal to the result of calling
		// getBspline() on the BsplineCdata object curve
		b1 = curve.getBspline();

		// step 14
		// declare a Vector<Point3D> variables called cpts and set it equal to the result of calling
		// getCpoints() on the BsplineCurve object b1
		Vector<Point3D> cpts = b1.getCpoints();

		// step 15
		// use a for loop from j=0, j<dimv to copy the elements cpts[j] into temp[i][j]
		for (int j = 0; j < dimv; j++) temp[i][j] = cpts[j];
	}

	// step 16 (knot set in v)
	// set knotsv equal to the result of calling getKnots() on the BsplineCurve object b1
	knotsv = b1.getKnots();

	// interpolate to the control points obtained from the first loop 
	for (int j = 0; j < dimv; j++) {

		// step 17
		// declare a Vector<Point3D> variable called upts of size numu
		Vector<Point3D> upts(numu);

		// step 18
		// use a for loop from i=0, i<numu to copy temp[i][j] into upts[i]		
		for (int i = 0; i < numu; i++) upts[i] = temp[i][j];

		// step 19
		// declare an object of Cdata called cdat with upts and numu as arguments to the constructor
		Cdata cdat(numu, upts);

		// step 20
		// declare a BsplineCdata object called curve initialised with cdat, number of segments in u, order in u
		BsplineCdata curve(cdat,nsegu,ordu);
		

		// step 21
		// set the BsplineCurve object b2 equal to the result of calling getBspline() on the BsplineCdata object curve
		b2 = curve.getBspline();

		// step 22
		// declare a Vector<Point3D> variables called cpts and set it equal to the result of calling
		// getCpoints() on the BsplineCurve object b2
		Vector<Point3D> cpts = b2.getCpoints();

		// step 23
		// use a for loop from i=0, i<dimu to copy the elements cpts[i] into final[i][j]
		for (int i = 0; i < dimu; i++) final[i][j] = cpts[i];
	}

	// step 24 (knot set in u)
	// set knotsu equal to the result of calling getKnots() on the BsplineCurve object b2
	knotsu = b2.getKnots();

	// step 25
	// assign the BsplineSurf object s to BsplineSurf(paramu[0], paramu[numu - 1], paramv[0], paramv[numv - 1], ordu, ordv, dimu, dimv, final, knotsu, knotsv)
	s = BsplineSurf(paramu[0], paramu[numu - 1], paramv[0], paramv[numv - 1], ordu, ordv, dimu, dimv, final, knotsu, knotsv);

}


double BsplineSdata::computeLSQError() const
{
	Matrix<Point3D> pts = sdat.getPoints();

	Vector<double> paramu = sdat.getParamU();
	Vector<double> paramv = sdat.getParamV();

	double sum = 0.0;
	for (int i = 0; i < pts.getNrows(); i++)
		for (int j = 0; j < pts.getNcols(); j++) {
			double dist = (pts[i][j].getX() - s(paramu[i], paramv[j]).getX()) * (pts[i][j].getX() - s(paramu[i], paramv[j]).getX()) +
				(pts[i][j].getY() - s(paramu[i], paramv[j]).getY()) * (pts[i][j].getY() - s(paramu[i], paramv[j]).getY()) +
				(pts[i][j].getZ() - s(paramu[i], paramv[j]).getZ()) * (pts[i][j].getZ() - s(paramu[i], paramv[j]).getZ());
			sum = sum + dist;
		}
	return sqrt(sum / (pts.getNrows() * pts.getNcols()));
}