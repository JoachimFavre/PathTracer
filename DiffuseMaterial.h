#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "DoubleVec3D.h"
#include "Material.h"
#include "Object3D.h"
#include "Ray.h"

#ifndef DEF_DIFFUSEMATERIAL
#define DEF_DIFFUSEMATERIAL

class DiffuseMaterial : public Material {
private:
	DoubleVec3D colour;

public:
	DiffuseMaterial(const DoubleVec3D& colour = DoubleVec3D(0.0), double emittance = 0);
	DiffuseMaterial(const DiffuseMaterial& material);

	DoubleVec3D getColour() const;
	void setColour(const DoubleVec3D& colour);

	DoubleVec3D getNewDirection(const Ray& previousRay, const DoubleVec3D& normal, double (*randomDouble)()) const;
	DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const;
};

#endif