#ifndef INTERFACE
#define INTERFACE

#include <iomanip>

#include "InterfaceGestion.h"
#include "Scene.h"
#include "PerspectiveCamera.h"
#include "Object3DGroup.h"

//! Different current main pages possible.
/*!
	Could have been defined using a boolean, but it is not something that really needs to be optimised and an enumeration is, I think, more readable.
*/
enum class Page {	
	ParametersPage,
	ObjectsPage
};

//! If the render time takes more time, the render will be backed up. 
constexpr double smallestRenderTime4PictBackup = 180.0;  // Three minutes
//! The name of the file in which the backup will be made.
const std::string backupFileName = formatFileName("backup", PICTURE_SAVE_EXTENSION_JSON);

static Scene scene;
static PerspectiveCamera& camera = scene.getCameraReference();
static std::vector<Object3DGroup>& objectGroups = scene.getObjectsGroupsReference();
static Page currentPage = Page::ParametersPage;
static bool commandWasInvalid = false;

// Main interface

//! Receives and executes the general commands.
/*!
	Asks a command to the user. If it is general to both main pages (exit, for example), executes it, else, calls executeParametersCommands() or exercuteObjectsCommands().
*/
void receiveAndExecuteGeneralCommands();

//! Executes a command specific to the parameters page.
void executeParametersCommands(char command);

//! Executes a command specific to the objects page.
void executeObjectsCommands(char command);

//! Prints the available command.
/*!
	The available commands change depending which page is active.
*/
void displayCommands();

//! Starts the infinite loop of the interface.
void initInterface();

#endif
