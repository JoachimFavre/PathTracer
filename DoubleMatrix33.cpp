#include "DoubleMatrix33.h"

// Constructors
DoubleMatrix33::DoubleMatrix33()
	: column0(), column1(), column2() {}
DoubleMatrix33::DoubleMatrix33(const DoubleVec3D& column0, const DoubleVec3D& column1, const DoubleVec3D& column2)
	: column0(column0), column1(column1), column2(column2) {}
DoubleMatrix33::DoubleMatrix33(const DoubleMatrix33& matrix)
	: column0(matrix.column0), column1(matrix.column1), column2(matrix.column2) {}

// Setters
DoubleVec3D DoubleMatrix33::getColumn0() { return column0; }
DoubleVec3D DoubleMatrix33::getColumn1() { return column1; }
DoubleVec3D DoubleMatrix33::getColumn2() { return column2; }

// Getters
void DoubleMatrix33::setColumn0(const DoubleVec3D& column0) { this->column0 = column0; }
void DoubleMatrix33::setColumn1(const DoubleVec3D& column1) { this->column1 = column1; }
void DoubleMatrix33::setColumn2(const DoubleVec3D& column2) { this->column2 = column2; }
