#include "Material.h"

// Constructors
Material::Material()
	: colour(0), emittance(0) {}
Material::Material(const DoubleVec3D& colour, double emittance /*= 0*/)
	: colour(colour), emittance(emittance) {}
Material::Material(const Material& material) 
	: colour(material.colour), emittance(material.emittance) {}


// Getters & Setters
DoubleVec3D Material::getColour() const { return colour; }
double Material::getEmittance() const { return emittance; }
void Material::setColour(const DoubleVec3D& colour) { this->colour = colour; }
void Material::setEmittance(double emittance) { this->emittance = emittance; }
