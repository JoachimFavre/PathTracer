#ifndef DEF_OBJECT3D
#define DEF_OBJECT3D

#include <string>

#include "DiffuseMaterial.h"
#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Material.h"
#include "Ray.h"

//! Abstract class for a three-dimentional object.
class Object3D {
private:
	Material* material;

public:
	//! Default constructor.
	/*!
		The default material is a diffuse one.
	*/
	Object3D();

	//! Main constructor.
	/*!
		\param material The material of this object.
	*/
	Object3D(Material* material);

	//! Copy constructor.
	/*!
		\param obj The object that will be copied.
	*/
	Object3D(const Object3D& obj);

	//! Destructor.
	~Object3D();

	
	// Getter for the Material.
	/*
		\return A pointer to this object's material.
	*/
	Material* getMaterial() const;

	// Setter for the Material.
	/*
		\param material The new material of this object.
	*/
	void setMaterial(Material* material);


	//! Makes a deep copy of this object.
	/*!
		\return A pointer to a deeply copied version of this object.
	*/
	virtual Object3D* deepCopy() const = 0;

	//! Computes the closes intersection between the ray and this object.
	/*!
		\param ray The ray with wich we want to compute the intersection.
		\return The distance between the ray origin and the intersection (the smalles one if there is more than one intersection). Returns -1 if the ray does not intersect with the object.
	*/
	virtual double closestIntersection(const Ray& ray) const = 0;

	//! Computes the normal at a point on the object.
	/*!
		\param point The point on the object at which we want to compute the normal.
		\return The normal at this point.
	*/
	virtual DoubleUnitVec3D getNormal(const DoubleVec3D& point) const = 0;
	
	//! Computes a random point on the object.
	/*!
		\param randomDouble A pointer to a function generating a random double between 0 and 1.
		\return A random point on this object.
	*/
	virtual DoubleVec3D getRandomPoint(double (*randomDouble)()) const = 0;

	//! Returns this object's description.
	/*!
		\param stream The current stream.
		\return The stream with the description.
	*/
	virtual std::ostream& getDescription(std::ostream& stream) const = 0;

	//! Returns this object's center.
	/*!
		\return The center of this object.
	*/
	virtual DoubleVec3D getCenter() const = 0;

	//! Returns this object type.
	/*!
		\return Returns this object type ("Sphere", "Triangle", ...).
	*/
	virtual std::string getType() const = 0;

	//! Converts this objects's location to json.
	/*!
		\return This object's location converted to json.
	*/
	virtual json getLocationJson() const = 0;

	//! Sets this object's location according to json.
	/*!
		\param j The json input.
	*/
	virtual void setLocationJson(const json& j) = 0;

	//! Assignment operator.
	/*!
		Makes a deepcopy of the material before copying it.
		\param otherObject The object to which this will be equal.
	*/
	Object3D& operator=(const Object3D& otherObject);
};

//! Ostream operator.
/*!
	Calls the getDescription() method.
	\param stream The ostream before.
	\param object The object that will be added to the stream.
	\return The stream with the object added.
	\sa getDescription()
*/
std::ostream& operator<<(std::ostream& stream, const Object3D& object);

#endif
