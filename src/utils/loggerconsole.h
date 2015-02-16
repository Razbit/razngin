#ifndef LOGGERCONSOLE_H
#define LOGGERCONSOLE_H

#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include "time.h"
#include "../game.h"

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
        printf("[%s] ", Time::getTime().c_str());

        va_list args;
        va_start (args, fmt);
        vprintf(fmt, args);
        va_end (args);
    }

    /**
     * @brief Write an error message to the screen.
     * @details Uses a function from the printf() -family internally, so is used similarily.
     * @param fmt A C-string containing the formatting used.
     * @param severity An integer for severity of the error (0 == terminate)
     */
    virtual void error(int severity, const char* fmt, ...)
    {
        printf("[%s] ERROR: ", Time::getTime().c_str());

        va_list args;
        va_start (args, fmt);
        vprintf(fmt, args);
        va_end (args);

        if (severity == 0)
        {
            write("Error cannot be handled, terminating..\n");
            Game::terminate(EXIT_FAILURE);
        }
    }
};

#endif // LOGGERCONSOLE_H
