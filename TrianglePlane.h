#ifndef DEF_TRIANGLEPLANE
#define DEF_TRIANGLEPLANE

#include "Object3D.h"
#include "DoubleVec3.h"
#include "Material.h"
#include "Constants.h"

class TrianglePlane : public Object3D {
private:
	DoubleVec3 vertex1, vertex2, vertex3;

public:
	TrianglePlane();
	TrianglePlane(const DoubleVec3& vertex1, const DoubleVec3& vertex2, const DoubleVec3& vertex3, const Material& material);
	TrianglePlane(const TrianglePlane& triangle);

	DoubleVec3 getVertex1() const;
	DoubleVec3 getVertex2() const;
	DoubleVec3 getVertex3() const;

	void setVertex1(const DoubleVec3& vertex);
	void setVertex2(const DoubleVec3& vertex);
	void setVertex3(const DoubleVec3& vertex);

	double closestIntersection(const Ray& ray) const;
	DoubleVec3 getNormal(const DoubleVec3& point) const;
};

#endif