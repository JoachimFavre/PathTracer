#ifndef DEF_INTERFACECREATION
#define DEF_INTERFACECREATION

#include "DiffuseMaterial.h"
#include "RefractiveMaterial.h"
#include "SpecularMaterial.h"

#include "Triangle.h"
#include "Sphere.h"

/*!
    \file InterfaceCreation.h
    \brief Defines functions that are used to ask for values to the user, and to interactively create 3D objects and materials.

    \var const std::string POSITIVE_DOUBLE_INFO
    \brief Information that is printed when asking a postive double to the user.

    \var const std::string POSITIVE_INT_INFO
    \brief Information that is printed when asking a postive integer to the user.

    \var const std::string BOOL_INFO
    \brief Information that is printed when asking a boolean to the user.

    \fn std::string getStringFromUser(std::string question = "", std::string prompt = PROMPT)
    \brief Gets a string from the user.
    \param question The question that will be asked to the user.
    \param prompt The prompt that will be used to show the user that he or she can write something.
    \return The string the user gave.

    \fn char getLowerCaseCharFromUser(std::string question = "", std::string prompt = PROMPT)
    \brief Gets a lowercase character from the user.
    \details Uses the getStringFromUser() method and takes the first character of this string.
    \param question The question that will be asked to the user.
    \param prompt The prompt that will be used to show the user that he or she can write something.
    \return The character the user gave.
    \sa getStringFromUser()

    \fn int getIntFromUser(std::string question = "", std::string prompt = PROMPT)
    \brief Gets an integer from the user.
    \details Uses the getStringFromUser() method. Will continue to ask the question until the user gives a string that can be converted to an int.
    \param question The question that will be asked to the user.
    \param prompt The prompt that will be used to show the user that he or she can write something.
    \return The integer the user gave.
    \sa getStringFromUser()

    \fn unsigned int getUnsignedIntFromUser(std::string question = "", std::string prompt = PROMPT)
    \brief Gets a positive integer from the user.
    \details Uses the getIntFromUser() method. Will continue to ask the question until the user gives a positive integer.
    \param question The question that will be asked to the user.
    \param prompt The prompt that will be used to show the user that he or she can write something.
    \return The postive integer the user gave.
    \sa getIntFromUser()

    \fn double getDoubleFromUser(std::string question = "", std::string prompt = PROMPT)
    \brief Gets a number from the user.
    \details Uses the getStringFromUser() method. Will continue to ask the question until the user gives a string that can be converted to a double.
    \param question The question that will be asked to the user.
    \param prompt The prompt that will be used to show the user that he or she can write something.
    \return The double the user gave.
    \sa getStringFromUser()

    \fn double getPositiveDoubleFromUser(std::string question = "", std::string prompt = PROMPT)
    \brief Gets a positive number from the user.
    \details Uses the getDoubleFromUser() method. Will continue to ask the question until the user gives a positive double.
    \param question The question that will be asked to the user.
    \param prompt The prompt that will be used to show the user that he or she can write something.
    \return The postive double the user gave.
    \sa getDoubleFromUser()

    \fn bool getBoolFromUser(std::string question = "", std::string prompt = PROMPT)
    \brief Gets a boolean from the user.
    \details Uses the getLowerCaseCharFromUser() method. Will continue to ask the question until the user gives a 't' or 'f'.
    \param question The question that will be asked to the user.
    \param prompt The prompt that will be used to show the user that he or she can write something.
    \return The boolean the user gave.
    \sa getLowerCaseCharFromUser()

    \fn DoubleVec3D getXYZDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT)
    \brief Gets a vector from the user.
    \details Uses three times the getDoubleFromUser() method. Adds "x ", "y " or "z " before the prompt, to show the user which coordinates he or she is giving.
    \param question The question that will be asked to the user.
    \param prompt The prompt that will be used to show the user that he or she can write something.
    \return The vector the user gave.
    \sa getDoubleFromUser()

    \fn DoubleVec3D getRGBDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT)
    \brief Gets a vector with only positive coordinates from the user.
    \details Uses three times the getPositiveDoubleFromUser() method. Adds "r ", "g " or "b " before the prompt, to show the user which coordinates he or she is giving.
    \param question The question that will be asked to the user.
    \param prompt The prompt that will be used to show the user that he or she can write something.
    \return The vector the user gave.
    \sa getPositiveDoubleFromUser()

    \fn Material* createDiffuseMaterial(const DoubleVec3D& emittance)
    \brief Interactive creation of a DiffuseMaterial.
    \param emittance The emittance of the material.
    \return A pointer to the created diffuse material.

    \fn Material* createRefractiveMaterial(const DoubleVec3D& emittance)
    \brief Interactive creation of a RefractiveMaterial.
    \param emittance The emittance of the material.
    \return A pointer to the created refractive material.

    \fn Material* createSpecularMaterial(const DoubleVec3D& emittance)
    \brief Interactive creation of a SpecularMaterial.
    \param emittance The emittance of the material.
    \return A pointer to the created specular material.

    \fn Material* createMaterial()
    \brief Interactive creation of a Material.
    \details Gets the main parameters of a material, and calls createDiffuseMaterial(), createRefractiveMaterial() or createSpecularMaterial().
    \return A pointer to the created material.
    \sa createDiffuseMaterial(), createRefractiveMaterial(), createSpecularMaterial()

    \fn Object3D* createSphere(Material* material)
    \brief Interactive creation of a Sphere.
    \param material The material of this sphere.
    \return A pointer to the created sphere.

    \fn Object3D* createTriangle(Material* material)
    \brief Interactive creation of a Triangle.
    \param material The material of this triangle.
    \return A pointer to the created triangle.

    \fn Object3D* createObject3D()
    \brief Interactive creation of an Object3D.
    \details Gets the main parameters of an object, and calls createSphere() or createTriangle().
    \return A pointer to the created object.
    \sa createSphere(), createTriangle()

    \fn void to_json(json& j, const Material& mat)
    \brief Material conversion to json.
    \param j Json output.
    \param mat The material that will be converted.

    \fn Material* importMaterialFromJson(const json& j)
    \brief Material conversion from json
    \param j Json input.
    \return A pointer to the material stored in the json.

    \fn void to_json(json& j, const Object3D& obj)
    \brief Object3D conversion to json.
    \param j Json output.
    \param obj The object that will be converted.

    \fn Object3D* importObject3DFromJson(const json& j)
    \brief Object3D conversion from json
    \param j Json input.
    \return A pointer to the object stored in the json.
*/

const std::string POSITIVE_DOUBLE_INFO = "(positive number)";
const std::string POSITIVE_INT_INFO = "(positive integer)";
const std::string BOOL_INFO = "(True=T=true=t / False=F=false=f)";

std::string getStringFromUser(std::string question = "", std::string prompt = PROMPT);
char getLowerCaseCharFromUser(std::string question = "", std::string prompt = PROMPT);
int getIntFromUser(std::string question = "", std::string prompt = PROMPT);
unsigned int getUnsignedIntFromUser(std::string question = "", std::string prompt = PROMPT);
double getDoubleFromUser(std::string question = "", std::string prompt = PROMPT);
double getPositiveDoubleFromUser(std::string question = "", std::string prompt = PROMPT);
bool getBoolFromUser(std::string question = "", std::string prompt = PROMPT);
DoubleVec3D getXYZDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT);
DoubleVec3D getRGBDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT);

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