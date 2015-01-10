/* Copyright Eetu "Razbit" Pesonen, 2015
 * Any kind of redistribution without explicit permission is prohibited. */

/* A class derived from Logger to log to the console */

#ifndef LOGGERCONSOLE_H
#define LOGGERCONSOLE_H

#include <iostream>
#include <stdio.h>
#include <stdarg.h>

#include "logger.h"

class LoggerConsole : public Logger
{
public:
    LoggerConsole(){}
    virtual void write(char* fmt, ...)
    {
        va_list args;
        va_start (args, fmt);
        vprintf(fmt, args);
        va_end (args);
    }
};

#endif // LOGGERCONSOLE_H
