#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "DoubleVec3D.h"
#include "Ray.h"


/*!
	\file Material.h
	\brief Defines the Material class and the functions around it.

	\class Material
	\brief Abstrat class that models a material.

	\fn Material::Material(DoubleVec3D emittance = 0)
	\brief Default and main constructor.
	\param emittance The light this material emits.

	\fn Material::Material(const Material& material)
	\brief Copy constructor.
	\param material The material that will be copied.

	\fn Material::getEmittance()
	\brief Getter for the emittance attribute.
	\return The emittance of this material.

	\fn Material::setEmittance(DoubleVec3D emittance)
	\brief Setter for the emittance attribute.
	\param emittance The new emittance of this material.

	\fn Material::deepCopy()
	\brief Makes a deep copy of this material.
	\return A pointer to a deeply copied version of this material.

	\fn Material::getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)())
	\brief Computes the new ray direction.
	\param previousRay The ray that hits this material.
	\param normal The normal at the intersection.
	\param randomDouble A pointer to a function generating a random double between 0 and 1.

	\fn Material::computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal)
	\brief Computes the new colour.
	\param recursiveColour The colour recursively obtained.
	\param angleNewDirectionNormal The angle between the cosine of the angle between the next ray's direction and the normal at the intersection.
	\return The new colour.

	\fn Material::worksWithNextEventEstimation()
	\brief Returns whether this material works with next event estimation.
	\return True if this material works with the next event estimation algorithm, false else.

	\fn Material::getDescription(std::ostream& stream)
	\brief Returns this material's description.
	\param stream The current stream.
	\return The stream with the description.

	\fn Material::getType()
	\brief Returns this material type.
	\return Returns this material type ("Diffuse", "Refractive", ...)

	\fn Material::getSpecificParametersJson()
	\brief Converts this material's specific parameters to json.
	\return This material's specific parameters converted to json.

	\fn Material::setSpecificParametersJson(const json& j)
	\brief Sets this material's specific parameters according to json.
	\param j The json input.

	\fn operator<<(std::ostream& stream, const Material& material)
	\brief Ostream operator.
	\details Calls the getDescription() method.
	\param stream The ostream before.
	\param material The material that will be added to the stream.
	\return The stream with the material added.
	\sa getDescription()
*/


class Material {
private:
	DoubleVec3D emittance;

public:
	Material(DoubleVec3D emittance = 0);
	Material(const Material& material);

	DoubleVec3D getEmittance() const;
	void setEmittance(DoubleVec3D emittance);

	virtual Material* deepCopy() const = 0;
	
	virtual DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const = 0;  // Must give pointer to random double because doesn't work with unif and re or including random
	virtual DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const = 0;
	virtual bool worksWithNextEventEstimation() const = 0;

	virtual std::ostream& getDescription(std::ostream& stream) const = 0;
	virtual std::string getType() const = 0;
	virtual json getSpecificParametersJson() const = 0;
	virtual void setSpecificParametersJson(const json& j) = 0;
};

std::ostream& operator<<(std::ostream& stream, const Material& material);

#endif
