#ifndef DEF_TRIANGLEPLANE
#define DEF_TRIANGLEPLANE

#include "Object3D.h"
#include "DoubleVec3D.h"
#include "Material.h"

class TrianglePlane : public Object3D {
private:
	DoubleVec3D vertex1, vertex2, vertex3;

public:
	TrianglePlane();
	TrianglePlane(const DoubleVec3D& vertex1, const DoubleVec3D& vertex2, const DoubleVec3D& vertex3, const Material& material);
	TrianglePlane(const TrianglePlane& triangle);

	DoubleVec3D getVertex1() const;
	DoubleVec3D getVertex2() const;
	DoubleVec3D getVertex3() const;

	void setVertex1(const DoubleVec3D& vertex);
	void setVertex2(const DoubleVec3D& vertex);
	void setVertex3(const DoubleVec3D& vertex);

	double closestIntersection(const Ray& ray) const;
	DoubleVec3D getNormal(const DoubleVec3D& point) const;
};

#endif