#ifndef DEF_SPHERE
#define DEF_SPHERE

#include "Object3D.h";
#include "DoubleVec3.h"
#include "Ray.h"

class Sphere : public Object3D {
private:
	DoubleVec3 center;
	double radius;

public:
	Sphere();
	Sphere(const DoubleVec3& center, double radius, const DoubleVec3& colour, BRDF brdf, double emittance = 0);
	Sphere(const Sphere& sphere);

	DoubleVec3 getCenter() const;
	double getRadius() const;

	void setCenter(const DoubleVec3& center);
	void setRadius(double radius);

	double closestIntersection(const Ray& ray) const;
};

#endif