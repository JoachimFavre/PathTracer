#include "RefractiveMaterial.h"


// Constructors
RefractiveMaterial::RefractiveMaterial(double refractiveIndex /*= 1.5*/, DoubleVec3D emittance /*= 0*/)
	: Material(emittance), refractiveIndex(refractiveIndex) {}

RefractiveMaterial::RefractiveMaterial(const RefractiveMaterial& material)
	: Material(material), refractiveIndex(material.refractiveIndex) {}


// Getters and setters
double RefractiveMaterial::getRefractiveIndex() const { return refractiveIndex; }
void RefractiveMaterial::setRefractiveIndex(double refractiveIndex) { this->refractiveIndex = refractiveIndex; }


// Virtual methods
DoubleUnitVec3D RefractiveMaterial::getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const {
	double refractiveIndex = this->refractiveIndex;  // Must be modified
	DoubleUnitVec3D normalBis = normal;  // Must be modified
	DoubleUnitVec3D previousRayDirection = previousRay.getDirection();

	double reflectionProbNormal = pow((1.0 - refractiveIndex) / (1 + refractiveIndex), 2);  // Probability of reflection with normal incidence

	double cosFirstAngle = -dotProd(normalBis, previousRayDirection);  // Cosine of first angle
	if (cosFirstAngle < 0)  // Not on right side of surface
		normalBis *= -1;
	else
		refractiveIndex = 1 / refractiveIndex;

	double cosSecondAngle = 1.0 - refractiveIndex*refractiveIndex*(1.0 - cosFirstAngle*cosFirstAngle);  // 3D <=> 2 angles
	double reflectionProb = reflectionProbNormal + (1.0 - reflectionProbNormal)*pow(1.0 - cosFirstAngle, 5.0);  // Schlick's approximation

	if (cosSecondAngle > 0 && randomDouble() > reflectionProb)
		// Refraction case
		return previousRayDirection*refractiveIndex + normalBis*(refractiveIndex*cosFirstAngle - sqrt(cosSecondAngle));  // Casted into DoubleUnitVec3D => normalised
	// Reflection case
	return previousRayDirection + normalBis*cosFirstAngle*2;  // Casted into DoubleUnitVec3D => normalised
}


DoubleVec3D RefractiveMaterial::computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const {
	return recursiveColour;
}


bool RefractiveMaterial::worksWithNextEventEstimation() const {
	return false;
}


std::ostream& RefractiveMaterial::getDescription(std::ostream& stream) const {
	stream << "RefractiveMaterial / refractiveIndex = " << refractiveIndex;
	return stream;
}
