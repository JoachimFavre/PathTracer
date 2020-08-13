#include "PerspectiveCamera.h"

// Constructors
PerspectiveCamera::PerspectiveCamera()
    : numberPixelsX(500), numberPixelsY(500), focalLength(1), fovX(M_PI_4), tanFovX(tan(fovX)) {}

PerspectiveCamera::PerspectiveCamera(unsigned int numberPixelsX, unsigned int numberPixelsY, double focalLength /*= 1*/, double fovX /*= M_PI_4*/)
    : numberPixelsX(numberPixelsX), numberPixelsY(numberPixelsY), focalLength(focalLength), fovX(fovX), tanFovX(tan(fovX)) {}

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& camera)
    : numberPixelsX(camera.numberPixelsX), numberPixelsY(camera.numberPixelsY), focalLength(camera.focalLength), fovX(camera.fovX), tanFovX(camera.tanFovX) {}


// Getters
unsigned int PerspectiveCamera::getNumberPixelsX() const { return numberPixelsX; }
unsigned int PerspectiveCamera::getNumberPixelsY() const { return numberPixelsY; }
double PerspectiveCamera::getFovX() const { return fovX; }
double PerspectiveCamera::getTanFovX() const { return tanFovX; }
double PerspectiveCamera::getTanFovY() const { return numberPixelsY/numberPixelsX*tanFovX; }
double PerspectiveCamera::getFocalLength() const { return focalLength; }
double PerspectiveCamera::getWorldWidth() const { return 2*focalLength*tanFovX; }
double PerspectiveCamera::getWorldHeight() const { return 2*focalLength*getTanFovY(); }


// Setters
void PerspectiveCamera::setNumberPixelsX(unsigned int numberPixelsX) { this->numberPixelsX = numberPixelsX; }
void PerspectiveCamera::setNumberPixelsY(unsigned int numberPixelsY) { this->numberPixelsY = numberPixelsY; }
void PerspectiveCamera::setFocalLength(double focalLength) { this->focalLength = focalLength; }

void PerspectiveCamera::setFovX(double fovX) {
	this->fovX = fovX; 
	this->tanFovX = tan(fovX);
}


// Other methods
Ray PerspectiveCamera::getRayGoingThrough(double pixelX, double pixelY) const {
    DoubleVec3D rayOrigin(0.0);
    double worldWidth = getWorldWidth();
    double worldHeight = getWorldHeight();
    DoubleUnitVec3D rayDirection(worldWidth/numberPixelsX*(pixelX + 0.5) - 0.5*worldWidth,
                                 getWorldHeight()/numberPixelsY*(numberPixelsY - pixelY + 0.5) - 0.5*worldHeight,
                                 -focalLength);
    return Ray(rayOrigin, rayDirection);
}