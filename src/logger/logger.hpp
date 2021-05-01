#ifndef LOGGER
#define LOGGER

#include <string>

class Logger
{
private:
    int _level;

public:
    /*
        создание логгера с проритетом сообщений warning (по-умолчанию)
    */
    Logger();

    /*
        создание логгера с заданным проритетом сообщений
        приоритеты (нижние вкючают в себя все верхние):
        error (0) - печать ошибок
        warning (1) - печать предупреждений
        debug (2) - печать отладочной информации
        trace (3) - печать всей информации
    */
    Logger(const std::string status);

    /*
        печать предупреждений
    */
    void warning(const std::string message);

    /*
        печать низкоприоритетной информации
    */
    void trace(const std::string message);

    /*
        печать ошибок
    */
    void error(const std::string message);

    /*
        печать отладочной информации
    */
    void debug(const std::string message);
};

#endif