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
	RefractiveMaterial(const DoubleVec3D& colour, double refractiveIndex);
	RefractiveMaterial(const RefractiveMaterial& material);

	double getRefractiveIndex() const;
	void setRefractiveIndex(double refractiveIndex);

	DoubleVec3D getNextRay(const Ray& previousRay, Object3D* intersectedObject, const DoubleVec3D& intersectionPoint) const;
	double getBRDFFactor() const;
};

#endif
