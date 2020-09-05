#ifndef DEF_PERSPECTIVECAMERA
#define DEF_PERSPECTIVECAMERA

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "DoubleVec3D.h"
#include "Ray.h"

class PerspectiveCamera {
private:
	unsigned int numberPixelsX, numberPixelsY;
	DoubleVec3D origin, focal;

	DoubleUnitVec3D baseX;
	DoubleUnitVec3D baseY;
	void computeBases();

public:
	PerspectiveCamera();
	PerspectiveCamera(unsigned int numberPixelsX, unsigned int numberPixelsY, DoubleVec3D origin = DoubleVec3D(0.0), DoubleVec3D focal = DoubleVec3D(0, 0, -1));
	PerspectiveCamera(const PerspectiveCamera& camera);
	
	unsigned int getNumberPixelsX() const;
	unsigned int getNumberPixelsY() const;
	DoubleVec3D getOrigin() const;
	DoubleVec3D getFocal() const;
	double getWorldWidth() const;
	double getWorldHeight() const;

	void setNumberPixelsX(unsigned int numberPixelsX);
	void setNumberPixelsY(unsigned int numberPixelsY);
	void setOrigin(DoubleVec3D origin);
	void setFocal(DoubleVec3D focal);

	Ray getRayGoingThrough(double pixelX, double pixelY) const;
};

#endif
