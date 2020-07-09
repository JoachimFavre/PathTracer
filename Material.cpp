#include "Material.h"

// Constructors
Material::Material(double emittance /*= 0*/)
	: emittance(emittance) {}

Material::Material(const Material& material) 
	: emittance(material.emittance) {}


// Getters & Setters
double Material::getEmittance() const { return emittance; }
void Material::setEmittance(double emittance) { this->emittance = emittance; }
