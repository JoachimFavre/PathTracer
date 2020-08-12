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


enum class Page {
	ParametersPage,
	ObjectsPage
};


void clearScreen() {
	std::system("cls");  // clear screen

	std::cout << "Joachim Favre's TM" << std::endl;
	std::cout << "Bidirectional path tracer" << std::endl;
	std::cout << "**************************" << std::endl;
	std::cout << std::endl;
}

void displayCommands(Page currentPage) {
	bool isParametersPage = currentPage == Page::ParametersPage;

	std::cout << std::endl;
	std::cout << "**************************" << std::endl;
	std::cout << std::endl;
	std::cout << "You can use the following commands:" << std::endl;
	std::cout << "- [number]: modify the corresponding " << (isParametersPage ? "parameter" : "object") << std::endl;

	if (!isParametersPage)
		std::cout << "- a: add an object" << std::endl;

	std::cout << "- e: exit this program" << std::endl;

	if(!isParametersPage)
		std::cout << "- i: import an object from a FBX file" << std::endl;

	std::cout << "- l: load a parameter file and overwrite current objects & parameters" << std::endl;
	std::cout << "- p: switch to " << (isParametersPage ? "objects" : "parameters") << " page" << std::endl;
	std::cout << "- r: start the rendering" << std::endl;
	std::cout << "- s: save current objects and parameters to a file" << std::endl;
	std::cout << std::endl;
}

void displayParametersPage() {
	clearScreen();

	std::cout << "Camera" << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "0) Picture width = " << PICTURE_WIDTH << std::endl;
	std::cout << "1) Picture height = " << PICTURE_WIDTH << std::endl;
	std::cout << "2) Focal length = " << CAMERA_FOCAL_LENGTH << std::endl;
	std::cout << "3) X field of view = " << CAMERA_FOV_X << std::endl;
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

	displayCommands(Page::ParametersPage);
}

void displayObjectsPage() {
	clearScreen();

	std::vector<Object3DGroup> objectGroups = scene.getObjectsGroups();

	for (unsigned int i = 0; i < objectGroups.size(); i++) {
		Object3DGroup currentObjectGroup = objectGroups[i];

		std::cout << i << ") " << currentObjectGroup << std::endl << std::endl;
	}

	displayCommands(Page::ObjectsPage);
}


int main() {
	scene.resetObjectGroups();
	scene.defaultScene();
	bool firstPage = false;

	std::string information;
	while (true) {
		if (!firstPage)
			displayParametersPage();
		else
			displayObjectsPage();
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
