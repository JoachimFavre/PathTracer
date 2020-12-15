#ifndef DEF_DIFFUSEMATERIAL
#define DEF_DIFFUSEMATERIAL

#include "Material.h"


/*!
	\file DiffuseMaterial.h
	\brief Defines the DiffuseMaterial class.

	\class DiffuseMaterial
	\brief Models a diffuse material

	\fn DiffuseMaterial::DiffuseMaterial(const DoubleVec3D& colour = DoubleVec3D(0.0), DoubleVec3D emittance = 0)
	\brief Default and main constructor.
	\param colour The colour of this material.
	\param emittance The light this material emits.

	\fn DiffuseMaterial::DiffuseMaterial(const DiffuseMaterial& material)
	\brief Copy constructor.
	\param material The material that will be copied.

	\fn DiffuseMaterial::getColour()
	\brief Getter for the colour attribute.
	\return The colour of this material.
	\sa setColour()

	\fn DiffuseMaterial::setColour(const DoubleVec3D& colour)
	\brief Getter for the colour attribute.
	\param colour The new colour of this material.
	\sa getColour()

	\fn DiffuseMaterial::deepCopy()
	\brief Makes a deep copy of this material.
	\return A pointer to a deeply copied version of this material.

	\fn DiffuseMaterial::getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal)
	\brief Computes the new ray direction.
	\param previousRay The ray that hits this material.
	\param normal The normal at the intersection.

	\fn DiffuseMaterial::computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal, bool nextEventEstimation = false)
	\brief Computes the new colour.
	\param recursiveColour The colour recursively obtained.
	\param angleNewDirectionNormal The cosine of the angle between the direction of the next ray and the normal at the intersection.
	\param nextEventEstimation Whether the colour is obtained using the next event estimation algorithm.
	\return The new colour.

	\fn DiffuseMaterial::worksWithNextEventEstimation()
	\brief Returns whether this material works with next event estimation.
	\return True.

	\fn DiffuseMaterial::getDescription(std::ostream& stream)
	\brief Returns this material's description.
	\param stream The current stream.
	\return The stream with the description.

	\fn DiffuseMaterial::getType()
	\brief Returns "Diffuse".

	\fn DiffuseMaterial::getSpecificParametersJson()
	\brief Converts this material's specific parameters to json.
	\return This material's specific parameters converted to json.

	\fn DiffuseMaterial::setSpecificParametersJson(const json& j)
	\brief Sets this material's specific parameters according to json.
	\param j The json input.
*/


class DiffuseMaterial : public Material {
private:
	DoubleVec3D colour;

public:
	DiffuseMaterial(const DoubleVec3D& colour = DoubleVec3D(0.0), DoubleVec3D emittance = 0);
	DiffuseMaterial(const DiffuseMaterial& material);

	DoubleVec3D getColour() const;
	void setColour(const DoubleVec3D& colour);

	Material* deepCopy() const;

	DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal) const;
	DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal, bool nextEventEstimation = false) const;
	bool worksWithNextEventEstimation() const;

	std::ostream& getDescription(std::ostream& stream) const;
	std::string getType() const;
	json getSpecificParametersJson() const;
	void setSpecificParametersJson(const json& j);
};


#endif