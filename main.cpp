#include <string>
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

Scene scene;
PerspectiveCamera& camera = scene.getCameraReference();
std::vector<Object3DGroup>& objectGroups = scene.getObjectsGroupsReference();

enum class Page {
	ParametersPage,
	ObjectsPage
};

Page currentPage = Page::ParametersPage;
bool commandWasInvalid = false;

void clearScreenPrintHeader();
void displayParametersPage();
void displayObjectsPage();
void receiveAndExecuteParametersCommands(char command);
void receiveAndExecuteObjectsCommands(char command);
void receiveAndExecuteGeneralCommands();
void displayCommands();
void drawCurrentPage();


void displayParametersPage() {
	std::cout << "Camera" << std::endl;
	std::cout << dashSplitter << std::endl;
	std::cout << "0) Picture width = " << camera.getNumberPixelsX() << std::endl;
	std::cout << "1) Picture height = " << camera.getNumberPixelsY() << std::endl;
	std::cout << "2) Focal length = " << camera.getFocalLength() << std::endl;
	std::cout << "3) X field of view = " << camera.getFovX() << std::endl;
	std::cout << std::endl;

	std::cout << "Basic parameters" << std::endl;
	std::cout << dashSplitter << std::endl;
	std::cout << "4) Sample per pixels = " << scene.getSamplePerPixel() << std::endl;
	std::cout << "5) Minimum bounces = " << scene.getMinBounces() << std::endl;
	std::cout << "6) Max depth = " << scene.getMaxDepth() << std::endl;
	std::cout << std::endl;

	std::cout << "Optimisation parameters" << std::endl;
	std::cout << dashSplitter << std::endl;
	std::cout << "7) Number of threads = " << scene.getNumberThreads() << std::endl;
	std::cout << "8) Russian roulette = " << bool2string(scene.getRussianRoulette()) << std::endl;
	std::cout << "9) Rr stop probability = " << scene.getRrStopProbability() << std::endl;
	std::cout << "10) Next event estimation = " << bool2string(scene.getNextEventEstimation()) << std::endl;
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

	availableCommandsHeader();

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


void receiveAndExecuteGeneralCommands() {
	bool isParametersPage = currentPage == Page::ParametersPage;

	std::cout << std::endl;
	char command = getCharFromUser(commandWasInvalid ? invalidCommand : "");
	commandWasInvalid = false;

	std::cout << std::endl;

	switch (command) {
		case 'e': {
			std::cout << "Have a nice day!" << std::endl;
			exit(0);
		}
		case  'l': {

		}
		case 'p': {
			if (isParametersPage)
				currentPage = Page::ObjectsPage;
			else
				currentPage = Page::ParametersPage;
			return;
		}
		case 'r': {

		}
		case 's': {

		}
		default: 
			if (isParametersPage)
				receiveAndExecuteParametersCommands(command);
			else
				receiveAndExecuteObjectsCommands(command);
			return;
	}
}


void receiveAndExecuteParametersCommands(char command) {
	switch (command) {
	case 'm': {
		// Modify a parameter
		while (true) {
			unsigned int index = getUnsignedIntFromUser("What is the index of the parameter you want to modify (positive integer)");
			std::cout << std::endl;
			switch (index) {
			case 0: camera.setNumberPixelsX(getUnsignedIntFromUser("What is the new camera width? (positive integer)")); return;
			case 1: camera.setNumberPixelsY(getUnsignedIntFromUser("What is the new camera height? (positive integer)")); return;
			case 2: camera.setFocalLength(getDoubleFromUser("What is the new camera focal length (number)")); return;
			case 3: camera.setFovX(getDoubleFromUser("What is the new X field of view? (number)")); return;
			case 4: scene.setSamplePerPixel(getUnsignedIntFromUser("What is the new number of sample per pixel? (positive integer)")); return;
			case 5: scene.setMinBounces(getUnsignedIntFromUser("What is the new minimum number of ray bounces? (there can be less if nothing is hit) (positive integer)")); return;
			case 6: scene.setMaxDepth(getDoubleFromUser("What is the new maximum depth? (number)")); return;
			case 7: scene.setNumberThreads(getUnsignedIntFromUser("What is the new number of threads that will used during the rendering? (positive integer)")); return;
			case 8: scene.setRussianRoulette(getBoolFromUser("Will the russian roulette path termination algorithm be used? (True=T=true=t / False=F=false=f)")); return;
			case 9: scene.setRrStopProbability(getDoubleFromUser("What is the new stop probability for the russian roulette path termination algorithm? (number)")); return;
			case 10: scene.setNextEventEstimation(getBoolFromUser("Will the next event estimation algorithm be used? (True=T=true=t / False=F=false=f)")); return;
			default: std::cout << "This index is too big" << std::endl;
			}
		}
	}
	default:
		commandWasInvalid = true;
	}
}

void receiveAndExecuteObjectsCommands(char command) {
	switch (command) {
	case 'a': {
		Object3DGroup newGroup = Object3DGroup::create();
		newGroup.modify();
		return;
	}
	case 'd': {

	}
	case 'i': {

	}
	case 'm': {

	}
	default:
		commandWasInvalid = true;
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

		receiveAndExecuteGeneralCommands();
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
