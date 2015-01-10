/* Copyright Eetu "Razbit" Pesonen, 2015
 * Any kind of redistribution without explicit permission is prohibited. */

/* An abstract class for logging things */

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger
{
public:
    Logger(){}
    virtual ~Logger(){}
    virtual void write(char* fmt, ...) = 0;
};

#endif // LOGGER_H
