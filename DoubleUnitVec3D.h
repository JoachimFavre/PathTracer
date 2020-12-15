#ifndef DEF_DOUBLEUNITVEC3D
#define DEF_DOUBLEUNITVEC3D

#include "DoubleVec3D.h"

/*!
	\file DoubleUnitVec3D.h
	\brief Defines the DoubleUnitVec3D class and the functions around it.

	\class DoubleUnitVec3D
	\brief A three-dimensional unit vector using doubles.
	\details Inherits of the class DoubleVec3D. Each time a value is changed, automatically calls the normalise() method.

	\fn DoubleUnitVec3D::DoubleUnitVec3D()
	\brief Default constructor.
	\details Sets the vector to (1, 0, 0).

	\fn DoubleUnitVec3D::DoubleUnitVec3D(double x, double y, double z, bool alreadyNormalised = false)
	\brief Main constructor.
	\param x The first coordinate.
	\param y The second coordinate.
	\param z The third coordinate.
	\param alreadyNormalised If true, skips the normalisation when instantiated.
	\sa normalise()

	\fn DoubleUnitVec3D::DoubleUnitVec3D(const DoubleVec3D& vec, bool alreadyNormalised = false)
	\brief Converting constructor for the DoubleVec3D class.
	\param vec The vector that will be converted.
	\param alreadyNormalised If true, skips the normalisation when instantiated.
	\sa normalise()

	\fn DoubleUnitVec3D(const DoubleUnitVec3D& vec)
	\brief Copy constructor.
	\param vec The unit vector that will be copied.

	\fn DoubleUnitVec3D::setVals(double x, double y, double z)
	\brief Setter for all coordinates.
	\details Calls the normalisation method after this one.
	\param x The first coordinate.
	\param y The second coordinate.
	\param z The third coordinate.
	\sa normalise()

	\fn DoubleUnitVec3D::operator=(const DoubleVec3D& vec)
	\brief Assignment operator.
	\param vec The vector to which this will be equal.

	\fn operator-(const DoubleUnitVec3D& vec)
	\brief Unary minus.
	\details Allows to skip the conversion from DoubleVec3D to DoubleUnitVec3D.
	\param vec The vector that will be inversed.
	\return The inverse of vec.

	\fn randomVectorOnUnitRadiusSphere()
	\brief Generates a random unit vector on a sphere.
	\return A random unit vector on a sphere.
*/

class DoubleUnitVec3D : public DoubleVec3D
{
public:
	DoubleUnitVec3D();
	DoubleUnitVec3D(double x, double y, double z, bool alreadyNormalised = false);
	DoubleUnitVec3D(const DoubleVec3D& vec, bool alreadyNormalised = false);
	DoubleUnitVec3D(const DoubleUnitVec3D& vec);

	virtual void setVals(double x, double y, double z);
	void operator=(const DoubleVec3D& vec);
};

DoubleUnitVec3D operator-(const DoubleUnitVec3D& vec);
DoubleUnitVec3D randomVectorOnUnitRadiusSphere();

#endif
