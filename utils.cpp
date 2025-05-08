#include "utils.h"
#include <iostream>
#include <limits>
#include <sys/stat.h> // For directory checking

std::string printNiceHeader(const std::string &headerContent)
{
    std::cout << "\n" + headerContent << std::endl;
    std::string result;
    for (size_t i = 0; i < headerContent.length(); i++)
    {
        result += "_";
    }
    return result;
}

bool validateString(const std::string &s)
{
    for (const char c : s)
    {
        if (!isalpha(c) && !isspace(c) && c != '-')
        {
            return false;
        }
    }
    return true;
}

bool validateInteger(int value)
{
    return !std::cin.fail();
}

bool validateDate(const std::string &date)
{
    std::regex date_pattern(R"(\d{2}/\d{2}/\d{4})");
    if (!std::regex_match(date, date_pattern))
    {
        return false;
    }

    int day, month, year;
    sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);

    if (month < 1 || month > 12 || day < 1 || day > 31)
    {
        return false;
    }

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        return false;
    }

    if (month == 2)
    {
        bool is_leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !is_leap_year))
        {
            return false;
        }
    }

    return true;
}

bool fileExists(const std::string &filename)
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void createDirectoryIfNotExists(const std::string &dirName)
{
    struct stat info;
    if (stat(dirName.c_str(), &info) != 0)
    {
        mkdir(dirName.c_str(), 0777); // Create directory with full permissions
    }
}