#include "DiffuseMaterial.h"

// Constructors
DiffuseMaterial::DiffuseMaterial()
	: Material() {}

DiffuseMaterial::DiffuseMaterial(const DoubleVec3D& colour, double emittance /*=0*/)
	: Material(colour, emittance) {}

DiffuseMaterial::DiffuseMaterial(const DiffuseMaterial& material)
	: Material(material) {}


// Virtual methods
DoubleVec3D DiffuseMaterial::getNewDirection(const Ray& previousRay, const DoubleVec3D& normal, double (*randomDouble)()) const {
	double theta = M_PI*(randomDouble() - 0.5);
	double phi = M_PI*(randomDouble() - 0.5);
	DoubleVec3D newDirection(sin(theta)*cos(phi),
		                     sin(theta)*sin(phi),
		                     cos(theta));  // random vector on sphere of radius 1

	if (dotProd(newDirection, normal) < 0) // Wrong hemisphere
		return -newDirection;
	return newDirection;
}

DoubleVec3D DiffuseMaterial::computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const {
	DoubleVec3D colour = getColour();
	return DoubleVec3D(recursiveColour.getX()*colour.getX(),
				       recursiveColour.getY()*colour.getY(),
		               recursiveColour.getZ()*colour.getZ())
		               * angleNewDirectionNormal / M_PI / M_PI;
}
