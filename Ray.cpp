#include "Ray.h"

// Constructors
Ray::Ray() : origin(0), direction(1, 0, 0) {}

Ray::Ray(const DoubleVec3& origin, const DoubleVec3& direction)
	: origin(origin), direction(direction) {
	this->direction.normalise();
}

Ray::Ray(const Ray& ray) {
	this->origin = ray.getOrigin();
	this->direction = ray.getDirection();
}


// Getters
DoubleVec3 Ray::getOrigin() const {
	return origin;
}

DoubleVec3 Ray::getDirection() const {
	return direction;
}


// Setters
void Ray::setOrigin(const DoubleVec3& origin) {
	this->origin = origin;
}

void Ray::setDirection(const DoubleVec3& direction) {
	this->direction = direction;
	this->direction.normalise();
}

