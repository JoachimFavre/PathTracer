#include <iomanip>
#include <iostream>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>
#include <omp.h>

#include "DiffuseMaterial.h"
#include "DoubleVec3D.h"
#include "Object3D.h"
#include "PerspectiveCamera.h"
#include "RefractiveMaterial.h"
#include "Scene.h"
#include "SpecularMaterial.h"
#include "Sphere.h"
#include "Triangle.h"

constexpr unsigned int PICTURE_WIDTH = 500;
constexpr unsigned int PICTURE_HEIGHT = 500;
constexpr double CAMERA_FOCAL_LENGTH = 3;
constexpr double CAMERA_FOV_X = M_PI_4;

constexpr unsigned int NUMBER_THREADS = 8;

constexpr double MAX_DEPTH = 10;
constexpr unsigned int MIN_BOUNCES = 5;  // Less if nothing is hit
constexpr unsigned int SAMPLE_PER_PIXEL = 8;

constexpr bool RUSSIAN_ROULETTE = true;
constexpr double RR_STOP_PROBABILITY = 0.1;

constexpr bool NEXT_EVENT_ESTIMATION = true;

constexpr double MIDDLE_GRAY = 100;


int main() {
	double beginningTime = getCurrentTimeSeconds();

	// Display doubles with 2 decimals
	std::cout << std::fixed;
	std::cout << std::setprecision(2);

	PerspectiveCamera camera(PICTURE_WIDTH, PICTURE_HEIGHT, CAMERA_FOCAL_LENGTH, CAMERA_FOV_X);
	Scene scene(camera, SAMPLE_PER_PIXEL, MIN_BOUNCES, MAX_DEPTH);

	// Make scene
	// Spheres
	scene.addObject(new Sphere(DoubleVec3D(0, 1.5, -2.5), 0.5, new DiffuseMaterial(DoubleVec3D(0), 10000)));
	scene.addObject(new Sphere(DoubleVec3D(0.2, -1.5, -3), 0.5, new RefractiveMaterial(1.5)));
	scene.addObject(new Sphere(DoubleVec3D(1.2, -1.5, -2.4), 0.5, new SpecularMaterial));
	scene.addObject(new Sphere(DoubleVec3D(-1, -1.5, -2.3), 0.5, new DiffuseMaterial(DoubleVec3D(6))));
	// left
	scene.addObject(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, -2, 1), DoubleVec3D(-2, -2, -4), new DiffuseMaterial(DoubleVec3D(2, 2, 10))));
	scene.addObject(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, -2, -4), DoubleVec3D(-2, 2, -4), new DiffuseMaterial(DoubleVec3D(2, 2, 10))));
	// right
	scene.addObject(new Triangle(DoubleVec3D(2, -2, -4), DoubleVec3D(2, -2, 1), DoubleVec3D(2, 2, 1), new DiffuseMaterial(DoubleVec3D(10, 2, 2))));
	scene.addObject(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(2, -2, -4), DoubleVec3D(2, 2, 1), new DiffuseMaterial(DoubleVec3D(10, 2, 2))));
	// Top
	scene.addObject(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(-2, 2, 1), DoubleVec3D(-2, 2, -4), new DiffuseMaterial(DoubleVec3D(3))));
	scene.addObject(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(2, 2, -4), DoubleVec3D(2, 2, 1), new DiffuseMaterial(DoubleVec3D(3))));
	// Bottom
	scene.addObject(new Triangle(DoubleVec3D(-2, -2, 1), DoubleVec3D(2, -2, -4), DoubleVec3D(-2, -2, -4), new DiffuseMaterial(DoubleVec3D(3))));
	scene.addObject(new Triangle(DoubleVec3D(2, -2, -4), DoubleVec3D(-2, -2, 1), DoubleVec3D(2, -2, 1), new DiffuseMaterial(DoubleVec3D(3))));
	// Background
	scene.addObject(new Triangle(DoubleVec3D(-2, 2, -4), DoubleVec3D(-2, -2, -4), DoubleVec3D(2, 2, -4), new DiffuseMaterial(DoubleVec3D(2, 10, 2))));
	scene.addObject(new Triangle(DoubleVec3D(2, 2, -4), DoubleVec3D(-2, -2, -4), DoubleVec3D(2, -2, -4), new DiffuseMaterial(DoubleVec3D(2, 10, 2))));
	// Behind camera
	scene.addObject(new Triangle(DoubleVec3D(2, 2, 1), DoubleVec3D(2, -2, 1), DoubleVec3D(-2, -2, 1), new DiffuseMaterial(DoubleVec3D(6))));
	scene.addObject(new Triangle(DoubleVec3D(-2, 2, 1), DoubleVec3D(2, 2, 1), DoubleVec3D(-2, -2, 1), new DiffuseMaterial(DoubleVec3D(6))));

	scene.render()->write(MIDDLE_GRAY);

	// Measure time and make sound to warn that it is ended
	std::cout << "\nComputed in " << getCurrentTimeSeconds() - beginningTime << " seconds.\n";
	std::cout << "\a";

	return 0;
}
