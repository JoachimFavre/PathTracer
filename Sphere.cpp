#include "Sphere.h"

// Constructors
Sphere::Sphere()
	: Object3D(), center(0), radius(1) {}

Sphere::Sphere(const DoubleVec3D& center, double radius, Material* material)
	: Object3D(material), center(center), radius(radius) {}

Sphere::Sphere(const Sphere& sphere) 
	: Object3D(sphere), center(sphere.center), radius(sphere.radius) {}


// Getters
DoubleVec3D Sphere::getCenter() const { return center; }
double Sphere::getRadius() const { return radius; }


// Setters
void Sphere::setCenter(const DoubleVec3D& center) { this->center = center; }
void Sphere::setRadius(double radius) { this->radius = radius; }


// Virtual method
double Sphere::closestIntersection(const Ray& ray) const {
	// Returns -1 if no solution
	// Using quadratic equation formula to solve (meaning of a, b, c)
	// a = dotProd(rayDir, rayDir) but = 1
	DoubleVec3D differenceOriginCenter = ray.getOrigin() - center;
	double b = 2 * dotProd(ray.getDirection(), differenceOriginCenter);
	double c = dotProd(differenceOriginCenter, differenceOriginCenter) - radius * radius;

	double discriminant = b*b - 4*c;
	if (discriminant < 0.0)
		return -1.0;
	else if (discriminant == 0.0)
		return -b/2;
	else {
		double sqrt_discriminant = sqrt(discriminant);
		double twiceSolution1 = -b - sqrt_discriminant;
		if (twiceSolution1 > 0.0)
			return twiceSolution1/2; // smallest solution and is positive
		else
			return (-b + sqrt_discriminant)/2; // biggest solution but maybe positive
	}
}	

DoubleUnitVec3D Sphere::getNormal(const DoubleVec3D& point) const {
	return DoubleUnitVec3D((point - center)/radius, true);
}


DoubleVec3D Sphere::getRandomPoint(double (*randomDouble)()) const {
	DoubleVec3D point = randomVectorOnUnitRadiusSphere(randomDouble);
	return center + radius*point;
}
