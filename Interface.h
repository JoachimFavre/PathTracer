#ifndef DEF_INTERFACE
#define DEF_INTERFACE

#include <iostream>
#include <string>

constexpr unsigned int maxLengthStringFromUser = 256;
const std::string PROMPT = "> ";
const std::string starSplitter(26, '*');
const std::string dashSplitter(26, '-');
const std::string invalidCommand = "Invalid command.";

// Common parts in interface
static void clearScreenPrintHeader() {
	std::system("cls");

	std::cout << "Joachim Favre's TM" << std::endl;
	std::cout << "Bidirectional path tracer" << std::endl;
	std::cout << starSplitter << std::endl;
	std::cout << std::endl;
}


static void availableCommandsHeader() {
	std::cout << std::endl;
	std::cout << starSplitter << std::endl;
	std::cout << std::endl;
	std::cout << "You can use the following commands:" << std::endl;
}


// Conversion into string
static std::string bool2string(bool b) {
	return (b ? "True" : "False");
}


// Get from user
static std::string getStringFromUser(std::string question = "") {
	char userText[maxLengthStringFromUser];
	while (true) {
		std::cout << question << std::endl << PROMPT;
		std::cin.getline(userText, maxLengthStringFromUser);
		if (std::cin.fail()) {
			std::cout << "This string is too long." << std::endl << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			return userText;
	}
}


static char getCharFromUser(std::string question = "") {
	return (getStringFromUser(question))[0];
}


// Too many repetitions, I have to correct that
static int getIntFromUser(std::string question = "") {
	while (true) {
		std::string userText = getStringFromUser(question);

		try {
			return std::stoi(userText);
		} catch (const std::invalid_argument& exception) {
			std::cout << "This is not a number!";
		} catch (const std::out_of_range& exception) {
			std::cout << "This number is too big! (What were you expecting?)";
		}

		std::cout << std::endl << std::endl;
	}
}


static unsigned int getUnsignedIntFromUser(std::string question = "") {
	while (true) {
		int value = getIntFromUser(question);
		if (value >= 0)
			return value;
		std::cout << "This is not a positive number!" << std::endl << std::endl;
	}
}

static double getPositiveDoubleFromUser(std::string question = "") {
	while (true) {
		std::string userText = getStringFromUser(question);

		try {
			double value = std::stod(userText);

			if (value >= 0)
				return value;
			std::cout << "This is not a positive number!";

		} catch (const std::invalid_argument& exception) {
			std::cout << "This is not a number!";
		} catch (const std::out_of_range& exception) {
			std::cout << "This number is either too big or with too many decimals.";
		}

		std::cout << std::endl << std::endl;
	}
}

static bool getBoolFromUser(std::string question = "") {
	while (true) {
		char userText = getCharFromUser(question);

		if (userText == 'T' || userText == 't')
			return true;
		else if (userText == 'F' || userText == 'f')
			return false;
		else
			std::cout << "This is not a boolean!" << std::endl << std::endl;

	}
}

#endif
