#ifndef DEF_RAY
#define DEF_RAY

#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"

class Ray {
private:
	DoubleVec3D origin;
	DoubleUnitVec3D direction;

public:
	Ray();
	Ray(const DoubleVec3D& origin, const DoubleUnitVec3D& direction);
	Ray(const Ray& ray);

	DoubleVec3D getOrigin() const;
	DoubleUnitVec3D getDirection() const;

	void setOrigin(const DoubleVec3D& origin);
	void setDirection(const DoubleUnitVec3D& direction);
};

#endif
