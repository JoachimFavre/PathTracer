#include "InterfaceGestion.h"

// Common parts in interface
void clearScreenPrintHeader() {
    std::system("cls");

    std::cout << "Joachim Favre's Maturity Work" << std::endl;
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
    // From: https://stackoverflow.com/a/18028927/12637970 (see the documentation or the report for complete bibliography)
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


