#include "PerspectiveCamera.h"

// Constructors
PerspectiveCamera::PerspectiveCamera()
    : width(500), height(500), fovX(M_PI_4){}

PerspectiveCamera::PerspectiveCamera(unsigned int width, unsigned int height, double fovX /*= M_PI/4*/)
    : width(width), height(height), fovX(fovX) {}

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& camera)
    : width(camera.width), height(camera.height), fovX(camera.fovX) {}


// Getters
unsigned int PerspectiveCamera::getWidth() { return width; }
unsigned int PerspectiveCamera::getHeigt() { return height; }
double PerspectiveCamera::getFovX() { return fovX; }


// Setters
void PerspectiveCamera::setWidth(unsigned int width) { this->width = width; }
void PerspectiveCamera::setHeight(unsigned int height) { this->height = height; }
void PerspectiveCamera::setFovX(double fovX) { this->fovX = fovX; }


// Other methods
Ray PerspectiveCamera::getRayGoingThrough(unsigned int pixelX, unsigned int pixelY) {
    DoubleVec3 rayOrigin(0.0);
    DoubleVec3 rayDirection((2.0*pixelX - width)/width * tan(fovX),
                            (2.0*pixelY - height)/height * tan(height/width*fovX),
                            -1.0);  // Gets normalised in constructor
    return Ray(rayOrigin, rayDirection);
}