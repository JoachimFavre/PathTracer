#ifndef DEF_SPHERE
#define DEF_SPHERE

#include <math.h>

#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Material.h"
#include "Object3D.h"
#include "Ray.h"

class Sphere : public Object3D {
private:
	DoubleVec3D center;
	double radius;

public:
	Sphere();
	Sphere(const DoubleVec3D& center, double radius, Material* material);
	Sphere(const Sphere& sphere);

	DoubleVec3D getCenter() const;  // virtual method
	double getRadius() const;

	void setCenter(const DoubleVec3D& center);
	void setRadius(double radius);

	Object3D* deepCopy() const;
	double closestIntersection(const Ray& ray) const;
	DoubleUnitVec3D getNormal(const DoubleVec3D& point) const;
	DoubleVec3D getRandomPoint(double (*randomDouble)()) const;
	std::ostream& getDescription(std::ostream& stream) const;
};

#endif