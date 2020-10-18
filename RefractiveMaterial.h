#ifndef DEF_REFRACTIVEMATERIAL
#define DEF_REFRACTIVEMATERIAL

#include "DoubleVec3D.h"
#include "Material.h"
#include "Object3D.h"
#include "Ray.h"


//! Models a refractive material
class RefractiveMaterial : public Material {
private:
	double refractiveIndex;

public:
	//! Default and main constructor.
	/*!
		\param refractiveIndex The refractive index of this material.
		\param emittance The light this material emits.
	*/
	RefractiveMaterial(double refractiveIndex = 1.5, DoubleVec3D emittance = 0);

	//! Copy constructor.
	/*!
		\param material The material that will be copied.
	*/
	RefractiveMaterial(const RefractiveMaterial& material);


	//! Getter for the refractiveIndex attribute.
	/*!
		\return The refractive index of this material.
		\sa setRefractiveIndex()
	*/
	double getRefractiveIndex() const;

	//! Setter for the refractiveIndex attribute.
	/*!
		\param refractiveIndex The new refractive index of this material.
		\sa getRefractiveIndex()
	*/
	void setRefractiveIndex(double refractiveIndex);
	

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


	//! Returns "Refractive"
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
