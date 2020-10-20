#include "DiffuseMaterial.h"

// Constructors
DiffuseMaterial::DiffuseMaterial(const DoubleVec3D& colour /*= DoubleVec3D(0.0)*/, DoubleVec3D emittance /*=0*/)
	: Material(emittance), colour(colour) {}

DiffuseMaterial::DiffuseMaterial(const DiffuseMaterial& material)
	: Material(material), colour(material.colour) {}


// Getters and setters
DoubleVec3D DiffuseMaterial::getColour() const { return colour; }
void DiffuseMaterial::setColour(const DoubleVec3D& colour) { this->colour = colour; }


// Virtual methods
Material* DiffuseMaterial::deepCopy() const {
	return new DiffuseMaterial(colour, getEmittance());
}

DoubleUnitVec3D DiffuseMaterial::getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const {
	DoubleUnitVec3D newDirection(randomVectorOnUnitRadiusSphere(randomDouble));
	if (dotProd(newDirection, normal) < 0) // Wrong hemisphere
		return -newDirection;
	return newDirection;
}

DoubleVec3D DiffuseMaterial::computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const {
	DoubleVec3D colour = getColour();
	return DoubleVec3D(recursiveColour.getX()*colour.getX(),
				       recursiveColour.getY()*colour.getY(),
		               recursiveColour.getZ()*colour.getZ())
		               * angleNewDirectionNormal * 2;
}

bool DiffuseMaterial::worksWithNextEventEstimation() const {
	return true;
}

std::ostream& DiffuseMaterial::getDescription(std::ostream& stream) const {
	stream << "DiffuseMaterial / Colour = " << colour;
	return stream;
}


// Virtual methods for json
std::string DiffuseMaterial::getType() const { return "Diffuse"; }
json DiffuseMaterial::getSpecificParametersJson() const { return { { "Colour", colour } }; }
void DiffuseMaterial::setSpecificParametersJson(const json& j) { colour = j["Colour"].get<DoubleVec3D>(); }
