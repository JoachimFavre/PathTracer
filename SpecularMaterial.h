#include "Material.h"
#include "DoubleVec3D.h"
#include "Ray.h"
#include "Object3D.h"

#ifndef DEF_SPECULARMATERIAL
#define DEF_SPECULARMATERIAL

class SpecularMaterial : public Material {
public:
	SpecularMaterial();
	SpecularMaterial(const DoubleVec3D& colour);
	SpecularMaterial(const SpecularMaterial& material);

	DoubleVec3D getNextRay(const Ray& previousRay, Object3D* intersectedObject, const DoubleVec3D& intersectionPoint) const;
	double getBRDFFactor() const;
};

#endif