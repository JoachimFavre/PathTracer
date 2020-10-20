#ifndef DEF_OBJECT3D
#define DEF_OBJECT3D

#include <string>

#include "DiffuseMaterial.h"
#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Material.h"
#include "Ray.h"


/*!
	\file Object3D.h
	\brief Defines the Object3D class and the functions around it.

	\class Object3D
	\brief Abstract class for a three-dimentional object.

	\fn Object3D::Object3D()
	\brief Default constructor.
	\details The default material is a diffuse one.

	\fn Object3D::Object3D(Material* material)
	\brief Main constructor.
	\param material The material of this object.

	\fn Object3D::Object3D(const Object3D& obj)
	\brief Copy constructor.
	\param obj The object that will be copied.

	\fn Object3D::~Object3D()
	\brief Destructor.

	\fn Object3D::getMaterial()
	\brief Getter for the Material.
	\return A pointer to this object's material.

	\fn Object3D::setMaterial(Material* material)
	\brief Setter for the Material.
	\param material The new material of this object.

	\fn Object3D::deepCopy()
	\brief Makes a deep copy of this object.
	\return A pointer to a deeply copied version of this object.

	\fn Object3D::closestIntersection(const Ray& ray)
	\brief Computes the closes intersection between the ray and this object.
	\param ray The ray with wich we want to compute the intersection.
	\return The distance between the ray origin and the intersection (the smalles one if there is more than one intersection). Returns -1 if the ray does not intersect with the object.

	\fn Object3D::getNormal(const DoubleVec3D& point)
	\brief Computes the normal at a point on the object.
	\param point The point on the object at which we want to compute the normal.
	\return The normal at this point.

	\fn Object3D::getRandomPoint(double (*randomDouble)())
	\brief Computes a random point on the object.
	\param randomDouble A pointer to a function generating a random double between 0 and 1.
	\return A random point on this object.

	\fn Object3D::getDescription(std::ostream& stream)
	\brief Returns this object's description.
	\param stream The current stream.
	\return The stream with the description.

	\fn Object3D::getCenter()
	\brief Returns this object's center.
	\return The center of this object.

	\fn Object3D::getType()
	\brief Returns this object type.
	\return Returns this object type ("Sphere", "Triangle", ...).

	\fn Object3D::getLocationJson()
	\brief Converts this objects's location to json.
	\return This object's location converted to json.

	\fn Object3D::setLocationJson(const json& j)
	\brief Sets this object's location according to json.
	\param j The json input.

	\fn Object3D::operator=(const Object3D& otherObject)
	\brief Assignment operator.
	\details Makes a deepcopy of the material before copying it.
	\param otherObject The object to which this will be equal.

	\fn operator<<(std::ostream& stream, const Object3D& object)
	\brief Ostream operator.
	\details Calls the getDescription() method.
	\param stream The ostream before.
	\param object The object that will be added to the stream.
	\return The stream with the object added.
	\sa getDescription()
*/


class Object3D {
private:
	Material* material;

public:
	Object3D();
	Object3D(Material* material);
	Object3D(const Object3D& obj);
	~Object3D();

	Material* getMaterial() const;
	void setMaterial(Material* material);

	virtual Object3D* deepCopy() const = 0;

	virtual double closestIntersection(const Ray& ray) const = 0;
	virtual DoubleUnitVec3D getNormal(const DoubleVec3D& point) const = 0;
	virtual DoubleVec3D getRandomPoint(double (*randomDouble)()) const = 0;
	virtual std::ostream& getDescription(std::ostream& stream) const = 0;
	virtual DoubleVec3D getCenter() const = 0;

	virtual std::string getType() const = 0;
	virtual json getLocationJson() const = 0;
	virtual void setLocationJson(const json& j) = 0;

	Object3D& operator=(const Object3D& otherObject);
};

std::ostream& operator<<(std::ostream& stream, const Object3D& object);

#endif
