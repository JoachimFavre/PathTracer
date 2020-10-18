#ifndef DEF_DOUBLEMATRIX33
#define DEF_DOUBLEMATRIX33

#include "DoubleVec3D.h"

//! A three-dimensional square matrix using doubles.
class DoubleMatrix33 {
private:
	DoubleVec3D column0;
	DoubleVec3D column1;
	DoubleVec3D column2;

public:
	//! Default constructor. Gives all points the same value.
	/*!
		\param val The value of all the points.
		\sa DoubleMatrix33(const DoubleVec3D& column0, const DoubleVec3D& column1, const DoubleVec3D& column2)
	*/
	DoubleMatrix33(double val=0);

	//! Main constructor.
	/*!
		\param column0 The value of the first column.
		\param column1 The value of the second column.
		\param column2 The value of the third column.
		\sa DoubleMatrix33(double val)
	*/
	DoubleMatrix33(const DoubleVec3D& column0, const DoubleVec3D& column1, const DoubleVec3D& column2);

	//! Copy constructor.
	/*!
		\param vec The matrix that will be copied.
	*/
	DoubleMatrix33(const DoubleMatrix33& matrix);



	//! Getter for the first column.
	/*!
		\return The first column of this matrix.
		\sa setColumn0(), getColumn1(), getColumn2()
	*/
	DoubleVec3D getColumn0() const;

	//! Getter for the second column.
	/*!
		\return The second column of this matrix.
		\sa setColumn1(), getColumn0(), getColumn2()
	*/
	DoubleVec3D getColumn1() const;

	//! Getter for the third column.
	/*!
		\return The third column of this matrix.
		\sa setColumn2(), getColumn0(), getColumn1()
	*/
	DoubleVec3D getColumn2() const;

	//! Getter for the first row (transposed).
	/*!
		\return The first row transposed.
		\sa getRow1T(), getRow2T()
	*/
	DoubleVec3D getRow0T() const;

	//! Getter for the second row (transposed).
	/*!
		\return The second row transposed.
		\sa getRow0T(), getRow2T()
	*/
	DoubleVec3D getRow1T() const;

	//! Getter for the third row (transposed).
	/*!
		\return The third row transposed.
		\sa getRow0T(), getRow1T()
	*/
	DoubleVec3D getRow2T() const;

	// ##################################### SETTERS #####################################

	//! Setter for the first column
	/*!
		\param column0 The first column.
		\sa getColumn0(), setColumn1(), setColumn2()
	*/
	void setColumn0(const DoubleVec3D& column0);

	//! Setter for the second column
	/*!
		\param column1 The second column.
		\sa getColumn1(), setColumn0(), setColumn2()
	*/
	void setColumn1(const DoubleVec3D& column1);

	//! Setter for the third column
	/*!
		\param column2 The third column.
		\sa getColumn2(), setColumn0(), setColumn1()
	*/
	void setColumn2(const DoubleVec3D& column2);



	//! Sum operator.
	/*!
		\param matrix The second matrix that will be used for the sum.
		\sa operator+()
	*/
	void operator+=(const DoubleMatrix33& matrix);

	//! Difference operator.
	/*!
		Uses the sum and unary minus operators.
		\param matrix The second matrix that will be used for the difference.
		\sa operator+=(), operator-()
	*/
	void operator-=(const DoubleMatrix33& matrix);

	//! Multiplication by a matrix operator.
	/*!
		\param matrix The second matrix that will be used for the multiplication.
	*/
	void operator*=(const DoubleMatrix33& matrix);

	//! Multiplication by a scalar operator.
	/*!
		\param val The scalar that will be used for the multiplication.
		\sa operator*(), operator*()
	*/
	void operator*=(double val);
};



//! Sum operator.
/*!
	Uses the operator+=() method.
	\param matrix1 The first matrix for the sum.
	\param matrix2 The second matrix for the sum.
	\return The sum of the two matrices.
	\sa operator+=()
*/
DoubleMatrix33 operator+(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2);

//! Unary minus operator.
/*!
	Uses the operator*=() method.
	\param matrix The matrix that will be inversed.
	\return The inverse of matrix.
	\sa operator*=(), operator-=()
*/
DoubleMatrix33 operator-(const DoubleMatrix33& matrix);

//! Difference operator
/*!
	Uses the operator-=() method.
	\param matrix1 The first matrix for the difference.
	\param matrix2 The second matrix for the difference.
	\return The difference between matrix1 and matrix2.
	\sa operator-=()
*/
DoubleMatrix33 operator-(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2);

//! Matrix product operator
/*!
	Uses the operator*=() method.
	\param matrix1 The first matrix for the product.
	\param matrix2 The second matrix for the product.
	\return The product between matrix1 and matrix2.
	\sa operator*=()
*/
DoubleMatrix33 operator*(const DoubleMatrix33& matrix1, const DoubleMatrix33& matrix2);

//! Matrix-vector product operator
/*!
	\param matrix The matrix for the product.
	\param vec The vector for the product.
	\return The product between matrix and vec.
*/
DoubleVec3D operator*(const DoubleMatrix33& matrix, const DoubleVec3D& vec);



//! Rotation matrix around the x axis.
/*!
	\param roll The angle of the rotation.
	\return The rotation matrix.
*/
DoubleMatrix33 getRotationMatrixX(double roll);

//! Rotation matrix around the y axis.
/*!
	\param pitch The angle of the rotation.
	\return The rotation matrix.
*/
DoubleMatrix33 getRotationMatrixY(double pitch);

//! Rotation matrix around the z axis.
/*!
	\param yaw The angle of the rotation.
	\return The rotation matrix.
*/
DoubleMatrix33 getRotationMatrixZ(double yaw);

//! Rotation matrix around the z, y and then x axis.
/*!
	\param roll Angle of the rotation around the x axis.
	\param pitch Angle of the rotation around the y axis.
	\param yaw Angle of the rotation around the z axis.
	\return The product of the rotation matrices (z, y and then x).
*/
DoubleMatrix33 getRotationMatrixXYZ(double roll, double pitch, double yaw);

//! Rotation matrix around the z, y and then x axis.
/*!
	\param angles The first coordinate of this vector is the rotation around the x axis, the second one is the rotation around the y axis and the last one is the rotation around the z axis.
	\return The product of the rotation matrices (z, y and then x).
*/
DoubleMatrix33 getRotationMatrixXYZ(const DoubleVec3D& angles);



//! Scaling matrix on the x axis.
/*!
	\param x The factor of the scaling.
	\return The scaling matrix.
*/
DoubleMatrix33 getScalingMatrixX(double x);

//! Scaling matrix on the y axis.
/*!
	\param y The factor of the scaling.
	\return The scaling matrix.
*/
DoubleMatrix33 getScalingMatrixY(double y);

//! Scaling matrix on the z axis.
/*!
	\param z The factor of the scaling.
	\return The scaling matrix.
*/
DoubleMatrix33 getScalingMatrixZ(double z);

//! Scaling matrix on the x, y and z axis.
/*!
	\param x The factor of the scaling on the x axis.
	\param y The factor of the scaling on the y axis.
	\param z The factor of the scaling on the z axis.
	\return The scaling matrix.
*/
DoubleMatrix33 getScalingMatrixXYZ(double x, double y, double z);

//! Scaling matrix on the x, y and z axis.
/*!
	\param values The first coordinate of this vector is the scaling on the x axis, the second one is the scaling on the y axis and the last one is the scaling on the z axis.
	\return The scaling matrix.
*/
DoubleMatrix33 getScalingMatrixXYZ(const DoubleVec3D& values);

#endif