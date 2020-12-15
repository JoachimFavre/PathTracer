#ifndef DEF_INTERFACEGESTION
#define DEF_INTERFACEGESTION

#include <chrono>
#include <fstream>
#include <random>

#include "DiffuseMaterial.h"
#include "SpecularMaterial.h"
#include "RefractiveMaterial.h"
#include "Sphere.h"
#include "Triangle.h"

/*!
	\file InterfaceGestion.h
	\brief Defines functions that are used when drawing the interface.

	\var MAX_LENGTH_STRING_FROM_USER
	\brief Maximum length for a string the user can give.

	\var PROMPT
	\brief String that signal that the user can write a command.

	\var STAR_SPLITTER
	\brief A line of stars.

	\var DASH_SPLITTER
	\brief A line of dashs.

	\var INVALID_COMMAND
	\brief String used when the command is invalid.

	\var PICTURE_EXTENSION
	\brief File extension for pictures.

	\var FBX_EXTENSION
	\brief File extension for FBX files.

	\var PICTURE_SAVE_EXTENSION_JSON
	\brief Custom file extension to save pictures.

	\var OBJECTS_SAVE_EXTENSION
	\brief Custom file extension to save objects groups.

	\var PARAMETERS_SAVE_EXTENSION
	\brief Custom file extension to save parameters.

	\fn clearScreenPrintHeader()
	\brief Clears the console and shows the header.

	\fn availableCommandsHeader()
	\brief Prints a header before printing which commands are available.

	\fn bool2string(bool b)
	\brief Converts a boolean to string.
	\param b The boolean that will be converted.
	\return The boolean converted into a string.

	\fn getCurrentTimeSeconds()
	\brief Gives the number of seconds since 01/01/1970.
	\return The time since 01/01/1970 in seconds.

	\fn randomDouble()
	\brief Computes a random double between 0 and 1
	\return A random double between 0 and 1 generated following a uniform distrbution.

	\fn getStringFromUser(std::string question = "", std::string prompt = PROMPT)
	\brief Gets a string from the user.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The string the user gave.

	\fn getLowerCaseCharFromUser(std::string question = "", std::string prompt = PROMPT)
	\brief Gets a lowercase character from the user.
	\details Uses the getStringFromUser() method and takes the first character of this string.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The character the user gave.
	\sa getStringFromUser()

	\fn getIntFromUser(std::string question = "", std::string prompt = PROMPT)
	\brief Gets an integer from the user.
	\details Uses the getStringFromUser() method. Will continue to ask the question until the user gives a string that can be converted to an int.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The integer the user gave.
	\sa getStringFromUser()

	\fn getUnsignedIntFromUser(std::string question = "", std::string prompt = PROMPT)
	\brief Gets a positive integer from the user.
	\details Uses the getIntFromUser() method. Will continue to ask the question until the user gives a positive integer.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The postive integer the user gave.
	\sa getIntFromUser()

	\fn getDoubleFromUser(std::string question = "", std::string prompt = PROMPT)
	\brief Gets a number from the user.
	\details Uses the getStringFromUser() method. Will continue to ask the question until the user gives a string that can be converted to a double.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The double the user gave.
	\sa getStringFromUser()

	\fn getPositiveDoubleFromUser(std::string question = "", std::string prompt = PROMPT)
	\brief Gets a positive number from the user.
	\details Uses the getDoubleFromUser() method. Will continue to ask the question until the user gives a positive double.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The postive double the user gave.
	\sa getDoubleFromUser()

	\fn getBoolFromUser(std::string question = "", std::string prompt = PROMPT)
	\brief Gets a boolean from the user.
	\details Uses the getLowerCaseCharFromUser() method. Will continue to ask the question until the user gives a 't' or 'f'.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The boolean the user gave.
	\sa getLowerCaseCharFromUser()

	\fn getXYZDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT)
	\brief Gets a vector from the user.
	\details Uses three times the getDoubleFromUser() method. Adds "x ", "y " or "z " before the prompt, to show the user which coordinates he or she is giving.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The vector the user gave.
	\sa getDoubleFromUser()

	\fn getRGBDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT)
	\brief Gets a vector with only positive coordinates from the user.
	\details Uses three times the getPositiveDoubleFromUser() method. Adds "r ", "g " or "b " before the prompt, to show the user which coordinates he or she is giving.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The vector the user gave.
	\sa getPositiveDoubleFromUser()

	\fn fileExists(std::string fileName)
	\brief Verifies if the file exists.
	\param fileName The path to the file.
	\return True if the file exists, false else.

	\fn formatFileName(std::string fileName, std::string extension)
	\brief Formats the name of the file the user gave and the extension we want.
	\details For example, it will format "test.txt" into "test.txt" and "test" into "test.txt".
	\param fileName The path to the file we want to format.
	\param extension The file extension with which we want to format the file.
	\return The formated file name.

	\fn createDiffuseMaterial(const DoubleVec3D& emittance)
	\brief Interactive creation of a DiffuseMaterial.
	\param emittance The emittance of the material.
	\return A pointer to the created diffuse material.

	\fn createRefractiveMaterial(const DoubleVec3D& emittance)
	\brief Interactive creation of a RefractiveMaterial.
	\param emittance The emittance of the material.
	\return A pointer to the created refractive material.

	\fn createSpecularMaterial(const DoubleVec3D& emittance)
	\brief Interactive creation of a SpecularMaterial.
	\param emittance The emittance of the material.
	\return A pointer to the created specular material.

	\fn createMaterial()
	\brief Interactive creation of a Material.
	\details Gets the main parameters of a material, and calls createDiffuseMaterial(), createRefractiveMaterial() or createSpecularMaterial().
	\return A pointer to the created material.
	\sa createDiffuseMaterial(), createRefractiveMaterial(), createSpecularMaterial()

	\fn createSphere(Material* material)
	\brief Interactive creation of a Sphere.
	\param material The material of this sphere.
	\return A pointer to the created sphere.

	\fn createTriangle(Material* material)
	\brief Interactive creation of a Triangle.
	\param material The material of this triangle.
	\return A pointer to the created triangle.

	\fn createObject3D()
	\brief Interactive creation of an Object3D.
	\details Gets the main parameters of an object, and calls createSphere() or createTriangle().
	\return A pointer to the created object.
	\sa createSphere(), createTriangle()

	\fn to_json(json& j, const Material& mat)
	\brief Material conversion to json.
	\param j Json output.
	\param mat The material that will be converted.

	\fn importMaterialFromJson(const json& j)
	\brief Material conversion from json
	\param j Json input.
	\return A pointer to the material stored in the json.

	\fn to_json(json& j, const Object3D& obj)
	\brief Object3D conversion to json.
	\param j Json output.
	\param obj The object that will be converted.

	\fn importObject3DFromJson(const json& j)
	\brief Object3D conversion from json
	\param j Json input.
	\return A pointer to the object stored in the json.
*/

