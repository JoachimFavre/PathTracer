#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Material.h"
#include "Ray.h"

#ifndef DEF_DIFFUSEMATERIAL
#define DEF_DIFFUSEMATERIAL

class DiffuseMaterial : public Material {
private:
	DoubleVec3D colour;

public:
	DiffuseMaterial(const DoubleVec3D& colour = DoubleVec3D(0.0), DoubleVec3D emittance = 0);
	DiffuseMaterial(const DiffuseMaterial& material);

	DoubleVec3D getColour() const;
	void setColour(const DoubleVec3D& colour);

	Material* deepCopy() const;
	DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const;
	DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const;
	bool worksWithNextEventEstimation() const;
	std::ostream& getDescription(std::ostream& stream) const;
};


#endif