#ifndef DEF_SPECULARMATERIAL
#define DEF_SPECULARMATERIAL

#include "DoubleVec3D.h"
#include "Material.h"
#include "Object3D.h"
#include "Ray.h"


// Models a specular material
class SpecularMaterial : public Material {
public:
	//! Default and main constructor.
	/*!
		\param emittance The light this material emits.
	*/
	SpecularMaterial(DoubleVec3D emittance = 0);

	//! Copy constructor.
	/*!
		\param material The material that will be copied.
	*/
	SpecularMaterial(const SpecularMaterial& material);

	//! Makes a deep copy of this material.
	/*!
		\return A pointer to a deeply copied version of this.
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
		\return True if this material works with next event estimation, false else.
	*/
	bool worksWithNextEventEstimation() const;

	//! Returns this material's description.
	/*!
		\param stream The current stream.
		\return The stream with the description.
	*/
	std::ostream& getDescription(std::ostream& stream) const;


	//! Returns "Specular".
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