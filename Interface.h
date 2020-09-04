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

// Main interface
void clearScreenPrintHeader();
void receiveAndExecuteGeneralCommands();
void executeParametersCommands(char command);
void executeObjectsCommands(char command);
void displayCommands();
void initInterface();

#endif
