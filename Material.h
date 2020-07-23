#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "DoubleVec3D.h"
#include "Ray.h"

class Material {
private:
	double emittance;

public:
	Material(double emittance = 0);
	Material(const Material& material);

	double getEmittance() const;
	void setEmittance(double emittance);

	virtual DoubleUnitVec3D getNewDirection(const Ray& previousRay, const DoubleUnitVec3D& normal, double (*randomDouble)()) const = 0;  // Must give pointer to random double because doesn't work with unif and re or including random
	virtual DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const = 0;
	virtual bool worksWithNextEventEstimation() const = 0;
};

#endif
