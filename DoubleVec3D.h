#ifndef DEF_DOUBLEVEC3D
#define DEF_DOUBLEVEC3D

#include "InterfaceGestion.h"

/*! 
    \file DoubleVec3D.h
    \brief Defines the DoubleVec3D class and some functions around it.
    
    \class DoubleVec3D
    \brief A three-dimensional vector using double values.

    \var DoubleVec3D::normalised
    \brief Stores whether the vector was normalised.
    \details This value is set to false when we change any value of the vector (even if it gives it a magnitude of 1), and is set to true when the DoubleVec3D::normalise() method is called.
    \sa DoubleVec3D::normalise(), DoubleVec3D::isNormalised()    

    \fn DoubleVec3D::DoubleVec3D(double val = 0)
    \brief Default constructor. Gives all coordinates the same value.
    \param val The value of all the coordinates.
    \sa DoubleVec3D::DoubleVec3D(double x, double y, double z)

    \fn DoubleVec3D::DoubleVec3D(double x, double y, double z)
    \brief Main constructor.
    \param x The value of the first coordinate.
    \param y The value of the second coordinate.
    \param z The value of the third coordinate.
    \sa DoubleVec3D::DoubleVec3D(double val)

    \fn DoubleVec3D::DoubleVec3D(const DoubleVec3D& vec)
    \brief Copy constructor.
    \param vec The vector that will be copied.

    \fn DoubleVec3D::DoubleVec3D(const FbxDouble3& vec)
    \brief Converting constructor for FbxDouble3.
    \param vec The FbxDouble3 vector (from the FBX SDK library) that will be converted.
    \sa DoubleVec3D::DoubleVec3D(const FbxDouble4& vec)

    \fn DoubleVec3D::DoubleVec3D(const FbxDouble4& vec)
    \brief Converting constructor for FbxDouble4.
    \param vec The FbxDouble4 vector (from the FBX SDK library) that will be converted.
    \sa DoubleVec3D::DoubleVec3D(const FbxDouble3& vec)

    \fn double DoubleVec3D::getX()
    \brief Getter for the first coordinate.
    \return The first coordinate of this vector.
    \sa DoubleVec3D::getY(), DoubleVec3D::getZ(), DoubleVec3D::setVals()

    \fn double DoubleVec3D::getY()
    \brief Getter for the second coordinate.
    \return The second coordinate of this vector.
    \sa DoubleVec3D::getX(), DoubleVec3D::getZ(), DoubleVec3D::setVals()

    \fn double DoubleVec3D::getZ()
    \brief Getter for the third coordinate.
    \return The third coordinate of this vector.
    \sa DoubleVec3D::getX(), DoubleVec3D::getY(), DoubleVec3D::setVals()

    \fn virtual void DoubleVec3D::setVals()
    \brief Setter for all coordinates.
    \details There is not one setter by coordinate, because of the way the DoubleUnitVect3D class is defined.
    \param x The first coordinate.
    \param y The second coordinate.
    \param z The third coordinate.
    \sa DoubleVec3D::getX(), DoubleVec3D::getY(), DoubleVec3D::getZ()

    \fn void DoubleVec3D::operator+=(const DoubleVec3D& vec)
    \brief Sum operator.
    \param vec The second vector that will be used for the sum.
    \sa operator+(const DoubleVec3D& vec1, const DoubleVec3D& vec2)

    \fn void DoubleVec3D::operator-=(const DoubleVec3D& vec)
    \brief Difference operator.
    \details Uses the sum and unary minus operators.
    \param vec The second vector that will be used for the difference.
    \sa DoubleVec3D::operator+=(), operator-(const DoubleVec3D& vec)

    \fn void DoubleVec3D::operator*=(const double& val)
    \brief Multiplication by a scalar operator.
    \param val The scalar that will be used for the multiplication.
    \sa operator*(const DoubleVec3D& vec, const double& val), operator*(const double& val, const DoubleVec3D& vec)

    \fn void DoubleVec3D::operator/=(const double& val);
    \brief Division by a scalar operator.
    \details Uses the multiplication by a scalar operator.
    \param val The scalar that will be used for the division.
    \sa DoubleVec3D::operator*=(), operator/(const DoubleVec3D& vec, const double& val)

    \fn void DoubleVec3D::normalise()
    \brief Normalises the vector.
    \details Automatically verifies if normalised attribute is true or not. If the vector length is zero, sets it to (1, 0, 0).

    \fn bool DoubleVec3D::isNormalised()
    \brief Returns whether the vector is normalised.
    \return DoubleVec3D::normalised.
    \sa DoubleVec3D::normalised

    \fn bool DoubleVec3D::isZero()
    \brief Returns whether the vector has a length of zero.
    \return False if the three coordinates are 0, true else.

    \fn DoubleVec3D operator+(const DoubleVec3D& vec1, const DoubleVec3D& vec2)
    \brief Sum operator.
    \details Uses the DoubleVec3D::operator+=() method.
    \param vec1 The first vector for the sum.
    \param vec2 The second vector for the sum.
    \return The sum of the two vectors.
    \sa DoubleVec3D::operator+=()

    \fn DoubleVec3D operator-(const DoubleVec3D& vec)
    \brief Unary minus operator.
    \details Uses the DoubleVec3D::operator*=() method.
    \param vec The vector that will be inversed.
    \return The inverse of vec.
    \sa DoubleVec3D::operator*=(), DoubleVec3D::operator-=(), operator-(const DoubleVec3D& vec1, const DoubleVec3D& vec2)

    \fn DoubleVec3D operator-(const DoubleVec3D& vec1, const DoubleVec3D& vec2)
    \brief Difference operator.
    \details Uses the DoubleVec3D::operator-=() method.
    \param vec1 The first vector for the difference.
    \param vec2 The second vector for the difference.
    \return The difference between vec1 and vec2.
    \sa DoubleVec3D::operator-=(), operator-(const DoubleVec3D& vec)

    \fn DoubleVec3D operator*(const DoubleVec3D& vec, const double& val)
    \brief Multiplication by a scalar operator (commutative).
    \details Uses the DoubleVec3D::operator*=() method.
    \param vec The vector that will get multiplied.
    \param val The scalar that will multiply the vector.
    \return The vector multiplied by the scalar.
    \sa DoubleVec3D::operator*=(), operator*(const double& val, const DoubleVec3D& vec)

    \fn DoubleVec3D operator*(const double& val, const DoubleVec3D& vec)
    \brief Multiplication by a scalar operator (commutative).
    \details Uses the DoubleVec3D::operator*=() method.
    \param vec The vector that will get multiplied.
    \param val The scalar that will multiply the vector.
    \return The vector multiplied by the scalar.
    \sa DoubleVec3D::operator*=(), operator*(const DoubleVec3D& vec, const double& val)

    \fn DoubleVec3D operator/(const DoubleVec3D& vec, const double& val)
    \brief Division by a scalar operator.
    \details Uses the DoubleVec3D::operator/=() method.
    \param vec The vector that will get divided.
    \param val The scalar that will divide the vector.
    \return The vector divided by the scalar.
    \sa DoubleVec3D::operator/=()

    \fn std::ostream& operator<<(std::ostream& stream, const DoubleVec3D& vec)
    \brief Ostream operator.
    \details Displays vectors under the form "(x, y, z)"
    \param stream The ostream before.
    \param vec The vector that will be added to the stream.
    \return The stream with the vector added.

    \fn DoubleVec3D crossProd(const DoubleVec3D& vec1, const DoubleVec3D& vec2)
    \brief Cross product.
    \details A cross prodct gives a third vector, orthogonal to the two previous. Its length is given by the area of the parallelogram drawn by vec1 and vec2.
    \param vec1 The first vector for the product.
    \param vec2 The second vector for the product.
    \return The cross product between vec1 and vec2.

    \fn double dotProd(const DoubleVec3D& vec1, const DoubleVec3D& vec2)
    \brief Dot product.
    \details A dot product gives the product of the norm of each vector, multiplied by the cosine of the angle between the two vectors.
    \param vec1 The first vector for the product.
    \param vec2 The second vector for the product.
    \return The dot product between vec1 and vec2.
    \sa length()

    \fn double length(const DoubleVec3D& vec)
    \brief Gives the norm of the vector.
    \details Uses the dotProd() method.
    \param vec The vector from which the norm will be computed.
    \return The norm of this vector.
    \sa dotProd()

    \fn void to_json(json& j, const DoubleVec3D& vec)
    \brief Conversion to json.
    \param j Json output.
    \param vec The vector that will be converted.

    \fn void from_json(const json& j, DoubleVec3D& vec)
    \brief Conversion from json.
    \details Used for the .get<DoubleVec3D>() function.
    \param j Json input.
    \param vec The output vector.
*/

