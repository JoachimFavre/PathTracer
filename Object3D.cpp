#include "Object3D.h"

// Constructors
Object3D::Object3D() : colour(0), brdf(BRDF::Diffuse), emittance(0) {}

Object3D::Object3D(const DoubleVec3& colour, BRDF brdf, double emittance /* = 0*/)
	: colour(colour), brdf(brdf), emittance(emittance) {}

Object3D::Object3D(const Object3D& obj) 
	: colour(obj.colour), brdf(obj.brdf), emittance(obj.emittance) {}
