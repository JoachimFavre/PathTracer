#include "PerspectiveCamera.h"

// Constructors
PerspectiveCamera::PerspectiveCamera()
    : width(500), height(500), fovX(M_PI/4){}

PerspectiveCamera::PerspectiveCamera(unsigned int width, unsigned int height, double fovX /*= M_PI/4*/)
    : width(width), height(height), fovX(fovX) {}

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& camera)
    : width(camera.width), height(camera.height), fovX(camera.fovX) {}


