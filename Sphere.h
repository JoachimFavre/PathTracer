#ifndef DEF_SPHERE
#define DEF_SPHERE

#include <math.h>

#include "Object3D.h";
#include "Material.h"
#include "DoubleVec3D.h"
#include "Ray.h"

class Sphere : public Object3D {
private:
	DoubleVec3D center;
	double radius;

public:
	Sphere();
	Sphere(const DoubleVec3D& center, double radius, const Material& material);
	Sphere(const Sphere& sphere);

	DoubleVec3D getCenter() const;
	double getRadius() const;

	void setCenter(const DoubleVec3D& center);
	void setRadius(double radius);

	double closestIntersection(const Ray& ray) const;
	DoubleVec3D getNormal(const DoubleVec3D& point) const;
};

#endif