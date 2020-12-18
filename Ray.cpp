#include "Ray.h"

// Constructors
Ray::Ray() : origin(0), direction(1, 0, 0) {}

Ray::Ray(const DoubleVec3D& origin, const DoubleUnitVec3D& direction)
    : origin(origin), direction(direction) {}

Ray::Ray(const Ray& ray)
    : origin(ray.origin), direction(ray.direction) {}


// Getters
DoubleVec3D Ray::getOrigin() const { return origin; }
DoubleUnitVec3D Ray::getDirection() const {    return direction; }


// Setters
void Ray::setOrigin(const DoubleVec3D& origin) { this->origin = origin; }
void Ray::setDirection(const DoubleUnitVec3D& direction) { this->direction = direction; }

