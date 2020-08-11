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
	std::string name;
	Material* material;

public:
	Object3D();
	Object3D(const std::string& name, Material* material);
	Object3D(const Object3D& obj);

	~Object3D();

	std::string getName() const;
	Material* getMaterial() const;

	void setName(const std::string& name);
	void setMaterial(Material* material);

	virtual double closestIntersection(const Ray& ray) const = 0;
	virtual DoubleUnitVec3D getNormal(const DoubleVec3D& point) const = 0;
	virtual DoubleVec3D getRandomPoint(double (*randomDouble)()) const = 0;
	virtual std::ostream& getDescription(std::ostream& stream) const = 0;
};

std::ostream& operator<<(std::ostream& stream, const Object3D& object);

#endif
