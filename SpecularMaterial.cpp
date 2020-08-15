#include "SpecularMaterial.h"

// Constructors
SpecularMaterial::SpecularMaterial(DoubleVec3D emittance /*= 0*/)
	: Material(emittance) {}

SpecularMaterial::SpecularMaterial(const SpecularMaterial& material)
	: Material(material) {}


// Virtual methods
Material* SpecularMaterial::deepCopy() const {
	return new SpecularMaterial(getEmittance());
}

DoubleUnitVec3D SpecularMaterial::getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const {
	DoubleUnitVec3D previousRayDirection = previousRay.getDirection();
	return previousRayDirection - normal*dotProd(previousRayDirection, normal)*2;
}

DoubleVec3D SpecularMaterial::computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const {
	return recursiveColour;
}

bool SpecularMaterial::worksWithNextEventEstimation() const {
	return false;
}

std::ostream& SpecularMaterial::getDescription(std::ostream& stream) const {
	stream << "SpecularMaterial";
	return stream;
}


// Virtual methods for json
std::string SpecularMaterial::getType() const { return "Specular"; }
json SpecularMaterial::getSpecificParametersJson() const { return {}; }
void SpecularMaterial::setSpecificParametersJson(const json& j) {}
