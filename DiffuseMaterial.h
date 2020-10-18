#ifndef DEF_DIFFUSEMATERIAL
#define DEF_DIFFUSEMATERIAL

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Material.h"
#include "Ray.h"


//! Models a diffuse material
class DiffuseMaterial : public Material {
private:
	DoubleVec3D colour;

public:
	//! Default and main constructor.
	/*!
		\param colour The colour of this material.
		\param emittance The light this material emits.
	*/
	DiffuseMaterial(const DoubleVec3D& colour = DoubleVec3D(0.0), DoubleVec3D emittance = 0);

	//! Copy constructor.
	/*!
		\param material The material that will be copied.
	*/
	DiffuseMaterial(const DiffuseMaterial& material);


	//! Getter for the colour attribute.
	/*!
		\return The colour of this material.
		\sa setColour()
	*/
	DoubleVec3D getColour() const;
	
	//! Getter for the colour attribute.
	/*!
		\param colour The new colour of this material.
		\sa getColour()
	*/
	void setColour(const DoubleVec3D& colour);


	//! Makes a deep copy of this material.
	/*!
		\return A pointer to a deeply copied version of this material.
	*/
	Material* deepCopy() const;

	//! Computes the new ray direction.
	/*!
		\param previousRay The ray that hits this material.
		\param normal The normal at the intersection.
		\param randomDouble A pointer to a function generating a random double between 0 and 1.
	*/
	DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const;

	//! Computes the new colour.
	/*!
		\param recursiveColour The colour recursively obtained.
		\param angleNewDirectionNormal The angle between the cosine of the angle between the next ray's direction and the normal at the intersection.
		\return The new colour.
	*/
	DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const;
	
	//! Returns whether this material works with next event estimation.
	/*!
		\return True.
	*/
	bool worksWithNextEventEstimation() const;

	//! Returns this material's description.
	/*!
		\param stream The current stream.
		\return The stream with the description.
	*/
	std::ostream& getDescription(std::ostream& stream) const;

	//! Returns "Diffuse".
	std::string getType() const;

	//! Converts this material to json.
	/*!
		\return This material converted to json.
	*/
	json getSpecificParametersJson() const;

	//! Sets this material's values according to json.
	/*!
		\param j The json input.
	*/
	void setSpecificParametersJson(const json& j);
};


#endif