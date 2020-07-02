#include "DoubleVec3.h"

// Constructors
DoubleVec3::DoubleVec3(double val /*= 0*/) : x(val), y(val), z(val) {}

DoubleVec3::DoubleVec3(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

DoubleVec3::DoubleVec3(const DoubleVec3& vec) {
	this->x = vec.getX();
	this->y = vec.getY();
	this->z = vec.getZ();
}


// Getters
double DoubleVec3::getX() const { return this->x; }
double DoubleVec3::getY() const { return this->y; }
double DoubleVec3::getZ() const { return this->z; }


// Setters
void DoubleVec3::setX(double x) { this->x = x; }
void DoubleVec3::setY(double y) { this->y = y; }
void DoubleVec3::setZ(double z) { this->z = z; }

void DoubleVec3::setVals(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