class DoubleVec3D {
private:
    double x;
    double y;
    double z;

protected:
    bool normalised; 

public:
    DoubleVec3D(double val = 0);
    DoubleVec3D(double x, double y, double z);
    DoubleVec3D(const DoubleVec3D& vec);
    DoubleVec3D(const FbxDouble3& vec);
    DoubleVec3D(const FbxDouble4& vec);

    double getX() const;
    double getY() const;
    double getZ() const;

    virtual void setVals(double x, double y, double z);
    
    void operator+=(const DoubleVec3D& vec);
    void operator-=(const DoubleVec3D& vec);
    void operator*=(const double& val);
    void operator/=(const double& val);

    void normalise();
    bool isNormalised() const;
    bool isZero() const;
};

DoubleVec3D operator+(const DoubleVec3D& vec1, const DoubleVec3D& vec2);
DoubleVec3D operator-(const DoubleVec3D& vec);
DoubleVec3D operator-(const DoubleVec3D& vec1, const DoubleVec3D& vec2);
DoubleVec3D operator*(const DoubleVec3D& vec, const double& val);
DoubleVec3D operator*(const double& val, const DoubleVec3D& vec);
DoubleVec3D operator/(const DoubleVec3D& vec, const double& val);

std::ostream& operator<<(std::ostream& stream, const DoubleVec3D& vec);

DoubleVec3D crossProd(const DoubleVec3D& vec1, const DoubleVec3D& vec2);
double dotProd(const DoubleVec3D& vec1, const DoubleVec3D& vec2);
double length(const DoubleVec3D& vec);

void to_json(json& j, const DoubleVec3D& vec);
void from_json(const json& j, DoubleVec3D& vec);

#endif