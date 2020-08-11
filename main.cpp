#include <iomanip>
#include <iostream>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>
#include <omp.h>

#include "DiffuseMaterial.h"
#include "DoubleMatrix33.h"
#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
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
constexpr unsigned int SAMPLE_PER_PIXEL = 1;

constexpr bool RUSSIAN_ROULETTE = true;
constexpr double RR_STOP_PROBABILITY = 0.1;

constexpr bool NEXT_EVENT_ESTIMATION = true;

constexpr double MIDDLE_GRAY = 100;

constexpr bool useDefaultScene = true;
// const char* FILE_PATH = "_mesh.fbx";

Scene scene;

void clearScreen() {
	std::system("cls");  // clear screen

	std::cout << "Joachim Favre's TM" << std::endl;
	std::cout << "Bidirectional path tracer" << std::endl;
	std::cout << "**************************" << std::endl;
	std::cout << std::endl;
}

void displayInformations() {
	clearScreen();

	std::cout << "Camera" << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "0) Picture width = " << PICTURE_WIDTH << std::endl;
	std::cout << "1) Picture height = " << PICTURE_WIDTH << std::endl;
	std::cout << "2) Focal length = " << CAMERA_FOCAL_LENGTH << std::endl;
	std::cout << "3) FOV x = " << CAMERA_FOV_X << std::endl;
	std::cout << std::endl;

	std::cout << "Basic parameters" << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "4) Sample per pixels = " << SAMPLE_PER_PIXEL << std::endl;
	std::cout << "5) Minimum bounces = " << MIN_BOUNCES << std::endl;
	std::cout << "6) Max depth = " << MAX_DEPTH << std::endl;
	std::cout << std::endl;

	std::cout << "Optimisation parameters" << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "7) Number of threads = " << NUMBER_THREADS << std::endl;
	std::cout << "8) Russian roulette = " << (RUSSIAN_ROULETTE ? "True" : "False") << std::endl;
	std::cout << "9) Rr stop probability = " << RR_STOP_PROBABILITY << std::endl;
	std::cout << "10) Next event estimation = " << (NEXT_EVENT_ESTIMATION ? "True" : "False") << std::endl;
	std::cout << std::endl;

	// std::cout << "Write one of this number to modify its linked value, 0 to see and modify the list of current objects or -1 to start the rendering." << std::endl;
}

void displayObjects() {
	clearScreen();

	std::vector<Object3D*> objects = scene.getObjects();

	for (unsigned int i = 0; i < objects.size(); i++) {
		Object3D* currentObject = objects[i];

		std::cout << i << ") " << currentObject->getName() << std::endl;
		std::cout << "--------------------------" << std::endl;
		std::cout << *currentObject << std::endl;
		std::cout << "-> " << *(currentObject->getMaterial()) << std::endl;
		std::cout << std::endl;
	}
}


int main() {
	scene.resetObjects();
	scene.defaultScene();
	bool firstPage = false;

	std::string information;
	while (true) {
		if (!firstPage)
			displayInformations();
		else
			displayObjects();
		firstPage = !firstPage;
		std::cin >> information;
	}

	/*
	double beginningTime = getCurrentTimeSeconds();
	// Display doubles with 2 decimals
	std::cout << std::fixed;
	std::cout << std::setprecision(2);

	// Instantiate camera and scene
	PerspectiveCamera camera(PICTURE_WIDTH, PICTURE_HEIGHT, CAMERA_FOCAL_LENGTH, CAMERA_FOV_X);
	Scene scene(camera, SAMPLE_PER_PIXEL, MIN_BOUNCES, MAX_DEPTH, RR_STOP_PROBABILITY);
	scene.setRussianRoulette(RUSSIAN_ROULETTE);
	scene.setNextEventEstimation(NEXT_EVENT_ESTIMATION);
	scene.setNumberThreads(NUMBER_THREADS);

	if (useDefaultScene) {
		scene.defaultScene();
	} else { // Read file
		scene.importFBX(FILE_PATH);
		scene.addObject(new Sphere(DoubleVec3D(0, 1.5, -2.5), 0.5, new DiffuseMaterial(DoubleVec3D(0), 4000)));
	}

	// Render and write picture
	scene.render()->writeToFile(MIDDLE_GRAY);

	// Measure time and make sound to warn that it is ended
	std::cout << std::endl << "Total computation time: " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl;
	std::cout << "\a";
	*/
	return 0;
}
