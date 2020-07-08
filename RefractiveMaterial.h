#include "Material.h"
#include "DoubleVec3D.h"
#include "Ray.h"
#include "Object3D.h"

#ifndef DEF_REFRACTIVEMATERIAL
#define DEF_REFRACTIVEMATERIAL

class RefractiveMaterial : public Material {
private:
	double refractiveIndex;

public:
	RefractiveMaterial();
	RefractiveMaterial(const DoubleVec3D& colour, double refractiveIndex, double emittance = 0);
	RefractiveMaterial(const RefractiveMaterial& material);

	double getRefractiveIndex() const;
	void setRefractiveIndex(double refractiveIndex);

	DoubleVec3D getNewDirection(const Ray& previousRay, const DoubleVec3D& normal, double (*randomDouble)()) const;
	DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const;
};

#endif
