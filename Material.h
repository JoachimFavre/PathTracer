#ifndef DEF_MATERIAL
#define DEF_MATERIAL

#include "DoubleVec3D.h"
#include "Ray.h"
#include "Object3D.h"

class Material {
private:
	DoubleVec3D colour;

public:
	Material();
	Material(const DoubleVec3D& colour);
	Material(const Material& material);

	DoubleVec3D getColour() const;
	void setColour(const DoubleVec3D& colour);

	virtual DoubleVec3D getNextRay(const Ray& previousRay, Object3D* intersectedObject, const DoubleVec3D& intersectionPoint) const = 0;
	virtual double getBRDFFactor() const = 0;
};

#endif
