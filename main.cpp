#include <vector>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

#include "Object3D.h"
#include "Sphere.h"
#include "PerspectiveCamera.h"

std::vector<Object3D*> scene;

constexpr unsigned int PICTURE_WIDTH = 500;
constexpr unsigned int PICTURE_HEIGHT = 500;
constexpr double CAMERA_FOV_X = M_PI_4;

constexpr double MAX_DEPTH = 10;
constexpr unsigned int MAX_ITERATION = 5;
constexpr unsigned int SAMPLE_PER_PIXEL = 8;

int main() {
	
	scene.push_back(new Sphere(DoubleVec3(0, 0, 2), 1, Material(DoubleVec3(5), BRDF::Diffuse, 1000)));
	
	
	PerspectiveCamera camera(PICTURE_WIDTH, PICTURE_HEIGHT, CAMERA_FOV_X);


	return 0;
}
