#include "SpecularMaterial.h"

// Constructors
SpecularMaterial::SpecularMaterial(double emittance /*= 0*/)
	: Material(emittance) {}

SpecularMaterial::SpecularMaterial(const SpecularMaterial& material)
	: Material(material) {}


// Virtual methods
DoubleVec3D SpecularMaterial::getNewDirection(const Ray& previousRay, const DoubleVec3D& normal, double (*randomDouble)()) const {
	DoubleVec3D previousRayDirection = previousRay.getDirection();
	return previousRayDirection - normal*dotProd(previousRayDirection, normal)*2;
}

DoubleVec3D SpecularMaterial::computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const {
	return recursiveColour;
}


bool SpecularMaterial::worksWithNextEventEstimation() const {
	return false;
}
