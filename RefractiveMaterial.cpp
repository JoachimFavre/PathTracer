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
Material* RefractiveMaterial::deepCopy() const {
	return new RefractiveMaterial(refractiveIndex, getEmittance());
}

DoubleUnitVec3D RefractiveMaterial::getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const {
	DoubleUnitVec3D normalBis = normal;  // Must be modified
	DoubleUnitVec3D previousRayDirection = previousRay.getDirection();

	double refractiveIndex1 = 1.0;
	double refractiveIndex2 = 1.0;
	bool insideMedia = false;

	double cosIncidenceAngle = -dotProd(normalBis, previousRayDirection);
	if (cosIncidenceAngle < 0) {
		// Inside the media
		normalBis *= -1;
		cosIncidenceAngle *= -1;
		refractiveIndex1 = this->refractiveIndex;
		insideMedia = true;
	}
	else {
		refractiveIndex2 = this->refractiveIndex;
	}

	double refractiveQuotient = refractiveIndex1/refractiveIndex2;

	double cosRefractionAngleSquared = 1.0 - refractiveQuotient*refractiveQuotient*(1.0 - cosIncidenceAngle*cosIncidenceAngle);

	double reflectionProbNormal = pow((refractiveIndex1 - refractiveIndex2) / (refractiveIndex1 + refractiveIndex2), 2);  // Probability of reflection with normal incidence
	double reflectionProb = reflectionProbNormal + (1.0 - reflectionProbNormal)*pow(1.0 - cosIncidenceAngle, 5.0);  // Schlick's approximation

	if (cosRefractionAngleSquared > 0 && (insideMedia ||  randomDouble() > reflectionProb))
		// Refraction case
		return previousRayDirection*refractiveQuotient + normalBis*(refractiveQuotient*cosIncidenceAngle - sqrt(cosRefractionAngleSquared));  // Casted into DoubleUnitVec3D => normalised
	// Reflection case
	return previousRayDirection + normalBis*cosIncidenceAngle*2;  // Casted into DoubleUnitVec3D => normalised / cosIncidenceAngle = -cos that is in SpecularMaterial (why + instead of -)
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


// Virtual methods for json
std::string RefractiveMaterial::getType() const { return "Refractive"; }
json RefractiveMaterial::getSpecificParametersJson() const { return { { "RefractiveIndex", refractiveIndex } }; }
void RefractiveMaterial::setSpecificParametersJson(const json& j) { refractiveIndex = j["RefractiveIndex"].get<double>(); }
