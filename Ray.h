#ifndef DEF_RAY
#define DEF_RAY

#include "DoubleVec3.h"

class Ray {
private:
	DoubleVec3 origin, direction;

public:
	Ray();
	Ray(const DoubleVec3& origin, const DoubleVec3& direction);
	Ray(const Ray& ray);

	DoubleVec3 getOrigin() const;
	DoubleVec3 getDirection() const;

	void setOrigin(const DoubleVec3& origin);
	void setDirection(const DoubleVec3& direction);
};

#endif
