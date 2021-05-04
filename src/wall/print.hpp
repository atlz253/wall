#include <string>

/*
    печать предупреждений
*/
void printWarning(const std::string message);
void printWarning(const std::string message1, const std::string message2);
void printWarning(const std::string message1, const std::string message2, const std::string message3);

/*
    печать низкоприоритетной информации
*/
void printTrace(const std::string message);
void printTrace(const std::string message1, const std::string message2);
void printTrace(const std::string message1, const std::string message2, const std::string message3);

/*
    печать ошибок
*/
void printError(const std::string message);
void printError(const std::string message1, const std::string message2);
void printError(const std::string message1, const std::string message2, const std::string message3);

/*
    печать отладочной информации
*/
void printDebug(const std::string message);
void printDebug(const std::string message1, const std::string message2);
void printDebug(const std::string message1, const std::string message2, const std::string message3);