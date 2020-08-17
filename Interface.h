#ifndef DEF_INTERFACE
#define DEF_INTERFACE

#include <iostream>
#include <fstream>
#include <string>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Object3D.h"
#include "Sphere.h"
#include "Triangle.h"
#include "DiffuseMaterial.h"
#include "SpecularMaterial.h"
#include "RefractiveMaterial.h"

constexpr unsigned int MAX_LENGTH_STRING_FROM_USER = 256;
const std::string PROMPT = "> ";
const std::string STAR_SPLITTER(26, '*');
const std::string DASH_SPLITTER(26, '-');
const std::string INVALID_COMMAND = "Invalid command.";

const std::string FBX_EXTENSION = "fbx";
const std::string OBJECTS_SAVE_EXTENSION = "ptobj";
const std::string PARAMETERS_SAVE_EXTENSION = "ptparam";

// Common parts in interface
static void clearScreenPrintHeader() {
	std::system("cls");

	std::cout << "Joachim Favre's TM" << std::endl;
	std::cout << "Bidirectional path tracer" << std::endl;
	std::cout << STAR_SPLITTER << std::endl;
	std::cout << std::endl;
}


static void availableCommandsHeader() {
	std::cout << std::endl;
	std::cout << STAR_SPLITTER << std::endl;
	std::cout << std::endl;
	std::cout << "You can use the following commands:" << std::endl;
}


// Conversion into string
static std::string bool2string(bool b) {
	return (b ? "True" : "False");
}


// Get from user
static std::string getStringFromUser(std::string question = "", std::string prompt = PROMPT) {
	char userText[MAX_LENGTH_STRING_FROM_USER];
	while (true) {
		if (question != "")
			std::cout << question << std::endl;
		std::cout << prompt;
		std::cin.getline(userText, MAX_LENGTH_STRING_FROM_USER);
		if (std::cin.fail()) {
			std::cout << "This string is too long." << std::endl << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			return userText;
	}
}


static char getCharFromUser(std::string question = "", std::string prompt = PROMPT) {
	return (getStringFromUser(question, prompt))[0];
}


// Too many repetitions, I have to correct that
static int getIntFromUser(std::string question = "", std::string prompt = PROMPT) {
	while (true) {
		std::string userText = getStringFromUser(question, prompt);

		try {
			return std::stoi(userText);
		} catch (const std::invalid_argument& exception) {
			std::cout << "This is not a number!";
		} catch (const std::out_of_range& exception) {
			std::cout << "This number is too big! (What were you expecting?)";
		}

		std::cout << std::endl << std::endl;
	}
}


static unsigned int getUnsignedIntFromUser(std::string question = "", std::string prompt = PROMPT) {
	while (true) {
		int value = getIntFromUser(question, prompt);
		if (value >= 0)
			return value;
		std::cout << "This is not a positive number!" << std::endl << std::endl;
	}
}

static double getDoubleFromUser(std::string question = "", std::string prompt = PROMPT) {
	while (true) {
		std::string userText = getStringFromUser(question, prompt);

		try {
			return std::stod(userText);
		} catch (const std::invalid_argument& exception) {
			std::cout << "This is not a number!";
		} catch (const std::out_of_range& exception) {
			std::cout << "This number is either too big or with too many decimals.";
		}

		std::cout << std::endl << std::endl;
	}
}

static double getPositiveDoubleFromUser(std::string question = "", std::string prompt = PROMPT) {
	while (true) {
		double value = getDoubleFromUser(question, prompt);
		if (value >= 0)
			return value;
		std::cout << "This is not a positive number!" << std::endl << std::endl;
	}
}


static bool getBoolFromUser(std::string question = "", std::string prompt = PROMPT) {
	while (true) {
		char userText = getCharFromUser(question, prompt);

		if (userText == 'T' || userText == 't')
			return true;
		else if (userText == 'F' || userText == 'f')
			return false;
		else
			std::cout << "This is not a boolean!" << std::endl << std::endl;

	}
}

static DoubleVec3D getXYZDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT) {
	// Use array?
	double x = getDoubleFromUser(question, "x " + prompt);
	double y = getDoubleFromUser("", "y " + prompt);
	double z = getDoubleFromUser("", "z " + prompt);

	return DoubleVec3D(x, y, z);
}

static DoubleVec3D getRGBDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT) {
	// Use array?
	double x = getPositiveDoubleFromUser(question, "r " + prompt);
	double y = getPositiveDoubleFromUser("", "g " + prompt);
	double z = getPositiveDoubleFromUser("", "b " + prompt);

	return DoubleVec3D(x, y, z);
}


// File manipulation
static bool fileExists(std::string fileName) {
	std::ifstream f(fileName.c_str());
	return f.good();
}

