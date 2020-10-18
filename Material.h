#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "DoubleVec3D.h"
#include "Ray.h"

//! Abstrat class that models a material.
class Material {
private:
	DoubleVec3D emittance;

public:
	//! Default and main constructor.
	/*!
		\param emittance The light this material emits.
	*/
	Material(DoubleVec3D emittance = 0);

	//! Copy constructor.
	/*!
		\param material The material that will be copied.
	*/
	Material(const Material& material);


	//! Getter for the emittance attribute.
	/*!
		\return The emittance of this material.
	*/
	DoubleVec3D getEmittance() const;

	//! Setter for the emittance attribute.
	/*!
		\param emittance The new emittance of this material.
	*/
	void setEmittance(DoubleVec3D emittance);


	//! Makes a deep copy of this material.
	/*!
		\return A pointer to a deeply copied version of this material.
	*/
	virtual Material* deepCopy() const = 0;
	
	//! Computes the new ray direction.
	/*!
		\param previousRay The ray that hits this material.
		\param normal The normal at the intersection.
		\param randomDouble A pointer to a function generating a random double between 0 and 1.
	*/
	virtual DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const = 0;  // Must give pointer to random double because doesn't work with unif and re or including random

	//! Computes the new colour.
	/*!
		\param recursiveColour The colour recursively obtained.
		\param angleNewDirectionNormal The angle between the cosine of the angle between the next ray's direction and the normal at the intersection.
		\return The new colour.
	*/
	virtual DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const = 0;
	
	//! Returns whether this material works with next event estimation.
	/*!
		\return True if this material works with the next event estimation algorithm, false else.
	*/
	virtual bool worksWithNextEventEstimation() const = 0;

	//! Returns this material's description.
	/*!
		\param stream The current stream.
		\return The stream with the description.
	*/
	virtual std::ostream& getDescription(std::ostream& stream) const = 0;

	/*!
		\return Returns this material type ("Diffuse", "Refractive", ...)
	*/
	virtual std::string getType() const = 0;


	//! Converts this material to json.
	/*!
		\return This material converted to json.
	*/
	virtual json getSpecificParametersJson() const = 0;

	//! Sets this material's values according to json.
	/*!
		\param j The json input.
	*/
	virtual void setSpecificParametersJson(const json& j) = 0;
};

//! Ostream operator.
/*!
	Calls the getDescription() method.
	\param stream The ostream before.
	\param vec The material that will be added to the stream.
	\return The stream with the material added.
	\sa getDescription()
*/
std::ostream& operator<<(std::ostream& stream, const Material& material);

#endif
