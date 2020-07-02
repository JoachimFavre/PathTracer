#ifndef DEF_OBJECT3D
#define DEF_OBJECT3D

#include "DoubleVec3.h"
#include "Ray.h"
#include "BRDF.h"

class Object3D {
private:
	DoubleVec3 colour;
	BRDF brdf;
	double emittance;

public:
	Object3D();
	Object3D(const DoubleVec3& colour, BRDF brdf, double emittance = 0);
	Object3D(const Object3D& obj);

	DoubleVec3 getColour() const;
	BRDF getBRDF() const;
	double getEmittance() const;

	void setColour(const DoubleVec3& colour);
	void setBRDF(BRDF brdf);
	void setEmittance(double emittance);

	virtual double closestIntersection(const Ray& ray) const = 0;
};

#endif
