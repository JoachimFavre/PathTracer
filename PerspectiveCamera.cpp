#include "PerspectiveCamera.h"

// Constructors
PerspectiveCamera::PerspectiveCamera()
    : PerspectiveCamera(500, 500) {}

PerspectiveCamera::PerspectiveCamera(unsigned int numberPixelsX, unsigned int numberPixelsY, DoubleVec3D origin /*= DoubleVec3D(0.0)*/, DoubleVec3D focal /*= DoubleVec3D(0, 0, -0.75)*/)
    : numberPixelsX(numberPixelsX), numberPixelsY(numberPixelsY), origin(origin), focal(focal) {
	computeBases();
}

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& camera)
    : PerspectiveCamera(camera.numberPixelsX, camera.numberPixelsY, camera.origin, camera.focal) {}


// Getters
unsigned int PerspectiveCamera::getNumberPixelsX() const { return numberPixelsX; }
unsigned int PerspectiveCamera::getNumberPixelsY() const { return numberPixelsY; }
DoubleVec3D PerspectiveCamera::getOrigin() const { return origin; }
DoubleVec3D PerspectiveCamera::getFocal() const { return focal; }
double PerspectiveCamera::getWorldWidth() const { return 1; }
double PerspectiveCamera::getWorldHeight() const { return numberPixelsY/numberPixelsX*getWorldWidth(); }


// Setters
void PerspectiveCamera::setNumberPixelsX(unsigned int numberPixelsX) { this->numberPixelsX = numberPixelsX; computeBases(); }
void PerspectiveCamera::setNumberPixelsY(unsigned int numberPixelsY) { this->numberPixelsY = numberPixelsY; computeBases(); }
void PerspectiveCamera::setOrigin(DoubleVec3D origin) { this->origin = origin; computeBases(); }
void PerspectiveCamera::setFocal(DoubleVec3D focal) { this->focal = focal; computeBases(); }


// Other methods
void PerspectiveCamera::computeBases() {
	if (-DBL_EPSILON < focal.getX() && focal.getX() < DBL_EPSILON)
		baseX = DoubleUnitVec3D(1, 0, 0);
	else
		baseX = DoubleUnitVec3D(-focal.getZ() / focal.getX(), 0, 1);

	baseY = crossProd(baseX, focal);

	if (baseY.getY() < 0) {
		baseX = -baseX;
		baseY = -baseY;
	}
}

Ray PerspectiveCamera::getRayGoingThrough(double pixelX, double pixelY) const {
	DoubleUnitVec3D rayDirection = 1.0/numberPixelsX*((pixelX - numberPixelsX/2)*baseX - (pixelY - numberPixelsY/2)*baseY) + focal;
	return Ray(origin, rayDirection);
}
