#include "Sphere.h"

// Constructors
Sphere::Sphere() : Object3D(), center(0), radius(1) {}

Sphere::Sphere(const DoubleVec3& center, double radius, const DoubleVec3& colour, BRDF brdf, double emittance /*= 0*/)
	: Object3D(colour, brdf, emittance), center(center), radius(radius) {}

Sphere::Sphere(const Sphere& sphere) 
	: Object3D(sphere), center(sphere.center), radius(sphere.radius) {}


// Getters
DoubleVec3 Sphere::getCenter() const { return center; }
double Sphere::getRadius() const { return radius; }

// Setters
void Sphere::setCenter(const DoubleVec3& center) { this->center = center; }
void Sphere::setRadius(double radius) { this->radius = radius; }
