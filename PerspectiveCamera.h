#ifndef DEF_PERSPECTIVECAMERA
#define DEF_PERSPECTIVECAMERA

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "DoubleVec3D.h"
#include "Ray.h"

class PerspectiveCamera {
private:
	unsigned int numberPixelsX, numberPixelsY;
	double focalLength, fovX, tanFovX;

public:
	PerspectiveCamera();
	PerspectiveCamera(unsigned int numberPixelsX, unsigned int numberPixelsY, double focalLength = 1, double fovX = M_PI_4);
	PerspectiveCamera(const PerspectiveCamera& camera);
	
	unsigned int getNumberPixelsX() const;
	unsigned int getNumberPixelsY() const;
	double getFovX() const;
	double getTanFovX() const;
	double getTanFovY() const;
	double getFocalLength() const;
	double getWorldWidth() const;
	double getWorldHeight() const;

	void setNumberPixelsX(unsigned int numberPixelsX);
	void setNumberPixelsY(unsigned int numberPixelsY);
	void setFocalLength(double focalLength);
	void setFovX(double fovX);

	Ray getRayGoingThrough(double pixelX, double pixelY) const;
};

#endif