static std::string formatFileName(std::string fileName, std::string extension) {
	if (extension[0] != '.')
		extension = "." + extension;

	if (fileName.size() < extension.size())
		return fileName + extension;

	int extensionBeginningInFileName = fileName.size() - extension.size();

	for (int i = 0; i < extension.size(); i++) {
		if (!(std::tolower(fileName[extensionBeginningInFileName + i]) == std::tolower(extension[i]))) {
			return fileName + extension;
		}
	}

	return fileName;
}


// Materials
static Material* createDiffuseMaterial(const DoubleVec3D& emittance) {
	DoubleVec3D colour = getRGBDoubleVec3DFromUser("What is the colour of this diffuse material?");
	std::cout << std::endl;
	return new DiffuseMaterial(colour, emittance);
}

static Material* createRefractiveMaterial(const DoubleVec3D& emittance) {
	double refractiveIndex = getPositiveDoubleFromUser("What is the refractive index of this material? (1 = no refraction / 1.5 = glass)");
	std::cout << std::endl;
	return new RefractiveMaterial(refractiveIndex, emittance);
}

static Material* createSpecularMaterial(const DoubleVec3D& emittance) {
	return new SpecularMaterial(emittance);
}

static Material* createMaterial() {
	while (true) {
		char command = getCharFromUser("Do you want a (d)iffuse material, a (r)efractive material or a (s)pecular material?");
		if (command == 'd' || command == 'r' || command == 's') {
			std::cout << std::endl;
			DoubleVec3D emittance = getRGBDoubleVec3DFromUser("What is the emittance of this material? ((0, 0, 0) if not a lamp)");
			std::cout << std::endl;

			switch (command) {
			case 'd': return createDiffuseMaterial(emittance);
			case 'r': return createRefractiveMaterial(emittance);
			case 's': return createSpecularMaterial(emittance);
			}
		}
		else
			std::cout << INVALID_COMMAND << std::endl << std::endl;
	}
}


// Objects
static Object3D* createSphere(Material* material) {
	DoubleVec3D center = getXYZDoubleVec3DFromUser("What is the center of the sphere?");
	std::cout << std::endl;
	double radius = getPositiveDoubleFromUser("What is the radius of the sphere?");
	std::cout << std::endl;

	return new Sphere(center, radius, material);
}

static Object3D* createTriangle(Material* material) {
	DoubleVec3D vertex1 = getXYZDoubleVec3DFromUser("What is the first vertex of the triangle? (Order is important for the normal, give them counterclockwise from where they are visible.)");
	std::cout << std::endl;
	DoubleVec3D vertex2 = getXYZDoubleVec3DFromUser("What is the second vertex of the triangle?");
	std::cout << std::endl;
	DoubleVec3D vertex3 = getXYZDoubleVec3DFromUser("What is the third vertex of the triangle?");
	std::cout << std::endl;

	return new Triangle(vertex1, vertex2, vertex3, material);
}

static Object3D* createObject3D() {
	while (true) {
		char command = getCharFromUser("Do you want a (s)phere or a (t)riangle?");
		if (command == 's' || command == 't') {
			std::cout << std::endl;
			Material* material = createMaterial();
			
			switch (command) {
			case 's': return createSphere(material);
			case 't': return createTriangle(material);
			}
		}
		else
			std::cout << INVALID_COMMAND << std::endl << std::endl;
	}
}

// Json
static void to_json(json& j, const Material& mat) {
	j = json{ {"MaterialType", mat.getType()},  {"Emittance", mat.getEmittance()}, {"SpecificParameters", mat.getSpecificParametersJson()} };
}

static Material* importMaterialFromJson(const json& j) {
	std::string materialType = j["MaterialType"].get<std::string>();
	Material* mat = nullptr;

	if (materialType == "Diffuse")
		mat = new DiffuseMaterial;
	else if (materialType == "Refractive")
		mat = new RefractiveMaterial;
	else if (materialType == "Specular")  // Use obj.getType static?
		mat = new SpecularMaterial;


	mat->setEmittance(j["Emittance"].get<DoubleVec3D>());
	mat->setSpecificParametersJson(j["SpecificParameters"]);

	return mat;
}

static void to_json(json& j, const Object3D& obj) {
	j = json{ {"ObjectType", obj.getType()}, {"Material", *(obj.getMaterial())}, {"Location", obj.getLocationJson()} };
}

static Object3D* importObject3DFromJson(const json& j) {
	std::string objectType = j["ObjectType"].get<std::string>();
	Object3D* obj = nullptr;

	if (objectType == "Sphere")
		obj = new Sphere;
	else if (objectType == "Triangle")
		obj = new Triangle;

	obj->setMaterial(importMaterialFromJson(j["Material"]));
	obj->setLocationJson(j["Location"]);

	return obj;
}

#endif
