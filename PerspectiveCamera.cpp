#include "PerspectiveCamera.h"

// Constructors
PerspectiveCamera::PerspectiveCamera()
    : numberPixelsX(500), numberPixelsY(500), focalLength(1), tanFovX(tan(M_PI_4)) {}

PerspectiveCamera::PerspectiveCamera(unsigned int numberPixelsX, unsigned int numberPixelsY, double focalLength /*= 1*/, double fovX /*= M_PI / 4*/)
    : numberPixelsX(numberPixelsX), numberPixelsY(numberPixelsY), focalLength(focalLength), tanFovX(tan(fovX)) {}

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& camera)
    : numberPixelsX(camera.numberPixelsX), numberPixelsY(camera.numberPixelsY), focalLength(camera.focalLength), tanFovX(camera.tanFovX) {}


// Getters
unsigned int PerspectiveCamera::getNumberPixelsX() { return numberPixelsX; }
unsigned int PerspectiveCamera::getNumberPixelsY() { return numberPixelsY; }
double PerspectiveCamera::getTanFovX() { return tanFovX; }
double PerspectiveCamera::getTanFovY() { return numberPixelsY/numberPixelsX*tanFovX; }
double PerspectiveCamera::getFocalLength() { return focalLength; }
double PerspectiveCamera::getWorldWidth() { return 2*focalLength*tanFovX; }
double PerspectiveCamera::getWorldHeight() { return 2*focalLength*getTanFovY(); }


// Setters
void PerspectiveCamera::setNumberPixelsX(unsigned int numberPixelsX) { this->numberPixelsX = numberPixelsX; }
void PerspectiveCamera::setNumberPixelsY(unsigned int numberPixelsY) { this->numberPixelsY = numberPixelsY; }
void PerspectiveCamera::setFocalLength(double focalLength) { this->focalLength = focalLength; }
void PerspectiveCamera::setFovX(double fovX) { this->tanFovX = tan(fovX); }


// Other methods
Ray PerspectiveCamera::getRayGoingThrough(double pixelX, double pixelY) {
    DoubleVec3D rayOrigin(0.0);
    double worldWidth = getWorldWidth();
    double worldHeight = getWorldHeight();
    DoubleVec3D rayDirection(worldWidth/numberPixelsX*(pixelX + 0.5) - 0.5*worldWidth,
                             getWorldHeight()/numberPixelsY*(pixelY + 0.5) - 0.5*worldHeight,
                             -focalLength);  // Gets normalised in ray constructor
    return Ray(rayOrigin, rayDirection);
}