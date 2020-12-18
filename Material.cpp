#include "Material.h"

// Constructors
Material::Material(DoubleVec3D emittance /*= 0*/)
    : emittance(emittance) {}

Material::Material(const Material& material) 
    : emittance(material.emittance) {}


// Getters & Setters
DoubleVec3D Material::getEmittance() const { return emittance; }
void Material::setEmittance(DoubleVec3D emittance) { this->emittance = emittance; }


// Ostream operator
std::ostream& operator<<(std::ostream& stream, const Material& material) {
    return material.getDescription(stream) << " / Emittance = " << material.getEmittance();
}
