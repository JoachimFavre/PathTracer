#ifndef DEF_SPHERE
#define DEF_SPHERE

#include <math.h>

#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Material.h"
#include "Object3D.h"
#include "Ray.h"

/*!
	\file Sphere.h
	\brief Defines the Sphere class.

	\class Sphere
	\brief A sphere described by its center and its raidus.

	\fn Sphere::Sphere()
	\brief Default constructor.
	\details Sets the center at (0, 0, 0) and the radius at 1.

	\fn Sphere::Sphere(const DoubleVec3D& center, double radius, Material* material)
	\brief Main constructor
	\param center The center of this sphere.
	\param radius The radius of this sphere.
	\param material A pointer to the material of this sphere.

	\fn Sphere::Sphere(const Sphere& sphere)
	\brief Copy constructor.
	\param sphere The sphere that will be copied.

	\fn Sphere::getRadius()
	\brief Getter for the radius.
	\return This sphere's radius.

	\fn Sphere::getCenter()
	\brief Getter for the center.
	\return This sphere's center.

	\fn Sphere::setCenter(const DoubleVec3D& center)
	\brief Setter for the center.
	\param center The new center of this sphere.

	\fn Sphere::setRadius(double radius)
	\brief Setter for the radius.
	\param radius The new radius of this sphere.

	\fn Sphere::computeArea()
	\brief Computes this sphere's area.
	\details Modifies Object3D::area. It uses the formula A = 4*pi*radius.

	\fn Sphere::deepCopy()
	\brief Makes a deep copy of this object.
	\return A pointer to a deeply copied version of this object.

	\fn Sphere::closestIntersection(const Ray& ray)
	\brief Computes the closes intersection between the ray and this object.
	\param ray The ray with wich we want to compute the intersection.
	\return The distance between the ray origin and the intersection (the smalles one if there is more than one intersection). Returns -1 if the ray does not intersect with the object.

	\fn Sphere::getNormal(const DoubleVec3D& point)
	\brief Computes the normal at a point on the object.
	\param point The point on the object at which we want to compute the normal.
	\return The normal at this point.

	\fn Sphere::getRandomPoint(double (*randomDouble)())
	\brief Computes a random point on the object.
	\param randomDouble A pointer to a function generating a random double between 0 and 1.
	\return A random point on this object.

	\fn Sphere::getDescription(std::ostream& stream)
	\brief Returns this object's description.
	\param stream The current stream.
	\return The stream with the description.

	\fn Sphere::getType()
	\brief Returns this object type.
	\return "Sphere".

	\fn Sphere::getLocationJson()
	\brief Converts this objects's location to json.
	\return This sphere's center and radius converted to json.

	\fn Sphere::setLocationJson(const json& j)
	\brief Sets this object's location according to json.
	\param j The json input.
*/


class Sphere : public Object3D {
private:
	DoubleVec3D center;
	double radius;

public:
	Sphere();
	Sphere(const DoubleVec3D& center, double radius, Material* material);
	Sphere(const Sphere& sphere);

	double getRadius() const;
	DoubleVec3D getCenter() const;  // virtual method

	void setCenter(const DoubleVec3D& center);
	void setRadius(double radius);

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