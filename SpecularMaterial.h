#include "DoubleVec3D.h"
#include "Material.h"
#include "Object3D.h"
#include "Ray.h"

#ifndef DEF_SPECULARMATERIAL
#define DEF_SPECULARMATERIAL

class SpecularMaterial : public Material {
public:
	SpecularMaterial(double emittance = 0);
	SpecularMaterial(const SpecularMaterial& material);

	DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const;
	DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const;
	bool worksWithNextEventEstimation() const;
};

#endif