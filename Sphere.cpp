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

// Virtual functions
double Sphere::closestIntersection(const Ray& ray) const {
	// Returns -1 if no solution
	// Using quadratic equation formula to solve (meaning of a, b, c)
	// a = dotProd(rayDir, rayDir) but = 1
	DoubleVec3 differenceOriginCenter = ray.getOrigin() - center;
	double b = 2 * dotProd(ray.getDirection(), differenceOriginCenter);
	double c = dotProd(differenceOriginCenter, differenceOriginCenter) - radius * radius;

	double discriminant = b*b - 4*c;
	if (discriminant < 0)
		return -1;
	else if (discriminant == 0)
		return -b/2;
	else {
		double sqrt_discriminant = sqrt(discriminant);
		double twiceSolution1 = -b - sqrt_discriminant;
		if (twiceSolution1 > 0)
			return twiceSolution1/2; // smallest solution and is positive
		else
			return (-b + sqrt_discriminant)/2; // biggest solution but maybe positive
	}
}

DoubleVec3 Sphere::getNormal(const DoubleVec3& point) const {
	DoubleVec3 normal(point.getX() - center.getX(),
					  point.getY() - center.getY(),
					  point.getZ() - center.getZ());
	return normal/radius; // normalised
}
