#include <string>
#include <iomanip>
#include <iostream>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>
#include <omp.h>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Material.h"
#include "DiffuseMaterial.h"
#include "DoubleMatrix33.h"
#include "DoubleVec3D.h"
#include "DoubleUnitVec3D.h"
#include "Object3D.h"
#include "PerspectiveCamera.h"
#include "RefractiveMaterial.h"
#include "SpecularMaterial.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Interface.h"

#include "Scene.h"


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
void receiveAndExecuteGeneralCommands();
void executeParametersCommands(char command);
void executeObjectsCommands(char command);
void displayCommands();
void drawCurrentPage();


void displayParametersPage() {
	std::cout << "Camera" << std::endl;
	std::cout << DASH_SPLITTER << std::endl;
	std::cout << "0) Picture width = " << camera.getNumberPixelsX() << std::endl;
	std::cout << "1) Picture height = " << camera.getNumberPixelsY() << std::endl;
	std::cout << "2) Focal length = " << camera.getFocalLength() << std::endl;
	std::cout << "3) X field of view = " << camera.getFovX() << std::endl;
	std::cout << std::endl;

	std::cout << "Basic parameters" << std::endl;
	std::cout << DASH_SPLITTER << std::endl;
	std::cout << "4) Sample per pixel = " << scene.getSamplePerPixel() << std::endl;
	std::cout << "5) Minimum bounces = " << scene.getMinBounces() << std::endl;
	std::cout << "6) Max depth = " << scene.getMaxDepth() << std::endl;
	std::cout << std::endl;

	std::cout << "Optimisation parameters" << std::endl;
	std::cout << DASH_SPLITTER << std::endl;
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
	bool isObjectsPages = currentPage == Page::ObjectsPage;

	availableCommandsHeader();

	if (isObjectsPages) {
		std::cout << "- a: add an object group" << std::endl;
		std::cout << "- d: delete an object group" << std::endl;
	}

	std::cout << "- e: exit this program" << std::endl;

	if (isObjectsPages) {
		std::cout << "- g: merge two objects groups" << std::endl;
		std::cout << "- i: import an object from a FBX file as an objects group" << std::endl;
		std::cout << "- l: load object groups from a " << OBJECTS_SAVE_EXTENSION << " file and add them to current ones" << std::endl;
	}
	else {
		std::cout << "- l: load parameters from a " << PARAMETERS_SAVE_EXTENSION << " file and overwrite current ones" << std::endl;
	}

	std::cout << "- m: modify a" << (isObjectsPages ?  "n object group" : " parameter") << std::endl;
	std::cout << "- p: switch to " << (isObjectsPages ? "parameters" : "objects") << " page" << std::endl;
	std::cout << "- r: start the rendering" << std::endl;

	if (isObjectsPages)
		std::cout << "- s: save current object groups to a " << OBJECTS_SAVE_EXTENSION << " file" << std::endl;
	else
		std::cout << "- s: save current parameters to a " << PARAMETERS_SAVE_EXTENSION << " file" << std::endl;
}


void receiveAndExecuteGeneralCommands() {
	bool isParametersPage = currentPage == Page::ParametersPage;

	std::cout << std::endl;
	if (commandWasInvalid) {
		commandWasInvalid = false;
		std::cout << INVALID_COMMAND << std::endl;
	}
	char command = getCharFromUser();
	command = std::tolower(command);

	std::cout << std::endl;

	switch (command) {
		case 'e': {
			std::cout << "Have a nice day!" << std::endl;
			exit(0);
		}
		case 'p': {
			if (isParametersPage)
				currentPage = Page::ObjectsPage;
			else
				currentPage = Page::ParametersPage;
			return;
		}
		case 'r': {
			double middleGray = getPositiveDoubleFromUser("What luminance will be the middle-gray? (try 100 if you have no idea) (positive number)");
			std::cout << std::endl;
			std::string filePath = getStringFromUser("What is the name of the file in which the picture will be saved?");
			clearScreenPrintHeader();
			scene.render()->writeToFile(middleGray, filePath);

			std::cout << std::endl;
			getStringFromUser("Press enter to continue.");
		}
		default: 
			if (isParametersPage)
				executeParametersCommands(command);
			else
				executeObjectsCommands(command);
			return;
	}
}


