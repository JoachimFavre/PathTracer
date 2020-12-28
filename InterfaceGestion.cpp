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

void showCMDCursor(bool show) {
    // From: https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt (see the documentation or the report for complete bibliography)
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = show;
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Conversion into string
std::string bool2string(bool b) {
    return (b ? "True" : "False");
}

// Time
double getCurrentTimeSeconds() {
    return (double)std::chrono::system_clock::now().time_since_epoch().count() / std::chrono::system_clock::period::den;
}

// Random
double randomDouble() {
    return unif(re);
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
