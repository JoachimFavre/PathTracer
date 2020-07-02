#include "DoubleVec3.h"

// Constructors
DoubleVec3::DoubleVec3(double val /*= 0*/) : x(val), y(val), z(val) {}

DoubleVec3::DoubleVec3(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

DoubleVec3::DoubleVec3(const DoubleVec3& vec) {
	this->setVals(vec.getX(), vec.getY(), vec.getZ());
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

// Operators
void DoubleVec3::operator+=(const DoubleVec3& vec) {
	x += vec.getX();
	y += vec.getY();
	z += vec.getZ();
}

void DoubleVec3::operator-=(const DoubleVec3& vec) { this->operator+=(-vec); }

void DoubleVec3::operator*=(const double& val) {
	x *= val;
	y *= val;
	z *= val;
}

void DoubleVec3::operator/=(const double& val) { this->operator*=(1 / val); }


// Functions
// Vector operators
DoubleVec3 operator+(const DoubleVec3& vec1, const DoubleVec3& vec2) {
	DoubleVec3 result = vec1;
	result += vec2;
	return result;
}

DoubleVec3 operator-(const DoubleVec3& vec) {
	DoubleVec3 result = vec;
	result *= -1;
	return result;
}

DoubleVec3 operator-(const DoubleVec3& vec1, const DoubleVec3& vec2) {
	DoubleVec3 result = vec1;
	result -= vec2;
	return result;
}

// Scalar operators
DoubleVec3 operator*(const DoubleVec3& vec, const double& val) {
	DoubleVec3 result = vec;
	result *= val;
	return result;
}

DoubleVec3 operator*(const double& val, const DoubleVec3& vec) { return operator*(vec, val); }

DoubleVec3 operator/(const DoubleVec3& vec, const double& val) {
	DoubleVec3 result = vec;
	result /= val;
	return result;
}


// ostream operator
std::ostream& operator<<(std::ostream& stream, const DoubleVec3& vec) {
	stream << "(" << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ")";
	return stream;
}


// Other functions
DoubleVec3 crossProd(const DoubleVec3& vec1, const DoubleVec3& vec2) {
	double x = vec1.getY()*vec2.getZ() - vec1.getZ()*vec2.getY();
	double y = vec1.getZ()*vec2.getX() - vec1.getX()*vec2.getZ();
	double z = vec1.getX()*vec2.getY() - vec1.getY()*vec2.getX();
	return DoubleVec3(x, y, z);
}

double dotProd(const DoubleVec3& vec1, const DoubleVec3& vec2) {
	double x = vec1.getX() * vec2.getX();
	double y = vec1.getY() * vec2.getY();
	double z = vec1.getZ() * vec2.getZ();
	return x + y + z;
}

double length(const DoubleVec3& vec) { return sqrt(dotProd(vec, vec)); }
