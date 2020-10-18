#ifndef DEF_DOUBLEVEC3D
#define DEF_DOUBLEVEC3D

#include <iostream>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

// Needs to be included before fbxsdk, else creates conflict.
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include <fbxsdk.h>


//! A three-dimensional vector using double values.
class DoubleVec3D {
private:
	double x;
	double y;
	double z;

protected:
	//! Stores whether the vector was normalised.
	/*!
		This value is set to false when we change any value of the vector (even if it gives it a magnitude of 1), and is set to true when the normalise() method is called.
	*/
	bool normalised; 

public:
	//! Default constructor. Gives all coordinates the same value.
	/*!
		\param val The value of all the coordinates.
		\sa DoubleVec3D(double x, double y, double z)
	*/
	DoubleVec3D(double val = 0);

	//! Main constructor.
	/*!
		\param x The value of the first coordinate.
		\param y The value of the second coordinate.
		\param z The value of the third coordinate.
		\sa DoubleVec3D(double val)
	*/
	DoubleVec3D(double x, double y, double z);
	
	//! Copy constructor.
	/*!
		\param vec The vector that will be copied.
	*/
	DoubleVec3D(const DoubleVec3D& vec);

	//! Converting constructor for FbxDouble3.
	/*!
		\param vec The FbxDouble3 vector (from FBX SDK library) that will be converted.
		\sa DoubleVec3D(const FbxDouble4& vec)
	*/
	DoubleVec3D(const FbxDouble3& vec);

	//! Converting constructor for FbxDouble4.
	/*!
		\param vec The FbxDouble4 vector (from FBX SDK library) that will be converted.
		\sa DoubleVec3D(const FbxDouble3& vec)
	*/
	DoubleVec3D(const FbxDouble4& vec);

	//! Getter for the first coordinate.
	/*!
		\return The first coordinate of this vector.
		\sa getY(), getZ(), setVals()
	*/
	double getX() const;

	//! Getter for the second coordinate.
	/*!
		\return The second coordinate of this vector.
		\sa getX(), getZ(), setVals()
	*/
	double getY() const;

	//! Getter for the third coordinate.
	/*!
		\return The third coordinate of this vector.
		\sa getX(), getY(), setVals()
	*/
	double getZ() const;

	//! Setter for all coordinates.
	/*!
		There is not one setter by coordinate, because of the way the DoubleUnitVect3D class is defined.
		\param x The first coordinate.
		\param y The second coordinate.
		\param z The third coordinate.
		\sa getX(), getY(), getZ()
	*/
	virtual void setVals(double x, double y, double z);
	

	//! Sum operator.
	/*!
		\param vec The second vector that will be used for the sum.
		\sa operator+()
	*/
	void operator+=(const DoubleVec3D& vec);

	//! Difference operator.
	/*!
		Uses the sum and unary minus operators.
		\param vec The second vector that will be used for the difference.
		\sa operator+=(), operator-()
	*/
	void operator-=(const DoubleVec3D& vec);

	//! Multiplication by a scalar operator.
	/*!
		\param val The scalar that will be used for the multiplication.
		\sa operator*(), operator*()
	*/
	void operator*=(const double& val);

	//! Division by a scalar operator.
	/*!
		Uses the multiplication by a scalar operator.
		\param val The scalar that will be used for the division.
		\sa operator*=(), operator/()
	*/
	void operator/=(const double& val);

	//! Normalises the vector
	/*!
		Automatically verifies if normalised attribute is true or not. If the vector length is zero, sets it to (1, 0, 0).
	*/
	void normalise();

	//! Returns whether the vector is normalised.
	/*!
		\return The attribute normalised.
	*/
	bool isNormalised() const;

	//! Returns whether the vector has a length of zero
	/*!
		\return False if the three coordinates are 0, true else.
	*/
	bool isZero() const;
};

//! Sum operator.
/*!
	Uses the operator+=() method.
	\param vec1 The first vector for the sum.
	\param vec2 The second vector for the sum.
	\return The sum of the two vectors.
	\sa operator+=()
*/
DoubleVec3D operator+(const DoubleVec3D& vec1, const DoubleVec3D& vec2);

//! Unary minus operator.
/*!
	Uses the operator*=() method.
	\param vec The vector that will be inversed.
	\return The inverse of vec.
	\sa operator*=(), operator-=()
*/
DoubleVec3D operator-(const DoubleVec3D& vec);

//! Difference operator
/*!
	Uses the operator-=() method.
	\param vec1 The first vector for the difference.
	\param vec2 The second vector for the difference.
	\return The difference between vec1 and vec2.
	\sa operator-=()
*/
DoubleVec3D operator-(const DoubleVec3D& vec1, const DoubleVec3D& vec2);


//! Multiplication by a scalar operator (commutative).
/*!
	Uses the operator*=() method.
	\param vec The vector that will get multiplied.
	\param val The scalar that will multiply the vector.
	\return The vector multiplied by the scalar.
	\sa operator*=()
*/
DoubleVec3D operator*(const DoubleVec3D& vec, const double& val);

//! Multiplication by a scalar operator (commutative).
/*!
	Uses the operator*=() method.
	\param vec The vector that will get multiplied.
	\param val The scalar that will multiply the vector.
	\return The vector multiplied by the scalar.
	\sa operator*=()
*/
DoubleVec3D operator*(const double& val, const DoubleVec3D& vec);

//! Division by a scalar operator.
/*!
	Uses the operator/=() method.
	\param vec The vector that will get divided.
	\param val The scalar that will divide the vector.
	\return The vector divided by the scalar.
	\sa operator/=()
*/
DoubleVec3D operator/(const DoubleVec3D& vec, const double& val);

//! Ostream operator.
/*!
	Displays vectors under the form "(x, y, z)"
	\param stream The ostream before.
	\param vec The vector that will be added to the stream.
	\return The stream with the vector added.
*/
std::ostream& operator<<(std::ostream& stream, const DoubleVec3D& vec);


//! Cross product.
/*!
	A cross prodct gives a third vector, orthogonal to the two previous.
	\param vec1 The fisrt vector for the product.
	\param vec2 The second vector for the product.
	\return The cross product between vec1 and vec2.
*/
DoubleVec3D crossProd(const DoubleVec3D& vec1, const DoubleVec3D& vec2);

//! Dot product.
/*!
	A dot product gives the product of the norm of each vector, multiplied by the cosine of the angle between the two vectors.
	\param vec1 The first vector for the product.
	\param vec2 The second vector for the product.
	\return The dot product between vec1 and vec2.
*/
double dotProd(const DoubleVec3D& vec1, const DoubleVec3D& vec2);

//! Norm of the vector.
/*!
	Uses the dotProd() method.
	\param vec The vector from which the norm will be computed.
	\return The norm of this vector.
*/
double length(const DoubleVec3D& vec);

//! Conversion to json.
/*!
	\param j Json output.
	\param vec The vector that will be converted.
*/
void to_json(json& j, const DoubleVec3D& vec);

//! Conversion from json
/*!
	Used for the .get<DoubleVec3D>() function.
	\param j Json input.
	\param vec The output vector.
*/
void from_json(const json& j, DoubleVec3D& vec);

#endif