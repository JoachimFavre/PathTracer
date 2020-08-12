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
#include "Interface.h"

unsigned int pictureWidth = 500;
unsigned int pictureHeight = 500;
double caneraFocalLength = 3;
double cameraFovX = M_PI_4;

unsigned int samplePerPixels = 1;
unsigned int minBounces = 5;  // Less if nothing is hit
double maxDepth = 10;

unsigned int numberThreads = 8;
bool russianRoulette = true;
double rrStopProbability = 0.1;
bool nextEventEstimation = true;

Scene scene;

enum class Page {
	ParametersPage,
	ObjectsPage
};

Page currentPage = Page::ParametersPage;

void clearScreenPrintHeader();
void displayParametersPage();
void displayObjectsPage();
void receiveAndExecuteCommand();
void displayCommands();
void drawCurrentPage();


void displayParametersPage() {
	std::cout << "Camera" << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "0) Picture width = " << pictureWidth << std::endl;
	std::cout << "1) Picture height = " << pictureHeight << std::endl;
	std::cout << "2) Focal length = " << caneraFocalLength << std::endl;
	std::cout << "3) X field of view = " << cameraFovX << std::endl;
	std::cout << std::endl;

	std::cout << "Basic parameters" << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "4) Sample per pixels = " << samplePerPixels << std::endl;
	std::cout << "5) Minimum bounces = " << minBounces << std::endl;
	std::cout << "6) Max depth = " << maxDepth << std::endl;
	std::cout << std::endl;

	std::cout << "Optimisation parameters" << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "7) Number of threads = " << numberThreads << std::endl;
	std::cout << "8) Russian roulette = " << (russianRoulette ? "True" : "False") << std::endl;
	std::cout << "9) Rr stop probability = " << rrStopProbability << std::endl;
	std::cout << "10) Next event estimation = " << (nextEventEstimation ? "True" : "False") << std::endl;
	std::cout << std::endl;
}


void displayObjectsPage() {
	std::vector<Object3DGroup> objectGroups = scene.getObjectsGroups();

	for (unsigned int i = 0; i < objectGroups.size(); i++) {
		Object3DGroup currentObjectGroup = objectGroups[i];

		std::cout << i << ") " << currentObjectGroup << std::endl << std::endl;
	}
}


void displayCommands() {
	bool isParametersPage = currentPage == Page::ParametersPage;

	std::cout << std::endl;
	std::cout << "**************************" << std::endl;
	std::cout << std::endl;
	std::cout << "You can use the following commands:" << std::endl;

	if (!isParametersPage) {
		std::cout << "- a: add an object group" << std::endl;
		std::cout << "- d: delete an object group" << std::endl;
	}

	std::cout << "- e: exit this program" << std::endl;

	if (!isParametersPage)
		std::cout << "- i: import an object from a FBX file" << std::endl;

	std::cout << "- l: load a parameter file and overwrite current objects & parameters" << std::endl;
	std::cout << "- m: modify a " << (isParametersPage ? "parameter" : "object group") << std::endl;
	std::cout << "- p: switch to " << (isParametersPage ? "objects" : "parameters") << " page" << std::endl;
	std::cout << "- r: start the rendering" << std::endl;
	std::cout << "- s: save current objects and parameters to a file" << std::endl;
}


void receiveAndExecuteCommand() {
	while (true) {
		bool isParametersPage = currentPage == Page::ParametersPage;
		char command = getCharFromUser();

		switch (command) {
			case 'a': {
				Object3DGroup newGroup = Object3DGroup::create();
				newGroup.modify();
				return;
			}
			case 'e': {
				std::cout << std::endl << "Have a nice day!" << std::endl;
				exit(0);
			}
			case 'p': {
				if (isParametersPage)
					currentPage = Page::ObjectsPage;
				else
					currentPage = Page::ParametersPage;
				return;
			}
		}
	}
}


void drawCurrentPage() {
	while (true) {
		clearScreenPrintHeader();
		if (currentPage == Page::ParametersPage)
			displayParametersPage();
		else
			displayObjectsPage();
		displayCommands();

		receiveAndExecuteCommand();
	}
}


int main() {
	std::cout << std::fixed;
	std::cout << std::setprecision(2);

	scene.resetObjectGroups();
	scene.defaultScene();
	drawCurrentPage();
	
	/*
	double beginningTime = getCurrentTimeSeconds();
	// Display doubles with 2 decimals

	// Instantiate camera and scene
	PerspectiveCamera camera(PICTURE_WIDTH, PICTURE_HEIGHT, CAMERA_FOCAL_LENGTH, CAMERA_FOV_X);
	Scene scene(camera, SAMPLE_PER_PIXEL, MIN_BOUNCES, MAX_DEPTH, RR_STOP_PROBABILITY);
	scene.setRussianRoulette(RUSSIAN_ROULETTE);
	scene.setNextEventEstimation(NEXT_EVENT_ESTIMATION);
	scene.setNumberThreads(NUMBER_THREADS);

	if (useDefaultScene) {
		scene.defaultScene();
	} else { // Read file
		// scene.importFBX(FILE_PATH);
		// scene.addObject(new Sphere(DoubleVec3D(0, 1.5, -2.5), 0.5, new DiffuseMaterial(DoubleVec3D(0), 4000)));
	}

	// Render and write picture
	scene.render()->writeToFile(MIDDLE_GRAY);

	// Measure time and make sound to warn that it is ended
	std::cout << std::endl << "Total computation time: " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl;
	std::cout << "\a";
	*/
	
	return 0;
}
