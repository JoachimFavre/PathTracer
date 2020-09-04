#include "InterfaceGestion.h"

// Common parts in interface
void clearScreenPrintHeader() {
	std::system("cls");

	std::cout << "Joachim Favre's TM" << std::endl;
	std::cout << "Path Tracer" << std::endl;
	std::cout << STAR_SPLITTER << std::endl;
	std::cout << std::endl;
}

void availableCommandsHeader() {
	std::cout << std::endl;
	std::cout << STAR_SPLITTER << std::endl;
	std::cout << std::endl;
	std::cout << "You can use the following commands:" << std::endl;
}


// Conversion into string
std::string bool2string(bool b) {
	return (b ? "True" : "False");
}


// Get from user
std::string getStringFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
	char userText[MAX_LENGTH_STRING_FROM_USER];
	while (true) {
		if (question != "")
			std::cout << question << std::endl;
		std::cout << prompt;
		std::cin.getline(userText, MAX_LENGTH_STRING_FROM_USER);
		if (std::cin.fail()) {
			std::cout << "This string is too long." << std::endl << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			return userText;
	}
}

char getLowerCaseCharFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
	return std::tolower((getStringFromUser(question, prompt))[0]);
}

// Too many repetitions, I have to correct that
int getIntFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
	while (true) {
		std::string userText = getStringFromUser(question, prompt);

		try {
			return std::stoi(userText);
		}
		catch (const std::invalid_argument& exception) {
			std::cout << "This is not a number!";
		}
		catch (const std::out_of_range& exception) {
			std::cout << "This number is too big! (What were you expecting?)";
		}

		std::cout << std::endl << std::endl;
	}
}

unsigned int getUnsignedIntFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
	while (true) {
		int value = getIntFromUser(question, prompt);
		if (value >= 0)
			return value;
		std::cout << "This is not a positive number!" << std::endl << std::endl;
	}
}

double getDoubleFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
	while (true) {
		std::string userText = getStringFromUser(question, prompt);

		try {
			return std::stod(userText);
		}
		catch (const std::invalid_argument& exception) {
			std::cout << "This is not a number!";
		}
		catch (const std::out_of_range& exception) {
			std::cout << "This number is either too big or with too many decimals.";
		}

		std::cout << std::endl << std::endl;
	}
}

double getPositiveDoubleFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
	while (true) {
		double value = getDoubleFromUser(question, prompt);
		if (value >= 0)
			return value;
		std::cout << "This is not a positive number!" << std::endl << std::endl;
	}
}

bool getBoolFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
	while (true) {
		char userText = getLowerCaseCharFromUser(question, prompt);

		if (userText == 't')
			return true;
		else if (userText == 'f')
			return false;
		else
			std::cout << "This is not a boolean!" << std::endl << std::endl;

	}
}

DoubleVec3D getXYZDoubleVec3DFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
	// Use array?
	double x = getDoubleFromUser(question, "x " + prompt);
	double y = getDoubleFromUser("", "y " + prompt);
	double z = getDoubleFromUser("", "z " + prompt);

	return DoubleVec3D(x, y, z);
}

DoubleVec3D getRGBDoubleVec3DFromUser(std::string question /*= ""*/, std::string prompt /*= PROMPT*/) {
	// Use array?
	double x = getPositiveDoubleFromUser(question, "r " + prompt);
	double y = getPositiveDoubleFromUser("", "g " + prompt);
	double z = getPositiveDoubleFromUser("", "b " + prompt);

	return DoubleVec3D(x, y, z);
}


// File manipulation
bool fileExists(std::string fileName) {
	std::ifstream f(fileName.c_str());
	return f.good();
}

std::string formatFileName(std::string fileName, std::string extension) {
	if (extension[0] != '.')
		extension = "." + extension;

	if (fileName.size() < extension.size())
		return fileName + extension;

	int extensionBeginningInFileName = fileName.size() - extension.size();

	for (int i = 0; i < extension.size(); i++) {
		if (!(std::tolower(fileName[extensionBeginningInFileName + i]) == std::tolower(extension[i]))) {
			return fileName + extension;
		}
	}

	return fileName;
}
