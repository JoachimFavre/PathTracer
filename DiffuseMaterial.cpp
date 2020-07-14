#include "DiffuseMaterial.h"

// Constructors
DiffuseMaterial::DiffuseMaterial(const DoubleVec3D& colour /*= DoubleVec3D(0.0)*/, double emittance /*=0*/)
	: Material(emittance), colour(colour) {}

DiffuseMaterial::DiffuseMaterial(const DiffuseMaterial& material)
	: Material(material), colour(material.colour) {}


// Getters and setters
DoubleVec3D DiffuseMaterial::getColour() const { return colour; }
void DiffuseMaterial::setColour(const DoubleVec3D& colour) { this->colour = colour; }


// Virtual methods
DoubleVec3D DiffuseMaterial::getNewDirection(const Ray& previousRay, const DoubleVec3D& normal, double (*randomDouble)()) const {
	double theta = 2*M_PI*randomDouble();
	double phi = 2*M_PI*randomDouble();
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
