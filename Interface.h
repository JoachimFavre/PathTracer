#ifndef INTERFACE
#define INTERFACE

#include "Scene.h"

/*!
    \file Interface.h
    \brief Defines some functions for the interface.

    \fn void receiveAndExecuteGeneralCommands()
    \brief Receives and executes the general commands.
    \details Asks a command to the user. If it is general to both main pages (exit, for example), executes it, else, calls executeParametersCommands() or executeObjectsCommands().

    \fn void executeParametersCommands(char command)
    \brief Executes a command specific to the parameters page.

    \fn void executeObjectsCommands(char command)
    \brief Executes a command specific to the objects page.

    \fn void displayCommands()
    \brief Prints the available command.
    \details The available commands change depending on the active page.

    \fn void printAll()
    \brief Prints the whole page.
    \details Clears the page, prints the header, information and the available commands.
    \sa clearScreenPrintHeader(), Scene::displayParametersPage(), Scene::displayObjectsPage(), displayCommands()

    \fn void initInterface()
    \brief Starts the infinite loop of the interface.
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
