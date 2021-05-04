#include "print.hpp"
#include <iostream>

const std::string
    WHITE = "\033[0;37m",
    RED = "\033[0;31m",
    GREEN = "\033[0;32m",
    YELLOW = "\033[0;33m",
    GREY = "\033[0;38m";

void printWarning(const std::string message)
{
    std::cout << YELLOW << message << WHITE << std::endl;
}

void printWarning(const std::string message1, const std::string message2)
{
    std::cout << YELLOW << message1 << ' ' << message2 << WHITE << std::endl;
}

void printWarning(const std::string message1, const std::string message2, const std::string message3)
{
    std::cout << YELLOW << message1 << ' ' << message2 << ' ' << message3 << WHITE << std::endl;
}

void printTrace(const std::string message)
{
    std::cout << GREY << message << WHITE << std::endl;
}

void printTrace(const std::string message1, const std::string message2)
{
    std::cout << GREY << message1 << ' ' << message2 << WHITE << std::endl;
}

void printTrace(const std::string message1, const std::string message2, const std::string message3)
{
    std::cout << GREY << message1 << ' ' << message2 << ' ' << message3 << WHITE << std::endl;
}

void printError(const std::string message)
{
    std::cout << RED << message << WHITE << std::endl;
}

void printError(const std::string message1, const std::string message2)
{
    std::cout << RED << message1 << ' ' << message2 << WHITE << std::endl;
}

void printError(const std::string message1, const std::string message2, const std::string message3)
{
    std::cout << RED << message1 << ' ' << message2 << ' ' << message3 << WHITE << std::endl;
}

void printDebug(const std::string message)
{
    std::cout << message << std::endl;
}

void printDebug(const std::string message1, const std::string message2)
{
    std::cout << message1 << ' ' << message2 << std::endl;
}

void printDebug(const std::string message1, const std::string message2, const std::string message3)
{
    std::cout << message1 << ' ' << message2 << ' ' << message3 << std::endl;
}