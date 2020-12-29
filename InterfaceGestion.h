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
    \brief File extension for FBX files.

    \var const std::string PICTURE_SAVE_EXTENSION_JSON
    \brief Custom file extension to save pictures.

    \var const std::string OBJECTS_SAVE_EXTENSION
    \brief Custom file extension to save objects groups.

    \var const std::string PARAMETERS_SAVE_EXTENSION
    \brief Custom file extension to save parameters.

    \var const std::string POSITIVE_DOUBLE_INFO
    \brief Information that is printed when asking a postive double to the user.

    \var const std::string POSITIVE_INT_INFO
    \brief Information that is printed when asking a postive integer to the user.

    \var const std::string BOOL_INFO
    \brief Information that is printed when asking a boolean to the user.

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

const std::string POSITIVE_DOUBLE_INFO = "(positive number)";
const std::string POSITIVE_INT_INFO = "(positive integer)";
const std::string BOOL_INFO = "(True=T=true=t / False=F=false=f)";

static std::uniform_real_distribution<double> unif(0, 1);
static std::default_random_engine re(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());


// Functions
void clearScreenPrintHeader();
void availableCommandsHeader();
void showCMDCursor(bool show);

std::string bool2string(bool b);
double getCurrentTimeSeconds();
double randomDouble();

std::string getStringFromUser(std::string question = "", std::string prompt = PROMPT);
char getLowerCaseCharFromUser(std::string question = "", std::string prompt = PROMPT);
int getIntFromUser(std::string question = "", std::string prompt = PROMPT);
unsigned int getUnsignedIntFromUser(std::string question = "", std::string prompt = PROMPT);
double getDoubleFromUser(std::string question = "", std::string prompt = PROMPT);
double getPositiveDoubleFromUser(std::string question = "", std::string prompt = PROMPT);
bool getBoolFromUser(std::string question = "", std::string prompt = PROMPT);

bool fileExists(std::string fileName);
std::string formatFileName(std::string fileName, std::string extension);

#endif
