#ifndef DEF_OBJECT3D
#define DEF_OBJECT3D

#include "Material.h"
#include "DoubleVec3.h"
#include "Ray.h"

class Object3D {
private:
	Material material;

public:
	Object3D();
	Object3D(const Material& material);
	Object3D(const Object3D& obj);

	Material getMaterial() const;
	void setMaterial(const Material& material);

	virtual double closestIntersection(const Ray& ray) const = 0;
	virtual DoubleVec3 getNormal(const DoubleVec3& point) const = 0;
};

#endif