// Constants
constexpr unsigned int MAX_LENGTH_STRING_FROM_USER = 256;
const std::string PROMPT = "> ";
const std::string STAR_SPLITTER = std::string(26, '*');
const std::string DASH_SPLITTER = std::string(26, '-');
const std::string INVALID_COMMAND = "Invalid command.";

const std::string PICTURE_EXTENSION = "bmp";  // list of available extensions: http://cimg.eu/reference/group__cimg__files__io.html
const std::string FBX_EXTENSION = "fbx";
const std::string PICTURE_SAVE_EXTENSION_JSON = "ptpict";
const std::string OBJECTS_SAVE_EXTENSION = "ptobj";
const std::string PARAMETERS_SAVE_EXTENSION = "ptparam";

static std::uniform_real_distribution<double> unif(0, 1);
static std::default_random_engine re(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());


// Functions
void clearScreenPrintHeader();
void availableCommandsHeader();

std::string bool2string(bool b);
double getCurrentTimeSeconds();
double randomDouble();

std::string getStringFromUser(std::string question = "", std::string prompt = PROMPT);
char getLowerCaseCharFromUser(std::string question = "", std::string prompt = PROMPT);
int getIntFromUser(std::string question = "", std::string prompt = PROMPT);
unsigned int getUnsignedIntFromUser(std::string question = "", std::string prompt = PROMPT);
double getDoubleFromUser(std::string question = "", std::string prompt = PROMPT);
double getPositiveDoubleFromUser(std::string question = "", std::string prompt = PROMPT);
bool getBoolFromUser(std::string question = "", std::string prompt = PROMPT);
DoubleVec3D getXYZDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT);
DoubleVec3D getRGBDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT);

bool fileExists(std::string fileName);
std::string formatFileName(std::string fileName, std::string extension);

Material* createDiffuseMaterial(const DoubleVec3D& emittance);
Material* createRefractiveMaterial(const DoubleVec3D& emittance);
Material* createSpecularMaterial(const DoubleVec3D& emittance);
Material* createMaterial();

Object3D* createSphere(Material* material);
Object3D* createTriangle(Material* material);
Object3D* createObject3D();

void to_json(json& j, const Material& mat);
Material* importMaterialFromJson(const json& j);
void to_json(json& j, const Object3D& obj);
Object3D* importObject3DFromJson(const json& j);

#endif
