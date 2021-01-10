#ifndef INTERFACE
#define INTERFACE

#include "Scene.h"

/*!
    \file Interface.h
    \brief Defines some functions for the interface.

    \var static Scene scene
    \brief The scene that will be used by the interface.

    \var static PerspectiveCamera& camera
    \brief A reference to the camera from the scene.
    \sa Scene::getCameraReference()

    \var static std::vector<Object3DGroup>& objectGroups
    \brief A reference to the vector of object groups from the scene.
    \sa Scene::getObjectGroupsReference()

    \var static bool isParametersPage
    \brief Defines whether the current page is the parameters page.
    \details If the current page is not the parameters page, then it is the objects page.

    \var static bool commandWasInvalid
    \brief Defines whether the last command that was used was invalid.
    \details It is used to display INVALID_COMMAND when reprinting the page.
    \sa INVALID_COMMAND

    \fn void receiveAndExecuteGeneralCommands()
    \brief Receives and executes a general command.
    \details Asks a command to the user. If it is general to both main pages (exit, for example), executes it. Else, it calls executeParametersCommands() or executeObjectsCommands().
    \sa executeObjectsCommands(), executeObjectsCommands(), displayCommands(), initInterface()

    \fn void executeParametersCommands(char command)
    \brief Executes a command specific to the parameters page.
    \sa receiveAndExecuteGeneralCommands(), executeObjectsCommands(), displayCommands()

    \fn void executeObjectsCommands(char command)
    \brief Executes a command specific to the objects page.
    \sa receiveAndExecuteGeneralCommands(), executeParametersCommands(), displayCommands()

    \fn void displayCommands()
    \brief Prints the available commands.
    \details The available commands change depending on the active page.
    \sa printAll(), receiveAndExecuteGeneralCommands(), executeParametersCommands(), executeObjectsCommands()

    \fn void printAll()
    \brief Prints the whole page.
    \details Clears the page, prints the header, information and the available commands.
    \sa clearScreenPrintHeader(), Scene::displayParametersPage(), Scene::displayObjectsPage(), displayCommands(), initInterface()

    \fn void initInterface()
    \brief Starts the infinite loop of the interface.
    \details Fills the scene with a default one. Then, it calls printAll() and receiveAndExecuteGeneralCommands() indefinitely.
    \sa Scene::defaultScene(), printAll(), receiveAndExecuteGeneralCommands()
*/

static Scene scene;
static PerspectiveCamera& camera = scene.getCameraReference();
static std::vector<Object3DGroup>& objectGroups = scene.getObjectGroupsReference();
static bool isParametersPage = true;
static bool commandWasInvalid = false;

// Main interface
void receiveAndExecuteGeneralCommands();
void executeParametersCommands(char command);
void executeObjectsCommands(char command);

void displayCommands();
void printAll();
void initInterface();

#endif
