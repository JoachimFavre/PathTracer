#ifndef DEF_DOUBLEMATRIX33
#define DEF_DOUBLEMATRIX33

#include "DoubleVec3D.h"

class DoubleMatrix33 {
private:
	DoubleVec3D column0;
	DoubleVec3D column1;
	DoubleVec3D column2;

public:
	DoubleMatrix33(double val=0);
	DoubleMatrix33(const DoubleVec3D& column0, const DoubleVec3D& column1, const DoubleVec3D& column2);
	DoubleMatrix33(const DoubleMatrix33& matrix);

	DoubleVec3D getColumn0() const;
	DoubleVec3D getColumn1() const;
	DoubleVec3D getColumn2() const;

	DoubleVec3D getRow0T() const;
	DoubleVec3D getRow1T() const;
	DoubleVec3D getRow2T() const;

	void setColumn0(const DoubleVec3D& column0);
	void setColumn1(const DoubleVec3D& column1);
	void setColumn2(const DoubleVec3D& column2);

	void operator+=(const DoubleMatrix33& matrix);
	void operator-=(const DoubleMatrix33& matrix);
	void operator*=(const DoubleMatrix33& matrix);
	void operator*=(double val);
};

DoubleMatrix33 operator+(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2);
DoubleMatrix33 operator-(const DoubleMatrix33& matrixs);
DoubleMatrix33 operator-(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2);
DoubleMatrix33 operator*(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2);
DoubleVec3D operator*(const DoubleMatrix33& matrix, const DoubleVec3D& vec);

DoubleMatrix33 getRotationMatrixX(double roll);
DoubleMatrix33 getRotationMatrixY(double pitch);
DoubleMatrix33 getRotationMatrixZ(double yaw);
DoubleMatrix33 getRotationMatrixXYZ(double roll, double pitch, double yaw);
DoubleMatrix33 getRotationMatrixXYZ(const DoubleVec3D& angles);

#endif