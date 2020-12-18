#include "DiffuseMaterial.h"

// Constructors
DiffuseMaterial::DiffuseMaterial(const DoubleVec3D& albedo /*= DoubleVec3D(0.0)*/, DoubleVec3D emittance /*=0*/)
    : Material(emittance), albedo(albedo) {}

DiffuseMaterial::DiffuseMaterial(const DiffuseMaterial& material)
    : Material(material), albedo(material.albedo) {}


// Getters and setters
DoubleVec3D DiffuseMaterial::getAlbedo() const { return albedo; }
void DiffuseMaterial::setAlbedo(const DoubleVec3D& albedo) { this->albedo = albedo; }


// Virtual methods
Material* DiffuseMaterial::deepCopy() const {
    return new DiffuseMaterial(albedo, getEmittance());
}

DoubleUnitVec3D DiffuseMaterial::getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal) const {
    DoubleUnitVec3D newDirection(randomVectorOnUnitRadiusSphere());
    if (dotProd(newDirection, normal) < 0) // Wrong hemisphere
        return -newDirection;
    return newDirection;
}

DoubleVec3D DiffuseMaterial::computeCurrentRadiance(const DoubleVec3D& recursiveRadiance, double angleNewDirectionNormal, bool nextEventEstimation /*= false*/) const {
    DoubleVec3D albedo = getAlbedo();

    double neeFactor = 2.0;
    if (nextEventEstimation)
        neeFactor = 1.0 / M_PI;

    return DoubleVec3D(recursiveRadiance.getX()*albedo.getX(),
                       recursiveRadiance.getY()*albedo.getY(),
                       recursiveRadiance.getZ()*albedo.getZ())
                       * angleNewDirectionNormal * neeFactor;
}

bool DiffuseMaterial::worksWithNextEventEstimation() const {
    return true;
}

std::ostream& DiffuseMaterial::getDescription(std::ostream& stream) const {
    stream << "DiffuseMaterial / Albedo = " << albedo;
    return stream;
}


// Virtual methods for json
std::string DiffuseMaterial::getType() const { return "Diffuse"; }
json DiffuseMaterial::getSpecificParametersJson() const { return { { "Albedo", albedo } }; }
void DiffuseMaterial::setSpecificParametersJson(const json& j) { albedo = j["Albedo"].get<DoubleVec3D>(); }
