#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <regex>

// printing a nice header
std::string printNiceHeader(const std::string &headerContent);

// Input validation functions
bool validateString(const std::string &s);
bool validateInteger(int value);
bool validateDate(const std::string &date);

// File utility functions
bool fileExists(const std::string &filename);
void createDirectoryIfNotExists(const std::string &dirName);

#endif