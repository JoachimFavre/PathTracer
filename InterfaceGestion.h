#ifndef DEF_INTERFACEGESTION
#define DEF_INTERFACEGESTION

#include <fstream>
#include <string>

#include "DoubleVec3D.h"

// Constants
constexpr unsigned int MAX_LENGTH_STRING_FROM_USER = 256;
const std::string PROMPT = "> ";
const std::string STAR_SPLITTER(26, '*');
const std::string DASH_SPLITTER(26, '-');
const std::string INVALID_COMMAND = "Invalid command.";

const std::string PICTURE_EXTENSION = "bmp";  // list of available extensions: http://cimg.eu/reference/group__cimg__files__io.html
const std::string FBX_EXTENSION = "fbx";
const std::string OBJECTS_SAVE_EXTENSION = "ptobj";
const std::string PARAMETERS_SAVE_EXTENSION = "ptparam";

// Functions
void clearScreenPrintHeader();
void availableCommandsHeader();

std::string bool2string(bool b);

std::string getStringFromUser(std::string question = "", std::string prompt = PROMPT);
char getLowerCaseCharFromUser(std::string question = "", std::string prompt = PROMPT);
int getIntFromUser(std::string question = "", std::string prompt = PROMPT);
unsigned int getUnsignedIntFromUser(std::string question = "", std::string prompt = PROMPT);
double getDoubleFromUser(std::string question = "", std::string prompt = PROMPT);
double getPositiveDoubleFromUser(std::string question = "", std::string prompt = PROMPT);
bool getBoolFromUser(std::string question = "", std::string prompt = PROMPT);
DoubleVec3D getXYZDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT);
DoubleVec3D getRGBDoubleVec3DFromUser(std::string question = "", std::string prompt = PROMPT);

bool fileExists(std::string fileName);
std::string formatFileName(std::string fileName, std::string extension);

#endif
