#ifndef DEF_INTERFACE
#define DEF_INTERFACE

#include <iostream>
#include <string>


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
	std::cout << question << std::endl << PROMPT;
	std::string userText;
	std::cin >> userText;
	return userText;
}


static char getCharFromUser(std::string question = "") {
	return (getStringFromUser(question))[0];
}


static unsigned int getUnsignedIntFromUser(std::string question = "") {
	while (true) {
		std::string userText = getStringFromUser(question);

		try {
			int value = std::stoi(userText);

			if (value >= 0)
				return value;
			std::cout << "This is not a positive number!";

		} catch (const std::invalid_argument& exception) {
			std::cout << "This is not a number!";
		} catch (const std::out_of_range& exception) {
			std::cout << "This number is too big! (What were you expecting?)";
		}

		std::cout << std::endl << std::endl;
	}
}


#endif