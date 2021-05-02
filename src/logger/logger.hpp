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
    void warning(const std::string message1, const std::string message2);
    void warning(const std::string message1, const std::string message2, const std::string message3);

    /*
        печать низкоприоритетной информации
    */
    void trace(const std::string message);
    void trace(const std::string message1, const std::string message2);
    void trace(const std::string message1, const std::string message2, const std::string message3);

    /*
        печать ошибок
    */
    void error(const std::string message);
    void error(const std::string message1, const std::string message2);
    void error(const std::string message1, const std::string message2, const std::string message3);

    /*
        печать отладочной информации
    */
    void debug(const std::string message);
    void debug(const std::string message1, const std::string message2);
    void debug(const std::string message1, const std::string message2, const std::string message3);
};

#endif