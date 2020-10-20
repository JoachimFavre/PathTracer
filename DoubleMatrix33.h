#ifndef DEF_DOUBLEMATRIX33
#define DEF_DOUBLEMATRIX33

#include "DoubleVec3D.h"


/*!
	\file DoubleMatrix33.h
	\brief Defines the DoubleMatrix33 class and the functions around it.

	\class DoubleMatrix33
	\brief A three-dimensional square matrix using doubles.

	\fn DoubleMatrix33::DoubleMatrix33(double val=0)
	\brief Default constructor. Gives all points the same value.
	\param val The value of all the points.
	\sa DoubleMatrix33(const DoubleVec3D& column0, const DoubleVec3D& column1, const DoubleVec3D& column2)

	\fn DoubleMatrix33::DoubleMatrix33(const DoubleVec3D& column0, const DoubleVec3D& column1, const DoubleVec3D& column2)
	\brief Main constructor.
	\param column0 The value of the first column.
	\param column1 The value of the second column.
	\param column2 The value of the third column.
	\sa DoubleMatrix33(double val)

	\fn DoubleMatrix33::DoubleMatrix33(const DoubleMatrix33& matrix)
	\brief Copy constructor.
	\param matrix The matrix that will be copied.

	\fn DoubleMatrix33::getColumn0()
	\brief Getter for the first column.
	\return The first column of this matrix.
	\sa setColumn0(), getColumn1(), getColumn2()

	\fn DoubleMatrix33::getColumn1()
	\brief Getter for the second column.
	\return The second column of this matrix.
	\sa setColumn1(), getColumn0(), getColumn2()

	\fn DoubleMatrix33::getColumn2()
	\brief Getter for the third column.
	\return The third column of this matrix.
	\sa setColumn2(), getColumn0(), getColumn1()

	\fn DoubleMatrix33::getRow0T()
	\brief Getter for the first row (transposed).
	\return The first row transposed.
	\sa getRow1T(), getRow2T()

	\fn DoubleMatrix33::getRow1T()
	\brief Getter for the second row (transposed).
	\return The second row transposed.
	\sa getRow0T(), getRow2T()

	\fn DoubleMatrix33::getRow2T()
	\brief Getter for the third row (transposed).
	\return The third row transposed.
	\sa getRow0T(), getRow1T()

	\fn DoubleMatrix33::setColumn0(const DoubleVec3D& column0)
	\brief Setter for the first column
	\param column0 The first column.
	\sa getColumn0(), setColumn1(), setColumn2()

	\fn DoubleMatrix33::setColumn1(const DoubleVec3D& column1)
	\brief Setter for the second column
	\param column1 The second column.
	\sa getColumn1(), setColumn0(), setColumn2()

	\fn DoubleMatrix33::setColumn2(const DoubleVec3D& column2)
	\brief Setter for the third column
	\param column2 The third column.
	\sa getColumn2(), setColumn0(), setColumn1()

	\fn DoubleMatrix33::operator+=(const DoubleMatrix33& matrix)
	\brief Sum operator.
	\param matrix The second matrix that will be used for the sum.
	\sa operator+()

	\fn DoubleMatrix33::operator-=(const DoubleMatrix33& matrix)
	\brief Difference operator.
	\details Uses the sum and unary minus operators.
	\param matrix The second matrix that will be used for the difference.
	\sa operator+=(), operator-()

	\fn DoubleMatrix33::operator*=(const DoubleMatrix33& matrix)
	\brief Multiplication by a matrix operator.
	\param matrix The second matrix that will be used for the multiplication.

	\fn DoubleMatrix33::operator*=(double val)
	\brief Multiplication by a scalar operator.
	\param val The scalar that will be used for the multiplication.
	\sa operator*(), operator*()

	\fn operator+(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2)
	\brief Sum operator.
	\details Uses the operator+=() method.
	\param matrix1 The first matrix for the sum.
	\param matrix2 The second matrix for the sum.
	\return The sum of the two matrices.
	\sa operator+=()

	\fn operator-(const DoubleMatrix33& matrix)
	\brief Unary minus operator.
	\details Uses the operator*=() method.
	\param matrix The matrix that will be inversed.
	\return The inverse of matrix.
	\sa operator*=(), operator-=()

	\fn operator-(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2)
	\brief Difference operator
	\details Uses the operator-=() method.
	\param matrix1 The first matrix for the difference.
	\param matrix2 The second matrix for the difference.
	\return The difference between matrix1 and matrix2.
	\sa operator-=()

	\fn operator*(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2)
	\brief Matrix product operator
	\details Uses the operator*=() method.
	\param matrix1 The first matrix for the product.
	\param matrix2 The second matrix for the product.
	\return The product between matrix1 and matrix2.
	\sa operator*=()

	\fn operator*(const DoubleMatrix33& matrix, const DoubleVec3D& vec)
	\brief Matrix-vector product operator
	\param matrix The matrix for the product.
	\param vec The vector for the product.
	\return The product between matrix and vec.

	\fn getRotationMatrixX(double roll)
	\brief Rotation matrix around the x axis.
	\param roll The angle of the rotation.
	\return The rotation matrix.

	\fn getRotationMatrixY(double pitch)
	\brief Rotation matrix around the y axis.
	\param pitch The angle of the rotation.
	\return The rotation matrix.

	\fn getRotationMatrixZ(double yaw)
	\brief Rotation matrix around the z axis.
	\param yaw The angle of the rotation.
	\return The rotation matrix.

	\fn getRotationMatrixXYZ(double roll, double pitch, double yaw)
	\brief Rotation matrix around the z, y and then x axis.
	\param roll Angle of the rotation around the x axis.
	\param pitch Angle of the rotation around the y axis.
	\param yaw Angle of the rotation around the z axis.
	\return The product of the rotation matrices (z, y and then x).

	\fn getRotationMatrixXYZ(const DoubleVec3D& angles)
	\brief Rotation matrix around the z, y and then x axis.
	\param angles The first coordinate of this vector is the rotation around the x axis, the second one is the rotation around the y axis and the last one is the rotation around the z axis.
	\return The product of the rotation matrices (z, y and then x).

	\fn getScalingMatrixX(double x)
	\brief Scaling matrix on the x axis.
	\param x The factor of the scaling.
	\return The scaling matrix.

	\fn getScalingMatrixY(double y)
	\brief Scaling matrix on the y axis.
	\param y The factor of the scaling.
	\return The scaling matrix.

	\fn getScalingMatrixZ(double z)
	\brief Scaling matrix on the z axis.
	\param z The factor of the scaling.
	\return The scaling matrix.

	\fn getScalingMatrixXYZ(double x, double y, double z)
	\brief Scaling matrix on the x, y and z axis.
	\param x The factor of the scaling on the x axis.
	\param y The factor of the scaling on the y axis.
	\param z The factor of the scaling on the z axis.
	\return The scaling matrix.

	\fn getScalingMatrixXYZ(const DoubleVec3D& values)
	\brief Scaling matrix on the x, y and z axis.
	\param values The first coordinate of this vector is the scaling on the x axis, the second one is the scaling on the y axis and the last one is the scaling on the z axis.
	\return The scaling matrix.
*/


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
DoubleMatrix33 operator-(const DoubleMatrix33& matrix);
DoubleMatrix33 operator-(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2);
DoubleMatrix33 operator*(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2);
DoubleVec3D operator*(const DoubleMatrix33& matrix, const DoubleVec3D& vec);

DoubleMatrix33 getRotationMatrixX(double roll);
DoubleMatrix33 getRotationMatrixY(double pitch);
DoubleMatrix33 getRotationMatrixZ(double yaw);
DoubleMatrix33 getRotationMatrixXYZ(double roll, double pitch, double yaw);
DoubleMatrix33 getRotationMatrixXYZ(const DoubleVec3D& angles);

DoubleMatrix33 getScalingMatrixX(double x);
DoubleMatrix33 getScalingMatrixY(double y);
DoubleMatrix33 getScalingMatrixZ(double z);
DoubleMatrix33 getScalingMatrixXYZ(double x, double y, double z);
DoubleMatrix33 getScalingMatrixXYZ(const DoubleVec3D& values);

#endif