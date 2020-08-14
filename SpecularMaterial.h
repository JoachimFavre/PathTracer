#ifndef DEF_SPECULARMATERIAL
#define DEF_SPECULARMATERIAL

#include "DoubleVec3D.h"
#include "Material.h"
#include "Object3D.h"
#include "Ray.h"


class SpecularMaterial : public Material {
public:
	SpecularMaterial(DoubleVec3D emittance = 0);
	SpecularMaterial(const SpecularMaterial& material);

	Material* deepCopy() const;
	DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const;
	DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const;
	bool worksWithNextEventEstimation() const;
	std::ostream& getDescription(std::ostream& stream) const;

	std::string getType() const;
	json getSpecificParametersJson() const;
};

#endif