void executeParametersCommands(char command) {
	switch (command) {
	case  'l': {
		std::string fileName = getStringFromUser("What is the name of the " + PARAMETERS_SAVE_EXTENSION + " file from where the parameters will be loaded?");
		fileName = formatFileName(fileName, PARAMETERS_SAVE_EXTENSION);
		std::cout << std::endl;
		double beginningTime = getCurrentTimeSeconds();  // don't want to count user time

		bool exists = fileExists(fileName);
		if (!exists) {
			std::cout << "The file " << fileName << " does not exist." << std::endl << std::endl;
			getStringFromUser("Press enter to continue.");
			return;
		}

		json jsonInput;

		std::ifstream file;
		file.open(fileName);  // File could change name -> need to make another try catch
		try {
			file >> jsonInput;
			file.close();

			json jsonCamera = jsonInput["Camera"];
			camera.setNumberPixelsX(jsonCamera["NumberPixelsX"].get<unsigned int>());
			camera.setNumberPixelsY(jsonCamera["NumberPixelsY"].get<unsigned int>());
			camera.setFocalLength(jsonCamera["FocalLength"].get<double>());
			camera.setFovX(jsonCamera["FovX"].get<double>());
			
			json jsonBasicParameters = jsonInput["BasicParameters"];
			scene.setSamplePerPixel(jsonBasicParameters["SamplePerPixel"].get<unsigned int>());
			scene.setMinBounces(jsonBasicParameters["MinBounces"].get<unsigned int>());
			scene.setMaxDepth(jsonBasicParameters["MaxDepth"].get<double>());

			json jsonOptimisationParameters = jsonInput["OptimisationParameters"];
			scene.setNumberThreads(jsonOptimisationParameters["NumberThreads"].get<unsigned int>());
			scene.setRussianRoulette(jsonOptimisationParameters["RussianRoulette"].get<bool>());
			scene.setRrStopProbability(jsonOptimisationParameters["RrStopProbability"].get<double>());
			scene.setNextEventEstimation(jsonOptimisationParameters["NextEventEstimation"].get<bool>());

			std::cout << "Successfully loaded parameters from " << fileName << " in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl << std::endl;
		}
		catch (const json::exception& e) {
			if(file.is_open())
				file.close();
			std::cout << "The file " << fileName << " is corrupted." << std::endl << "Error: " << e.what() << std::endl << std::endl;
		}

		getStringFromUser("Press enter to continue.");
		return;
	}
	case 'm': {
		// Modify a parameter
		while (true) {
			unsigned int index = getUnsignedIntFromUser("What is the index of the parameter you want to modify (positive integer)");
			std::cout << std::endl;
			switch (index) {
			case 0: camera.setNumberPixelsX(getUnsignedIntFromUser("What is the new camera width? (positive integer)")); return;
			case 1: camera.setNumberPixelsY(getUnsignedIntFromUser("What is the new camera height? (positive integer)")); return;
			case 2: camera.setFocalLength(getPositiveDoubleFromUser("What is the new camera focal length (positive number)")); return;
			case 3: camera.setFovX(getPositiveDoubleFromUser("What is the new X field of view? (positive number)")); return;
			case 4: scene.setSamplePerPixel(getUnsignedIntFromUser("What is the new number of sample per pixel? (positive integer)")); return;
			case 5: scene.setMinBounces(getUnsignedIntFromUser("What is the new minimum number of ray bounces? (there can be less if nothing is hit) (positive integer)")); return;
			case 6: scene.setMaxDepth(getPositiveDoubleFromUser("What is the new maximum depth? (positive number)")); return;
			case 7: scene.setNumberThreads(getUnsignedIntFromUser("What is the new number of threads that will used during the rendering? (positive integer)")); return;
			case 8: scene.setRussianRoulette(getBoolFromUser("Will the russian roulette path termination algorithm be used? (True=T=true=t / False=F=false=f)")); return;
			case 9: scene.setRrStopProbability(getPositiveDoubleFromUser("What is the new stop probability for the russian roulette path termination algorithm? (positive number in [0, 1])")); return;
			case 10: scene.setNextEventEstimation(getBoolFromUser("Will the next event estimation algorithm be used? (True=T=true=t / False=F=false=f)")); return;
			default: std::cout << "This index is too big!" << std::endl;
			}
		}
	}
	case 's': {
		std::string fileName = getStringFromUser("What is the name of the " + PARAMETERS_SAVE_EXTENSION + " file in which the parameters will be saved?");
		std::cout << std::endl;
		fileName = formatFileName(fileName, PARAMETERS_SAVE_EXTENSION);

		if (fileExists(fileName)) {
			bool continue_ = getBoolFromUser("The file " + fileName + " already exists, do you want to continue? (True=T=true=t / False=F=false=f)");
			if (!continue_)
				return;
		}
		std::cout << std::endl;
		double beginningTime = getCurrentTimeSeconds();  // don't want to count user time

		json jsonOutput = {
			{"Camera", {
				{"NumberPixelsX", camera.getNumberPixelsX()},
				{"NumberPixelsY", camera.getNumberPixelsY()},
				{"FocalLength", camera.getFocalLength()},
				{"FovX", camera.getFovX()}
				}
			},
			{"BasicParameters", {
				{"SamplePerPixel", scene.getSamplePerPixel()},
				{"MinBounces", scene.getMinBounces()},
				{"MaxDepth", scene.getMaxDepth()}
				}
			},
			{"OptimisationParameters", {
				{"NumberThreads", scene.getNumberThreads()},
				{"RussianRoulette", scene.getRussianRoulette()},
				{"RrStopProbability", scene.getRrStopProbability()},
				{"NextEventEstimation", scene.getNextEventEstimation()}
				}
			}
		};

		std::ofstream file;
		file.open(fileName);
		file << std::setw(4) << jsonOutput << std::endl;
		file.close();

		std::cout << "Successfully saved objects to " << fileName << " in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl << std::endl;
		getStringFromUser("Press enter to continue.");
		return;
	}
	default:
		commandWasInvalid = true;
	}
}

