#include "DoubleVec3D.h"
#include "Material.h"
#include "Object3D.h"
#include "Ray.h"

#ifndef DEF_REFRACTIVEMATERIAL
#define DEF_REFRACTIVEMATERIAL

class RefractiveMaterial : public Material {
private:
	double refractiveIndex;

public:
	RefractiveMaterial(double refractiveIndex = 1.5, DoubleVec3D emittance = 0);
	RefractiveMaterial(const RefractiveMaterial& material);

	double getRefractiveIndex() const;
	void setRefractiveIndex(double refractiveIndex);

	Material* deepCopy() const;
	DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const;
	DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const;
	bool worksWithNextEventEstimation() const;
	std::ostream& getDescription(std::ostream& stream) const;
};

#endif
