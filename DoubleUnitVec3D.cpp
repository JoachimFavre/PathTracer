#include "DoubleUnitVec3D.h"

// Constructors
DoubleUnitVec3D::DoubleUnitVec3D()
	: DoubleVec3D(1, 0, 0) {}  // alerady normalised

DoubleUnitVec3D::DoubleUnitVec3D(double x, double y, double z, bool alreadyNormalised /* = false*/) 
	: DoubleVec3D(x, y, z) {
	if (!alreadyNormalised)
		normalise();
	else
		normalised = true;
}

DoubleUnitVec3D::DoubleUnitVec3D(const DoubleVec3D& vec, bool alreadyNormalised /* = false*/)
	: DoubleVec3D(vec) {
	if (!alreadyNormalised)
		normalise();
	else
		normalised = true;
}

DoubleUnitVec3D::DoubleUnitVec3D(const DoubleUnitVec3D& vec) 
	: DoubleVec3D(vec) {}  // already normalised


// Setter
void DoubleUnitVec3D::setVals(double x, double y, double z) {
	DoubleVec3D::setVals(x, y, z);
	normalise();
}


// Assignment operator
void DoubleUnitVec3D::operator=(const DoubleVec3D& vec) {
	DoubleVec3D::operator=(vec);
	normalise();
}


// Unary minus
DoubleUnitVec3D operator-(const DoubleUnitVec3D& vec) {
	return DoubleUnitVec3D(operator-((DoubleVec3D)vec), true);
}


// Other function
DoubleUnitVec3D randomVectorOnUnitRadiusSphere(double (*randomDouble)()) {
	double z = 2*randomDouble() - 1;
	double angle = 2*M_PI*randomDouble();
	double newRadius = sqrt(1 - z*z);
	return DoubleUnitVec3D(newRadius*cos(angle),
						   newRadius*sin(angle),
					       z, true);  // Already normalised
}
