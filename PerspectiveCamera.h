#ifndef DEF_PERSPECTIVECAMERA
#define DEF_PERSPECTIVECAMERA

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "DoubleVec3D.h"
#include "Ray.h"

class PerspectiveCamera {
private:
	unsigned int width, height;
	double fovX;

public:
	PerspectiveCamera();
	PerspectiveCamera(unsigned int width, unsigned int height, double fovX = M_PI/4);
	PerspectiveCamera(const PerspectiveCamera& camera);
	
	unsigned int getWidth();
	unsigned int getHeigt();
	double getFovX();

	void setWidth(unsigned int width);
	void setHeight(unsigned int height);
	void setFovX(double fovX);

	Ray getRayGoingThrough(double pixelX, double pixelY);
};

#endif
