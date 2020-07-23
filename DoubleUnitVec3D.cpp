#include "DoubleUnitVec3D.h"

// Constructors
DoubleUnitVec3D::DoubleUnitVec3D()
	: DoubleVec3D(1, 0, 0) {}  // alerady normalised

DoubleUnitVec3D::DoubleUnitVec3D(double x, double y, double z) 
	: DoubleVec3D(x, y, z) {
	normalise();
}

DoubleUnitVec3D::DoubleUnitVec3D(const DoubleVec3D& vec)
	: DoubleVec3D(vec) {
	normalise();
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
