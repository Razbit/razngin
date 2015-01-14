#ifndef LOGGER_H
#define LOGGER_H

#include <string>

/**
 * @file
 * @brief An abstract class for logging.
 */

/**
 * @brief An abstract class for logging things.
 * @author Eetu "Razbit" Pesonen
 * @version 0.01
 * @date 2015
 * @copyright Any kind of redistribution without explicit permission is prohibited.
 */

class Logger
{
public:
    Logger(){}
    virtual ~Logger(){}

    /**
     * @brief Write a log message.
     * @details Uses a function from the printf() -family internally, so is used similarily.
     * @param fmt A C-string containing the formatting used.
     */
    virtual void write(const char* fmt, ...) = 0;
};

#endif // LOGGER_H
