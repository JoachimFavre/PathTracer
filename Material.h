#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "DoubleVec3D.h"
#include "Ray.h"

class Material {
private:
	DoubleVec3D emittance;

public:
	Material(DoubleVec3D emittance = 0);
	Material(const Material& material);

	DoubleVec3D getEmittance() const;
	void setEmittance(DoubleVec3D emittance);

	virtual DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const = 0;  // Must give pointer to random double because doesn't work with unif and re or including random
	virtual DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const = 0;
	virtual bool worksWithNextEventEstimation() const = 0;
};

#endif
