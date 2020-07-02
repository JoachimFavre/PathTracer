#ifndef DEF_SPHERE
#define DEF_SPHERE

#include <math.h>

#include "Object3D.h";
#include "Material.h"
#include "DoubleVec3.h"
#include "Ray.h"

class Sphere : public Object3D {
private:
	DoubleVec3 center;
	double radius;

public:
	Sphere();
	Sphere(const DoubleVec3& center, double radius, const Material& material);
	Sphere(const Sphere& sphere);

	DoubleVec3 getCenter() const;
	double getRadius() const;

	void setCenter(const DoubleVec3& center);
	void setRadius(double radius);

	double closestIntersection(const Ray& ray) const;
	DoubleVec3 getNormal(const DoubleVec3& point) const;
};

#endif