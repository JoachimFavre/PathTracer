#ifndef DEF_SPHERE
#define DEF_SPHERE

#include <math.h>

#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Material.h"
#include "Object3D.h"
#include "Ray.h"

//! A sphere described by its center and its raidus.
class Sphere : public Object3D {
private:
	DoubleVec3D center;
	double radius;

public:
	//! Default constructor.
	Sphere();

	//! Main constructor
	/*!
		\param center The center of this sphere.
		\param radius The radius of this sphere.
		\param material A pointer to the material of this sphere.
	*/
	Sphere(const DoubleVec3D& center, double radius, Material* material);

	//! Copy constructor.
	/*!
		\param sphere The sphere that will be copied.
	*/
	Sphere(const Sphere& sphere);


	//! Getter for the radius.
	/*!
		\return This sphere's radius.
	*/
	double getRadius() const;

	//! Getter for the center.
	/*!
		\return This sphere's center.
	*/
	DoubleVec3D getCenter() const;  // virtual method

	//! Setter for the center.
	/*!
		\param center The new center of this sphere.
	*/
	void setCenter(const DoubleVec3D& center);

	//! Setter for the radius.
	/*!
		\param radius The new radius of this sphere.
	*/
	void setRadius(double radius);


	//! Makes a deep copy of this object.
	/*!
		\return A pointer to a deeply copied version of this object.
	*/
	Object3D* deepCopy() const;

	//! Computes the closes intersection between the ray and this object.
	/*!
		\param ray The ray with wich we want to compute the intersection.
		\return The distance between the ray origin and the intersection (the smalles one if there is more than one intersection). Returns -1 if the ray does not intersect with the object.
	*/
	double closestIntersection(const Ray& ray) const;

	//! Computes the normal at a point on the object.
	/*!
		\param point The point on the object at which we want to compute the normal.
		\return The normal at this point.
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
		\return "Sphere".
	*/
	std::string getType() const;

	//! Converts this objects's location to json.
	/*!
		\return This material's location converted to json.
	*/
	json getLocationJson() const;

	//! Sets this material's location according to json.
	/*!
		\param j The json input.
	*/
	void setLocationJson(const json& j);
};

#endif