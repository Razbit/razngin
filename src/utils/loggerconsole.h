#ifndef LOGGERCONSOLE_H
#define LOGGERCONSOLE_H

#include <iostream>
#include <stdio.h>
#include <stdarg.h>

#include "logger.h"

/**
 * @file
 * @brief A class for logging to the console.
 */

/**
 * @brief A class for logging things to the console.
 * @author Eetu "Razbit" Pesonen
 * @version 0.01
 * @date 2015
 * @copyright Any kind of redistribution without explicit permission is prohibited.
 */
class LoggerConsole : public Logger
{
public:
    LoggerConsole(){}

    /**
     * @brief Write a log message to the screen.
     * @details Uses a function from the printf() -family internally, so is used similarily.
     * @param fmt A C-string containing the formatting used.
     */
    virtual void write(const char* fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        vprintf(fmt, args);
        va_end (args);
    }
};

#endif // LOGGERCONSOLE_H
