#include "DoubleVec3.h"

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

