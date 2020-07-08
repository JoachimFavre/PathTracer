#ifndef DEF_RAY
#define DEF_RAY

#include "DoubleVec3D.h"

class Ray {
private:
	DoubleVec3D origin, direction;

public:
	Ray();
	Ray(const DoubleVec3D& origin, const DoubleVec3D& direction);
	Ray(const Ray& ray);

	DoubleVec3D getOrigin() const;
	DoubleVec3D getDirection() const;

	void setOrigin(const DoubleVec3D& origin);
	void setDirection(const DoubleVec3D& direction);
};

#endif
