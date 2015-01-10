/* Copyright Eetu "Razbit" Pesonen, 2015
 * Any kind of redistribution without explicit permission is prohibited. */

/* A class derived from Logger to log to files */

#ifndef LOGGERFILE_H
#define LOGGERFILE_H

#include <stdio.h>
#include <string>

#include "platform.h"
#include "logger.h"
#include "time.h"

class LoggerFile : public Logger
{
public:
    LoggerFile(const char* path)
    {
            outfile = fopen(path, "w");

            if (outfile == NULL)
                return;

            fprintf(outfile, " Begin log (%s at %s)\n", Time::getDate().c_str(), \
                    Time::getTime().c_str());
            fprintf(outfile, "Platform: %s\n\n", PLATFORM_NAME;
    }

    virtual ~LoggerFile()
    {
        if (outfile == NULL)
            return;

        fprintf(outfile, " End log (%s at %s)\n", Time::getDate().c_str(), \
                 Time::getTime().c_str();
        fclose(outfile);
    }

    virtual void write(char* fmt, ...)
    {
        if (outfile != NULL)
        {
            va_list args;
            va_start (args, fmt);
            vfprintf(outfile, fmt, args);
            va_end (args);
        }
    }

private:
    FILE* outfile;
};

#endif // LOGGERFILE_H
