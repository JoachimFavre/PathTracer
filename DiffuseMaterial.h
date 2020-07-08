#include "Material.h"
#include "DoubleVec3D.h"
#include "Ray.h"
#include "Object3D.h"

#ifndef DEF_DIFFUSEMATERIAL
#define DEF_DIFFUSEMATERIAL

class DiffuseMaterial : public Material {
private:
	double emittance;

public:
	DiffuseMaterial();
	DiffuseMaterial(const DoubleVec3D& colour, double emittance = 0);
	DiffuseMaterial(const DiffuseMaterial& material);

	double getEmittance() const;
	void setEmittance(double emittance);

	DoubleVec3D getNextRay(const Ray& previousRay, Object3D* intersectedObject, const DoubleVec3D& intersectionPoint) const;
	double getBRDFFactor() const;
};

#endif