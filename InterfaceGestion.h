#ifndef DEF_INTERFACEGESTION
#define DEF_INTERFACEGESTION

#include <chrono>
#include <fstream>
#include <random>
#include <iostream>

#define _USE_MATH_DEFINES  // to be able to use M_PI from math.h
#include <math.h>

// Needs to be included before fbxsdk, else creates conflict.
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include <fbxsdk.h>

#define NOMINMAX  // So that window.h does not interfere with std::min and std::max
#include <windows.h>  // To hide CMD cursor

/*!
    \file InterfaceGestion.h
    \brief Defines functions that are used when drawing the interface.

    \var constexpr unsigned int MAX_LENGTH_STRING_FROM_USER
    \brief Maximum length for a string the user can give.

    \var const std::string PROMPT
    \brief String that signal that the user can write a command.

    \var const std::string STAR_SPLITTER
    \brief A line of stars.

    \var const std::string DASH_SPLITTER
    \brief A line of dashs.

    \var const std::string INVALID_COMMAND
    \brief String used when the command is invalid.

    \var const std::string PICTURE_EXTENSION
    \brief File extension for pictures.

    \var const std::string FBX_EXTENSION
    \brief File extension for fbx files.

    \var const std::string PICTURE_SAVE_EXTENSION_JSON
    \brief Custom file extension to save pictures.

    \var const std::string OBJECTS_SAVE_EXTENSION
    \brief Custom file extension to save object groups.

    \var const std::string PARAMETERS_SAVE_EXTENSION
    \brief Custom file extension to save parameters.

    \fn void clearScreenPrintHeader()
    \brief Clears the console and shows the header.

    \fn void availableCommandsHeader()
    \brief Prints a header before printing which commands are available.

    \fn void showCMDCursor(bool show)
    \brief Shows or hide the cursor in the interface.
    \details Used code from Captain Obvlious. Remove blinking underscore on console / cmd prompt. [Accessed 28 December 2020]. Stackoverflow. Aug. 3, 2013. URL: https://stackoverflow.com/a/18028927/12637970.
    \param show Whether the cursor will shown or hidden.

    \fn std::string bool2string(bool b)
    \brief Converts a boolean to string.
    \param b The boolean that will be converted.
    \return The boolean converted into a string.

    \fn double getCurrentTimeSeconds()
    \brief Gives the number of seconds since 01/01/1970.
    \return The time since 01/01/1970 in seconds.

    \fn double randomDouble()
    \brief Computes a random double between 0 and 1
    \return A random double between 0 and 1 generated following a uniform distrbution.

    \fn bool fileExists(std::string fileName)
    \brief Verifies if the file exists.
    \param fileName The path to the file.
    \return True if the file exists, false else.

    \fn std::string formatFileName(std::string fileName, std::string extension)
    \brief Formats the name of the file the user gave and the extension we want.
    \details For example, it will format "test.txt" into "test.txt" and "test" into "test.txt".
    \param fileName The path to the file we want to format.
    \param extension The file extension with which we want to format the file.
    \return The formated file name.
*/

// Constants
constexpr unsigned int MAX_LENGTH_STRING_FROM_USER = 256;
const std::string PROMPT = "> ";
const std::string STAR_SPLITTER = std::string(26, '*');
const std::string DASH_SPLITTER = std::string(26, '-');
const std::string INVALID_COMMAND = "Invalid command.";

const std::string PICTURE_EXTENSION = "bmp";  // list of available extensions: http://cimg.eu/reference/group__cimg__files__io.html
const std::string FBX_EXTENSION = "fbx";
const std::string PICTURE_SAVE_EXTENSION_JSON = "ptpict";
const std::string OBJECTS_SAVE_EXTENSION = "ptobj";
const std::string PARAMETERS_SAVE_EXTENSION = "ptparam";

static std::uniform_real_distribution<double> unif(0, 1);
static std::default_random_engine re(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());


// Functions
void clearScreenPrintHeader();
void availableCommandsHeader();
void showCMDCursor(bool show);

std::string bool2string(bool b);
double getCurrentTimeSeconds();
double randomDouble();

bool fileExists(std::string fileName);
std::string formatFileName(std::string fileName, std::string extension);

#endif
