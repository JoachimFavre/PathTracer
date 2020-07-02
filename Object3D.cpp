#include "Object3D.h"

// Constructors
Object3D::Object3D() : colour(0), brdf(BRDF::Diffuse), emittance(0) {}

Object3D::Object3D(const DoubleVec3& colour, BRDF brdf, double emittance /* = 0*/)
	: colour(colour), brdf(brdf), emittance(emittance) {}

Object3D::Object3D(const Object3D& obj) 
	: colour(obj.colour), brdf(obj.brdf), emittance(obj.emittance) {}


// Getters
DoubleVec3 Object3D::getColour() const { return colour; }
BRDF Object3D::getBRDF() const { return brdf; }
double Object3D::getEmittance() const { return emittance; }

// Setters
void Object3D::setColour(const DoubleVec3& colour) { this->colour = colour; }
void Object3D::setBRDF(BRDF brdf) { this->brdf = brdf; }
void Object3D::setEmittance(double emittance) { this->emittance = emittance; }