void executeObjectsCommands(char command) {
	switch (command) {
	case 'a': {
		Object3DGroup newGroup = Object3DGroup::create();
		objectGroups.push_back(newGroup);
		objectGroups[objectGroups.size()-1].modify();
		return;
	}
	case 'd': {
		if (objectGroups.size() >= 1) {
			while (true) {
				int index = getIntFromUser("What is the index of the objects groups you want to delete? (-1 = cancel / -2 = delete all)");
				if (index == -1)
					return;
				if (index == -2) {
					std::cout << std::endl;
					bool confirmation = getBoolFromUser("Do you confirm the deletion of all the objects groups? (True=T=true=t / False=F=false=f)");
					if (confirmation)
						scene.resetObjectGroups();
					return;
				}
				if (index >= 0 && index < objectGroups.size()) {
					std::cout << std::endl;
					bool confirmation = getBoolFromUser("Do you confirm the deletion of this objects group? (True=T=true=t / False=F=false=f)");
					if (confirmation)
						objectGroups.erase(objectGroups.begin() + index);
					return;
				}
				std::cout << "This index is invalid!" << std::endl << std::endl;
			}
		}
		else
			commandWasInvalid = true;
	}
	case 'g': {
		if(objectGroups.size() >= 2) {
			while (true) {
				int index1 = getIntFromUser("What is the index of the first objects group? (-1 = cancel)");
				if (index1 == -1)
					return;
				if (index1 >= 0 && index1 < objectGroups.size()) {
					while (true) {
						std::cout << std::endl;
						int index2 = getIntFromUser("What is the index of the second objects group? (-1 = cancel)");
						if (index2 == -1)
							return;
						if (index2 == index1)
							std::cout << "The second index must be different from the first one" << std::endl << std::endl;
						else if (index2 >= 0 && index2 < objectGroups.size()) {
							std::cout << std::endl;
							std::string newName = getStringFromUser("What is the name of the merged objects group?");
							objectGroups[index1].merge(objectGroups[index2]);
							Object3DGroup newObject = objectGroups[index1];

							objectGroups.erase(objectGroups.begin() + std::max(index1, index2));
							objectGroups.erase(objectGroups.begin() + std::min(index1, index2));

							newObject.setName(newName);
							objectGroups.push_back(newObject);
							return;
						}
						else
							std::cout << "This index is invalid" << std::endl << std::endl;
					}
				}
				std::cout << "This index is invalid" << std::endl << std::endl;
			}
		}
		else
			commandWasInvalid = true;
	}
	case 'i': {
		std::string fileName = getStringFromUser("What is the name of the " + FBX_EXTENSION + " file?");
		fileName = formatFileName(fileName, ".fbx");
		std::cout << std::endl;
		bool exists = fileExists(fileName);

		if (!exists) {
			std::cout << "The file " << fileName << " does not exist." << std::endl << std::endl;
			getStringFromUser("Press enter to continue.");
			return;
		}

		std::string name = getStringFromUser("How do you want to call the objects group?");
		std::cout << std::endl;
		Material* material = createMaterial();
		scene.importFBX(fileName.c_str(), material, name);
		std::cout << std::endl;
		getStringFromUser("Press enter to continue.");
		return;
	}
	case  'l': {
		std::string fileName = getStringFromUser("What is the name of the " + OBJECTS_SAVE_EXTENSION + " file from where the object groups will be loaded?");
		fileName = formatFileName(fileName, OBJECTS_SAVE_EXTENSION);
		std::cout << std::endl;
		double beginningTime = getCurrentTimeSeconds();  // don't want to count user time
			
		bool exists = fileExists(fileName);
		if (!exists) {
			std::cout << "The file " << fileName << " does not exist." << std::endl << std::endl;
			getStringFromUser("Press enter to continue.");
			return;
		}

		json jsonInput;

		std::ifstream file;
		file.open(fileName);  // File could change name -> need to make another try catch
		try {
			file >> jsonInput;
			file.close();

			for (json jsonGroup : jsonInput) {
				objectGroups.push_back(jsonGroup.get<Object3DGroup>());
			}
			std::cout << "Successfully loaded objects from " << fileName << " in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl << std::endl;

		} catch (const json::exception& e) {
			if (file.is_open())
				file.close();
			std::cout << "The file " << fileName << " is corrupted." << std::endl << "Error: " << e.what() << std::endl << std::endl;
		}
			
		getStringFromUser("Press enter to continue.");
		return;
	}
	case 'm': {
		if(objectGroups.size() >= 1) {
			while (true) {
				unsigned int index = getUnsignedIntFromUser("What is the index of the objects groups you want to modify (positive integer)");

				if (index < objectGroups.size()) {
					objectGroups[index].modify();
					return;
				}
				else {
					std::cout << "This index is too big!" << std::endl << std::endl;
				}
			}
		}
		else
			commandWasInvalid = true;
	}
	case 's': {
		std::string fileName = getStringFromUser("What is the name of the " + OBJECTS_SAVE_EXTENSION + " file in which the object groups will be saved?");
		std::cout << std::endl;
		fileName = formatFileName(fileName, OBJECTS_SAVE_EXTENSION);

		if (fileExists(fileName)) {
			bool continue_ = getBoolFromUser("The file " + fileName + " already exists, do you want to continue? (True=T=true=t / False=F=false=f)");
			if (!continue_)
				return;
		}
		std::cout << std::endl;
		double beginningTime = getCurrentTimeSeconds();  // don't want to count user time

		json jsonOutput;
		for (Object3DGroup group : objectGroups) {
			jsonOutput.push_back(group); 
		}

		std::ofstream file;
		file.open(fileName);
		file << std::setw(4) << jsonOutput << std::endl;
		file.close();

		std::cout << "Successfully saved objects to " << fileName << " in " << getCurrentTimeSeconds() - beginningTime << " seconds." << std::endl << std::endl;
		getStringFromUser("Press enter to continue.");
		return;
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
