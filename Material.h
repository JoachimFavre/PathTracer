#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "DoubleVec3D.h"
#include "Ray.h"

class Material {
private:
	DoubleVec3D colour;
	double emittance;

public:
	Material();
	Material(const DoubleVec3D& colour, double emittance = 0);
	Material(const Material& material);

	DoubleVec3D getColour() const;
	double getEmittance() const;
	void setColour(const DoubleVec3D& colour);
	void setEmittance(double emittance);

	virtual DoubleVec3D getNewDirection(const Ray& previousRay, const DoubleVec3D& normal, double (*randomDouble)()) const = 0;  // Must give pointer to random double because doesn't work with unif and re or including random
	virtual DoubleVec3D computeCurrentColour(const DoubleVec3D& recursiveColour, double angleNewDirectionNormal) const = 0;
};

#endif
