#ifndef DEF_INTERFACECREATION
#define DEF_INTERFACECREATION

#include "InterfaceGestion.h"

#include "DiffuseMaterial.h"
#include "RefractiveMaterial.h"
#include "SpecularMaterial.h"

#include "Triangle.h"
#include "Sphere.h"

/*!
    \file InterfaceCreation.h
    \brief Defines functions that are used to interactively create 3D objects and materials.

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