#ifndef INTERFACE
#define INTERFACE

#include <iomanip>

#include "InterfaceGestion.h"
#include "Scene.h"
#include "PerspectiveCamera.h"
#include "Object3DGroup.h"

enum class Page {
	ParametersPage,
	ObjectsPage
};

static Scene scene;
static PerspectiveCamera& camera = scene.getCameraReference();
static std::vector<Object3DGroup>& objectGroups = scene.getObjectsGroupsReference();
static Page currentPage = Page::ParametersPage;
static bool commandWasInvalid = false;

// Material creation
Material* createDiffuseMaterial(const DoubleVec3D& emittance);
Material* createRefractiveMaterial(const DoubleVec3D& emittance);
Material* createSpecularMaterial(const DoubleVec3D& emittance);
Material* createMaterial();

// Object creation
Object3D* createSphere(Material* material);
Object3D* createTriangle(Material* material);
Object3D* createObject3D();

// From/to json
void to_json(json& j, const Material& mat);
Material* importMaterialFromJson(const json& j);
void to_json(json& j, const Object3D& obj);
Object3D* importObject3DFromJson(const json& j);

// Main interface
void clearScreenPrintHeader();
void receiveAndExecuteGeneralCommands();
void executeParametersCommands(char command);
void executeObjectsCommands(char command);
void displayCommands();
void initInterface();

#endif
