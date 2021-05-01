#include <iostream>
#include "logger.hpp"
#include "ccolors.hpp"

Logger::Logger()
{
    _level = 1; 
}

Logger::Logger(const std::string status)
{
    if (status == "error")
    {
        _level = 0;
    }
    else if (status == "warning")
    {
        _level = 1;
    }
    else if (status == "debug")
    {
        _level = 2;
    }
    else if (status == "trace")
    {
        _level = 3;
    }
    else
    {
        warning("Ошибка определения приоритета сообщений! Будет использован приоритет по-умолчанию (warning)");
        _level = 1;
    }
}

void Logger::error(const std::string message)
{
    std::cout << ccolors::RED << message << ccolors::WHITE << std::endl;
}

void Logger::warning(const std::string message)
{
    std::cout << ccolors::YELLOW << message << ccolors::WHITE << std::endl;
}

void Logger::debug(const std::string message)
{
    std::cout << message << std::endl;
}

void Logger::trace(const std::string message)
{
    std::cout << ccolors::GREY << message << ccolors::WHITE << std::endl;
}
