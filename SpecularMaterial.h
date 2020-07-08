#include "DoubleVec3D.h"
#include "Material.h"
#include "Object3D.h"
#include "Ray.h"

#ifndef DEF_SPECULARMATERIAL
#define DEF_SPECULARMATERIAL

class SpecularMaterial : public Material {
public:
	SpecularMaterial();
	SpecularMaterial(const DoubleVec3D& colour, double emittance = 0);
	SpecularMaterial(const SpecularMaterial& material);

	DoubleVec3D getNewDirection(const Ray& previousRay, const DoubleVec3D& normal, double (*randomDouble)()) const;
	DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const;
};

#endif