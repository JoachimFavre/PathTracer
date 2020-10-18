#ifndef DEF_DOUBLEUNITVEC3D
#define DEF_DOUBLEUNITVEC3D

#include "DoubleVec3D.h"

//! A three-dimensional unit vector using doubles.
/*!
	Inherits of the class DoubleVec3D. Each time a value is changed, automatically calls the normalise() method.
*/
class DoubleUnitVec3D : public DoubleVec3D
{
public:
	//! Default constructor.
	/*!
		Sets the vector to (1, 0, 0).
	*/
	DoubleUnitVec3D();

	//! Main constructor.
	/*!
		\param x The first coordinate.
		\param y The second coordinate.
		\param z The third coordinate.
		\param alreadyNormalised If true, skips the normalisation when instantiated. 
		\sa normalise()
	*/
	DoubleUnitVec3D(double x, double y, double z, bool alreadyNormalised = false);

	//! Converting constructor for the DoubleVec3D class.
	/*!
		\param vec The vector that will be converted.
		\param alreadyNormalised If true, skips the normalisation when instantiated.
		\sa normalise()
	*/
	DoubleUnitVec3D(const DoubleVec3D& vec, bool alreadyNormalised = false);

	//! Copy constructor.
	/*!
		\param vec The unit vector that will be copied.
	*/
	DoubleUnitVec3D(const DoubleUnitVec3D& vec);

	//! Setter for all coordinates.
	/*!
		Calls the normalisation method after this one.
		\param x The first coordinate.
		\param y The second coordinate.
		\param z The third coordinate.
		\sa normalise()
	*/
	virtual void setVals(double x, double y, double z);

	//! Assignment operator.
	/*!
		\param vec The vector to which this will be equal.
	*/
	void operator=(const DoubleVec3D& vec);
};

//! Unary minus.
/*!
	Allows to skip the conversion from DoubleVec3D to DoubleUnitVec3D.
	\param vec The vector that will be inversed.
	\return The inverse of vec.
*/
DoubleUnitVec3D operator-(const DoubleUnitVec3D& vec);

//! Generates a random unit vector on a sphere.
/*!
	\param randomDouble A pointer to a function generating a random double between 0 and 1.
	\return A random unit vector on a sphere.
*/
DoubleUnitVec3D randomVectorOnUnitRadiusSphere(double (*randomDouble)());

#endif
