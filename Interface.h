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

constexpr double smallestRenderTime4PictBackup = 180.0;  // 3 minutes
const std::string backupFileName = formatFileName("backup", PICTURE_SAVE_EXTENSION_JSON);

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
