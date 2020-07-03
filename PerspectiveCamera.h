#ifndef DEF_PERSPECTIVECAMERA
#define DEF_PERSPECTIVECAMERA

#include "DoubleVec3.h"
#include "Ray.h"

class PerspectiveCamera {
private:
	unsigned int width, height;
	double fovX;

public:
	PerspectiveCamera();
	PerspectiveCamera(unsigned int width, unsigned int height, double fovX);
	PerspectiveCamera(const PerspectiveCamera& camera);
	
	unsigned int getWidth();
	unsigned int getHeigt();
	double getFovX();

	void setWidth(unsigned int width);
	void setHeight(unsigned int height);
	void setFovX(double fovX);

	Ray getRayGoingThrough(unsigned int pixelX, unsigned int pixelY);
};

#endif
