#ifndef INTERFACE
#define INTERFACE

#include <iomanip>

#include "InterfaceGestion.h"
#include "Scene.h"
#include "PerspectiveCamera.h"
#include "Object3DGroup.h"

/*!
	\file Interface.h
	\brief Defines some functions for the interface.

	\enum Page
	\brief Different current main pages possible.
	\details Could have been defined using a boolean, but it is not something that really needs to be optimised and an enumeration is, I think, more readable.

	\var smallestRenderTime4PictBackup
	\brief If the render time takes more time, the render will be backed up.

	\var backupFileName
	\brief The name of the file in which the backup will be made.

	\fn receiveAndExecuteGeneralCommands()
	\brief Receives and executes the general commands.
	\details Asks a command to the user. If it is general to both main pages (exit, for example), executes it, else, calls executeParametersCommands() or exercuteObjectsCommands().

	\fn executeParametersCommands(char command)
	\brief Executes a command specific to the parameters page.

	\fn executeObjectsCommands(char command)
	\brief Executes a command specific to the objects page.

	\fn displayCommands()
	\brief Prints the available command.
	\details The available commands change depending on the active page.

	\fn initInterface()
	\brief Starts the infinite loop of the interface.
*/

enum class Page {	
	ParametersPage,
	ObjectsPage
};


constexpr double smallestRenderTime4PictBackup = 180.0;  // Three minutes
const std::string backupFileName = formatFileName("backup", PICTURE_SAVE_EXTENSION_JSON);

static Scene scene;
static PerspectiveCamera& camera = scene.getCameraReference();
static std::vector<Object3DGroup>& objectGroups = scene.getObjectsGroupsReference();
static Page currentPage = Page::ParametersPage;
static bool commandWasInvalid = false;

// Main interface
void receiveAndExecuteGeneralCommands();
void executeParametersCommands(char command);
void executeObjectsCommands(char command);

void displayCommands();
void initInterface();

#endif
