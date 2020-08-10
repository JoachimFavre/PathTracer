#include "DoubleMatrix33.h"

// Constructors
DoubleMatrix33::DoubleMatrix33(double val /*= 0*/)
	: column0(val), column1(val), column2(val) {}
DoubleMatrix33::DoubleMatrix33(const DoubleVec3D& column0, const DoubleVec3D& column1, const DoubleVec3D& column2)
	: column0(column0), column1(column1), column2(column2) {}
DoubleMatrix33::DoubleMatrix33(const DoubleMatrix33& matrix)
	: column0(matrix.column0), column1(matrix.column1), column2(matrix.column2) {}


// Getters
DoubleVec3D DoubleMatrix33::getColumn0() const { return column0; }
DoubleVec3D DoubleMatrix33::getColumn1() const { return column1; }
DoubleVec3D DoubleMatrix33::getColumn2() const { return column2; }

DoubleVec3D DoubleMatrix33::getRow0T() const {
	return DoubleVec3D(column0.getX(), column1.getX(), column2.getX()); 
}

DoubleVec3D DoubleMatrix33::getRow1T() const {
	return DoubleVec3D(column0.getY(), column1.getY(), column2.getY());
}

DoubleVec3D DoubleMatrix33::getRow2T() const {
	return DoubleVec3D(column0.getZ(), column1.getZ(), column2.getZ());
}


// Getters
void DoubleMatrix33::setColumn0(const DoubleVec3D& column0) { this->column0 = column0; }
void DoubleMatrix33::setColumn1(const DoubleVec3D& column1) { this->column1 = column1; }
void DoubleMatrix33::setColumn2(const DoubleVec3D& column2) { this->column2 = column2; }


// Operators
void DoubleMatrix33::operator+=(const DoubleMatrix33& matrix) {
	column0 += matrix.column0;
	column1 += matrix.column1;
	column2 += matrix.column2;
}

void DoubleMatrix33::operator-=(const DoubleMatrix33& matrix) {
	operator+=(-matrix);
}

void DoubleMatrix33::operator*=(const DoubleMatrix33& matrix) {
	DoubleMatrix33 thisCopy = *this;

	column0 = thisCopy*matrix.getColumn0();
	column1 = thisCopy*matrix.getColumn1();
	column2 = thisCopy*matrix.getColumn2();
}

void DoubleMatrix33::operator*=(double val) {
	column0 *= val;
	column1 *= val;
	column2 *= val;
}


// "Extern" operators
DoubleMatrix33 operator+(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2) {
	DoubleMatrix33 result = matrix1;
	result += matrix2;
	return result;
}

DoubleMatrix33 operator-(const DoubleMatrix33& matrix) {
	DoubleMatrix33 copy = matrix;
	copy *= -1;
	return copy;
}

DoubleMatrix33 operator-(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2) {
	DoubleMatrix33 result = matrix1;
	result -= matrix2;
	return result;
}

DoubleMatrix33 operator*(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2) {
	DoubleMatrix33 result = matrix1;
	result *= matrix2;
	return result;
}

DoubleVec3D operator*(const DoubleMatrix33& matrix, const DoubleVec3D& vec) {
	return DoubleVec3D(dotProd(matrix.getRow0T(), vec),
		               dotProd(matrix.getRow1T(), vec),
		               dotProd(matrix.getRow2T(), vec));
}


// Rotation matrices
DoubleMatrix33 getRotationMatrixX(double roll) {
	DoubleVec3D column0(1, 0, 0);
	DoubleVec3D column1(0, cos(roll), sin(roll));
	DoubleVec3D column2(0, -sin(roll), cos(roll));

	return DoubleMatrix33(column0, column1, column2);
}

DoubleMatrix33 getRotationMatrixY(double pitch) {
	DoubleVec3D column0(cos(pitch), 0, -sin(pitch));
	DoubleVec3D column1(0, 1, 0);
	DoubleVec3D column2(sin(pitch), 0, cos(pitch));

	return DoubleMatrix33(column0, column1, column2);
}

DoubleMatrix33 getRotationMatrixZ(double yaw) {
	DoubleVec3D column0(cos(yaw), sin(yaw), 0);
	DoubleVec3D column1(-sin(yaw), cos(yaw), 0);
	DoubleVec3D column2(0, 0, 1);

	return DoubleMatrix33(column0, column1, column2);
}

DoubleMatrix33 getRotationMatrixXYZ(double roll, double pitch, double yaw) {
	return getRotationMatrixZ(yaw)*getRotationMatrixY(pitch)*getRotationMatrixX(roll);
}

DoubleMatrix33 getRotationMatrixXYZ(const DoubleVec3D& angles) {
	return getRotationMatrixXYZ(angles.getX(), angles.getY(), angles.getZ());
}
