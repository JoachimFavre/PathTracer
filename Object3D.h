#ifndef DEF_OBJECT3D
#define DEF_OBJECT3D

#include <string>

#include "DiffuseMaterial.h"
#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
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

	virtual Object3D* deepCopy() const = 0;
	virtual double closestIntersection(const Ray& ray) const = 0;
	virtual DoubleUnitVec3D getNormal(const DoubleVec3D& point) const = 0;
	virtual DoubleVec3D getRandomPoint(double (*randomDouble)()) const = 0;
	virtual std::ostream& getDescription(std::ostream& stream) const = 0;
	virtual DoubleVec3D getCenter() const = 0;

	Object3D& operator=(const Object3D& otherObject);
};

std::ostream& operator<<(std::ostream& stream, const Object3D& object);

#endif
