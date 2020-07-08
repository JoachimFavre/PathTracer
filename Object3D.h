#ifndef DEF_OBJECT3D
#define DEF_OBJECT3D

#include "DiffuseMaterial.h"
#include "DoubleVec3D.h"
#include "Material.h"
#include "Ray.h"

class Object3D {
private:
	Material* material;

public:
	Object3D();
	Object3D(Material* material);
	Object3D(const Object3D& obj);

	~Object3D();

	Material* getMaterial() const;
	void setMaterial(Material* material);

	virtual double closestIntersection(const Ray& ray) const = 0;
	virtual DoubleVec3D getNormal(const DoubleVec3D& point) const = 0;
};

#endif
