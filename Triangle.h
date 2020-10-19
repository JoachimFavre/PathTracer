#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Material.h"
#include "Object3D.h"

//! A triangle defined by its three vertices.
/*!
	The order of its vertices is important. See the main constructor for more information.
*/
class Triangle : public Object3D {
private:
	DoubleVec3D vertex1, vertex2, vertex3;

public:
	//! Default constructor.
	Triangle();

	//! Main constructor
	/*!
		The order of the vertices is important, because the normal is only on one side of the triangle (meaning that the triangle can only be seen from one side). Give the vertices counterclockwise from where you want the triangle to be visible.
		\param vertex1 The first vertex of this triangle.
		\param vertex2 The second vertex of this triangle.
		\param vertex3 The third vertex of this triangle.
		\param material A pointer to the material of this triangle.
	*/
	Triangle(const DoubleVec3D& vertex1, const DoubleVec3D& vertex2, const DoubleVec3D& vertex3, Material* material);
	
	//! Copy constructor.
	/*!
		\param triangle The triangle that will be copied.
	*/
	Triangle(const Triangle& triangle);


	//! Getter for the first vertex.
	/*!
		\return This triangle's first vertex.
	*/
	DoubleVec3D getVertex1() const;

	//! Getter for the second vertex.
	/*!
		\return This triangle's second vertex.
	*/
	DoubleVec3D getVertex2() const;

	//! Getter for the third vertex.
	/*!
		\return This triangle's third vertex.
	*/
	DoubleVec3D getVertex3() const;

	//! Getter for the center.
	/*!
		\return The average of the three vertices.
	*/
	DoubleVec3D getCenter() const;  // virtual method

	//! Setter for the first vertex.
	/*!
		\param vertex The new first vertex of this triangle.
	*/
	void setVertex1(const DoubleVec3D& vertex);

	//! Setter for the second vertex.
	/*!
		\param vertex The new second vertex of this triangle.
	*/
	void setVertex2(const DoubleVec3D& vertex);

	//! Setter for the third vertex.
	/*!
		\param vertex The new third vertex of this triangle.
	*/
	void setVertex3(const DoubleVec3D& vertex);


	//! Makes a deep copy of this object.
	/*!
		\return A pointer to a deeply copied version of this object.
	*/
	Object3D* deepCopy() const;

	//! Computes the closes intersection between the ray and this object.
	/*!
		\param ray The ray with wich we want to compute the intersection.
		\return The distance between the ray origin and the intersection. Returns -1 if the ray does not intersect with the object.
	*/
	double closestIntersection(const Ray& ray) const;

	//! Computes the normal at a point on the object.
	/*!
		\param point The point on the object at which we want to compute the normal.
		\return The cross product between (vertex2 - vertex1) and (vertex3 - vertex1)
	*/
	DoubleUnitVec3D getNormal(const DoubleVec3D& point) const;

	//! Computes a random point on the object.
	/*!
		\param randomDouble A pointer to a function generating a random double between 0 and 1.
		\return A random point on this object.
	*/
	DoubleVec3D getRandomPoint(double (*randomDouble)()) const;

	//! Returns this object's description.
	/*!
		\param stream The current stream.
		\return The stream with the description.
	*/
	std::ostream& getDescription(std::ostream& stream) const;


	//! Returns this object type.
	/*!
		\return "Triangle".
	*/
	std::string getType() const;

	//! Converts this objects's location to json.
	/*!
		\return This triangle's vertices converted to json.
	*/
	json getLocationJson() const;

	//! Sets this object's location according to json.
	/*!
		\param j The json input.
	*/
	void setLocationJson(const json& j);
};

#endif