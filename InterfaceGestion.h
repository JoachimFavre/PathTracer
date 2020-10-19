#ifndef DEF_INTERFACEGESTION
#define DEF_INTERFACEGESTION

#include <chrono>
#include <fstream>
#include <string>

#include "Material.h"
#include "DiffuseMaterial.h"
#include "SpecularMaterial.h"
#include "RefractiveMaterial.h"
#include "Object3D.h"
#include "Sphere.h"
#include "Triangle.h"
#include "DoubleVec3D.h"

// Constants
//! Maximum length for a string the user can give.
constexpr unsigned int MAX_LENGTH_STRING_FROM_USER = 256;
//! String that signal that the user can write a command.
const std::string PROMPT = "> ";
//! A line of stars.
const std::string STAR_SPLITTER(26, '*');
//! A line of dashs.
const std::string DASH_SPLITTER(26, '-');
//! String used when the command is invalid.
const std::string INVALID_COMMAND = "Invalid command.";

//! File extension for pictures.
const std::string PICTURE_EXTENSION = "bmp";  // list of available extensions: http://cimg.eu/reference/group__cimg__files__io.html
//! File extension for FBX files.
const std::string FBX_EXTENSION = "fbx";
//! Custom file extension to save pictures.
const std::string PICTURE_SAVE_EXTENSION_JSON = "ptpict";
//! Custom file extension to save objects groups.
const std::string OBJECTS_SAVE_EXTENSION = "ptobj";
//! Custom file extension to save parameters.
const std::string PARAMETERS_SAVE_EXTENSION = "ptparam";

// Functions
//! Clears the console and shows the header.
void clearScreenPrintHeader();
//! Prints a header before printing which commands are available.
void availableCommandsHeader();


//! Converts a boolean to string.
/*!
	\param b The boolean that will be converted.
	\return The boolean converted into a string.
*/
std::string bool2string(bool b);

//! Gives the number of seconds since 01/01/1970.
/*!
	\return The time since 01/01/1970 in seconds.
*/
double getCurrentTimeSeconds();


//! Gets a string from the user.
/*!
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The string the user gave.
*/
std::string getStringFromUser(std::string question = "", std::string prompt = PROMPT);

//! Gets a lowercase character from the user.
/*!
	Uses the getStringFromUser() method and takes the first character of this string.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The character the user gave.
	\sa getStringFromUser()
*/
char getLowerCaseCharFromUser(std::string question = "", std::string prompt = PROMPT);

//! Gets an integer from the user.
/*!
	Uses the getStringFromUser() method. Will continue to ask the question until the user gives a string that can be converted to an int.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The integer the user gave.
	\sa getStringFromUser()
*/
int getIntFromUser(std::string question = "", std::string prompt = PROMPT);

//! Gets a positive integer from the user.
/*!
	Uses the getIntFromUser() method. Will continue to ask the question until the user gives a positive integer.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The postive integer the user gave.
	\sa getIntFromUser()
*/
unsigned int getUnsignedIntFromUser(std::string question = "", std::string prompt = PROMPT);

//! Gets a number from the user.
/*!
	Uses the getStringFromUser() method. Will continue to ask the question until the user gives a string that can be converted to a double.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The double the user gave.
	\sa getStringFromUser()
*/
double getDoubleFromUser(std::string question = "", std::string prompt = PROMPT);

//! Gets a positive number from the user.
/*!
	Uses the getDoubleFromUser() method. Will continue to ask the question until the user gives a positive double.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The postive double the user gave.
	\sa getDoubleFromUser()
*/
double getPositiveDoubleFromUser(std::string question = "", std::string prompt = PROMPT);

//! Gets a boolean from the user.
/*!
	Uses the getLowerCaseCharFromUser() method. Will continue to ask the question until the user gives a 't' or 'f'.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The boolean the user gave.
	\sa getLowerCaseCharFromUser()
*/
bool getBoolFromUser(std::string question = "", std::string prompt = PROMPT);

//! Gets a vector from the user.
/*!
	Uses three times the getDoubleFromUser() method. Adds "x ", "y " or "z " before the prompt, to show the user which coordinates he or she is giving.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The vector the user gave.
	\sa getDoubleFromUser()
*/
DoubleVec3D getXYZDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT);

//! Gets a vector with only positive coordinates from the user.
/*!
	Uses three times the getPositiveDoubleFromUser() method. Adds "r ", "g " or "b " before the prompt, to show the user which coordinates he or she is giving.
	\param question The question that will be asked to the user.
	\param prompt The prompt that will be used to show the user that he or she can write something.
	\return The vector the user gave.
	\sa getPositiveDoubleFromUser()
*/
DoubleVec3D getRGBDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT);

//! Verifies if the file exists.
/*!
	\param fileName The path to the file.
	\return True if the file exists, false else.
*/
bool fileExists(std::string fileName);

//! Formats the name of the file the user gave and the extension we want.
/*!
	For example, it will format "test.txt" into "test.txt" and "test" into "test.txt".
	\param fileName The path to the file we want to format.
	\param extension The file extension with which we want to format the file.
	\return The formated file name.
*/
std::string formatFileName(std::string fileName, std::string extension);


//! Interactive creation of a DiffuseMaterial.
/*!
	\param emittance The emittance of the material.
	\return A pointer to the created diffuse material.
*/
Material* createDiffuseMaterial(const DoubleVec3D& emittance);

//! Interactive creation of a RefractiveMaterial.
/*!
	\param emittance The emittance of the material.
	\return A pointer to the created refractive material.
*/
Material* createRefractiveMaterial(const DoubleVec3D& emittance);

//! Interactive creation of a SpecularMaterial.
/*!
	\param emittance The emittance of the material.
	\return A pointer to the created specular material.
*/
Material* createSpecularMaterial(const DoubleVec3D& emittance);

//! Interactive creation of a Material.
/*!
	Gets the main parameters of a material, and calls createDiffuseMaterial(), createRefractiveMaterial() or createSpecularMaterial().
	\return A pointer to the created material.
	\sa createDiffuseMaterial(), createRefractiveMaterial(), createSpecularMaterial()
*/
Material* createMaterial();


//! Interactive creation of a Sphere.
/*!
	\param material The material of this sphere.
	\return A pointer to the created sphere.
*/
Object3D* createSphere(Material* material);

//! Interactive creation of a Triangle.
/*!
	\param material The material of this triangle.
	\return A pointer to the created triangle.
*/
Object3D* createTriangle(Material* material);

//! Interactive creation of an Object3D.
/*!
	Gets the main parameters of an object, and calls createSphere() or createTriangle().
	\return A pointer to the created object.
	\sa createSphere(), createTriangle()
*/
Object3D* createObject3D();

//! Material conversion to json.
/*!
	\param j Json output.
	\param mat The material that will be converted.
*/
void to_json(json& j, const Material& mat);

//! Material conversion from json
/*!
	\param j Json input.
	\return A pointer to the material stored in the json.
*/
Material* importMaterialFromJson(const json& j);

//! Object3D conversion to json.
/*!
	\param j Json output.
	\param obj The object that will be converted.
*/
void to_json(json& j, const Object3D& obj);

//! Object3D conversion from json
/*!
	\param j Json input.
	\return A pointer to the object stored in the json.
*/
Object3D* importObject3DFromJson(const json& j);

#endif
