#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Material.h"
#include "Object3D.h"


/*!
	\file Triangle.h
	\brief Defines the Triangle class.

	\class Triangle
	\brief A triangle defined by its three vertices.
	\details The order of its vertices is important. See the main constructor for more information.

	\fn Triangle::Triangle()
	\brief Default constructor.
	\details Defines vertex1 = (1, 0, 0), vertex2 = (0, 1, 0) and vertex3 = (0, 0, 1)

	\fn Triangle::Triangle(const DoubleVec3D& vertex1, const DoubleVec3D& vertex2, const DoubleVec3D& vertex3, Material* material)
	\brief Main constructor
	\details The order of the vertices is important, because the normal is only on one side of the triangle (meaning that the triangle can only be seen from one side). Give the vertices counterclockwise from where you want the triangle to be visible.
	\param vertex1 The first vertex of this triangle.
	\param vertex2 The second vertex of this triangle.
	\param vertex3 The third vertex of this triangle.
	\param material A pointer to the material of this triangle.

	\fn Triangle::Triangle(const Triangle& triangle)
	\brief Copy constructor.
	\param triangle The triangle that will be copied.

	\fn Triangle::getVertex1()
	\brief Getter for the first vertex.
	\return This triangle's first vertex.

	\fn Triangle::getVertex2()
	\brief Getter for the second vertex.
	\return This triangle's second vertex.

	\fn Triangle::getVertex3()
	\brief Getter for the third vertex.
	\return This triangle's third vertex.

	\fn Triangle::getCenter()
	\brief Getter for the center.
	\return The average of the three vertices.

	\fn Triangle::setVertex1(const DoubleVec3D& vertex)
	\brief Setter for the first vertex.
	\param vertex The new first vertex of this triangle.

	\fn Triangle::setVertex2(const DoubleVec3D& vertex)
	\brief Setter for the second vertex.
	\param vertex The new second vertex of this triangle.

	\fn Triangle::setVertex3(const DoubleVec3D& vertex)
	\brief Setter for the third vertex.
	\param vertex The new third vertex of this triangle.

	\fn Triangle::computeArea()
	\brief Computes this triangle's area.
	\details Modifies Object3D::area. It uses the formula A = 0.5 * ||edge1 x edge2||.

	\fn Triangle::deepCopy()
	\brief Makes a deep copy of this object.
	\return A pointer to a deeply copied version of this object.

	\fn Triangle::closestIntersection(const Ray& ray)
	\brief Computes the closes intersection between the ray and this object.
	\param ray The ray with wich we want to compute the intersection.
	\return The distance between the ray origin and the intersection. Returns -1 if the ray does not intersect with the object.

	\fn Triangle::getNormal(const DoubleVec3D& point)
	\brief Computes the normal at a point on the object.
	\param point The point on the object at which we want to compute the normal.
	\return The cross product between (vertex2 - vertex1) and (vertex3 - vertex1)

	\fn Triangle::getRandomPoint(double (*randomDouble)())
	\brief Computes a random point on the object.
	\param randomDouble A pointer to a function generating a random double between 0 and 1.
	\return A random point on this object.

	\fn Triangle::getDescription(std::ostream& stream)
	\brief Returns this object's description.
	\param stream The current stream.
	\return The stream with the description.

	\fn Triangle::getType()
	\brief Returns this object type.
	\return "Triangle".

	\fn Triangle::getLocationJson()
	\brief Converts this objects's location to json.
	\return This triangle's vertices converted to json.

	\fn Triangle::setLocationJson(const json& j)
	\brief Sets this object's location according to json.
	\param j The json input.
*/


class Triangle : public Object3D {
private:
	DoubleVec3D vertex1, vertex2, vertex3;

public:
	Triangle();
	Triangle(const DoubleVec3D& vertex1, const DoubleVec3D& vertex2, const DoubleVec3D& vertex3, Material* material);
	Triangle(const Triangle& triangle);

	DoubleVec3D getVertex1() const;
	DoubleVec3D getVertex2() const;
	DoubleVec3D getVertex3() const;
	DoubleVec3D getCenter() const;  // virtual method

	void setVertex1(const DoubleVec3D& vertex);
	void setVertex2(const DoubleVec3D& vertex);
	void setVertex3(const DoubleVec3D& vertex);

	void computeArea();
	Object3D* deepCopy() const;

	double closestIntersection(const Ray& ray) const;
	DoubleUnitVec3D getNormal(const DoubleVec3D& point) const;
	DoubleVec3D getRandomPoint(double (*randomDouble)()) const;

	std::ostream& getDescription(std::ostream& stream) const;
	std::string getType() const;
	json getLocationJson() const;
	void setLocationJson(const json& j);
};

#endif