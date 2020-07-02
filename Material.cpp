#include "Material.h"

// Constructors
Material::Material() : colour(0), brdf(BRDF::Diffuse), emittance(0) {}

Material::Material(const DoubleVec3& colour, BRDF brdf, double emittance /* = 0*/)
	: colour(colour), brdf(brdf), emittance(emittance) {}

Material::Material(const Material& material) 
	: colour(material.colour), brdf(material.brdf), emittance(material.emittance) {}


// Getters
DoubleVec3 Material::getColour() const { return colour; }
BRDF Material::getBRDF() const { return brdf; }
double Material::getEmittance() const { return emittance; }

// Setters
void Material::setColour(const DoubleVec3& colour) { this->colour = colour; }
void Material::setBRDF(BRDF brdf) { this->brdf = brdf; }
void Material::setEmittance(double emittance) { this->emittance = emittance; }
