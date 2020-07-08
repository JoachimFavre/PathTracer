#include "DoubleVec3D.h"

// Constructors
DoubleVec3D::DoubleVec3D(double val /*= 0*/)
	: x(val), y(val), z(val) {}

DoubleVec3D::DoubleVec3D(double x, double y, double z)
	: x(x), y(y), z(z) {}

DoubleVec3D::DoubleVec3D(const DoubleVec3D& vec)
	: x(vec.x), y(vec.y), z(vec.z) {}


// Getters
double DoubleVec3D::getX() const { return this->x; }
double DoubleVec3D::getY() const { return this->y; }
double DoubleVec3D::getZ() const { return this->z; }


// Setters
void DoubleVec3D::setX(double x) { this->x = x; }
void DoubleVec3D::setY(double y) { this->y = y; }
void DoubleVec3D::setZ(double z) { this->z = z; }

void DoubleVec3D::setVals(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


// Operators
void DoubleVec3D::operator+=(const DoubleVec3D& vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

void DoubleVec3D::operator-=(const DoubleVec3D& vec) { this->operator+=(-vec); }

void DoubleVec3D::operator*=(const double& val) {
	x *= val;
	y *= val;
	z *= val;
}

void DoubleVec3D::operator/=(const double& val) { this->operator*=(1 / val); }


// Other method
void DoubleVec3D::normalise() {
	double lengthSquared = dotProd(*this, *this);
	if (lengthSquared != 1)  // square roots take a lot of time to compute
		this->operator/=(sqrt(lengthSquared));
}


// Functions
// Vector operators
DoubleVec3D operator+(const DoubleVec3D& vec1, const DoubleVec3D& vec2) {
	DoubleVec3D result = vec1;
	result += vec2;
	return result;
}

DoubleVec3D operator-(const DoubleVec3D& vec) {
	DoubleVec3D result = vec;
	result *= -1;
	return result;
}

DoubleVec3D operator-(const DoubleVec3D& vec1, const DoubleVec3D& vec2) {
	DoubleVec3D result = vec1;
	result -= vec2;
	return result;
}

// Scalar operators
DoubleVec3D operator*(const DoubleVec3D& vec, const double& val) {
	DoubleVec3D result = vec;
	result *= val;
	return result;
}

DoubleVec3D operator*(const double& val, const DoubleVec3D& vec) { return operator*(vec, val); }

DoubleVec3D operator/(const DoubleVec3D& vec, const double& val) {
	DoubleVec3D result = vec;
	result /= val;
	return result;
}


// ostream operator
std::ostream& operator<<(std::ostream& stream, const DoubleVec3D& vec) {
	stream << "(" << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ")";
	return stream;
}


// Other functions
DoubleVec3D crossProd(const DoubleVec3D& vec1, const DoubleVec3D& vec2) {
	double x = vec1.getY()*vec2.getZ() - vec1.getZ()*vec2.getY();
	double y = vec1.getZ()*vec2.getX() - vec1.getX()*vec2.getZ();
	double z = vec1.getX()*vec2.getY() - vec1.getY()*vec2.getX();
	return DoubleVec3D(x, y, z);
}

double dotProd(const DoubleVec3D& vec1, const DoubleVec3D& vec2) {
	return vec1.getX()*vec2.getX() + vec1.getY()*vec2.getY() + vec1.getZ()*vec2.getZ();
}

double length(const DoubleVec3D& vec) { return sqrt(dotProd(vec, vec)); }
