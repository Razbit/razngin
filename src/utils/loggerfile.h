#ifndef LOGGERFILE_H
#define LOGGERFILE_H

#include <stdio.h>
#include <string>

#include "platform.h"
#include "logger.h"
#include "time.h"

/**
 * @file
 * @brief A class for logging to a file.
 */

/**
 * @brief A class for logging things to a log file.
 * @author Eetu "Razbit" Pesonen
 * @version 0.01
 * @date 2015
 * @copyright Any kind of redistribution without explicit permission is prohibited.
 */
class LoggerFile : public Logger
{
public:
    /**
     * @brief Open the log file and writes the beginning message.
     * @param path Path to the log file
     */
    LoggerFile(const char* path)
    {
            outfile = fopen(path, "w");

            if (outfile == NULL)
                return;

            fprintf(outfile, "Begin log (%s at %s)\n", Time::getDate().c_str(), \
                    Time::getTime().c_str());
            fprintf(outfile, "Platform: %s\n\n", PLATFORM_NAME);
    }

    /**
     * @brief Write the ending message and close the FILE stream.
     */
    virtual ~LoggerFile()
    {
        if (outfile == NULL)
            return;

        fprintf(outfile, "End log (%s at %s)\n", Time::getDate().c_str(), \
                 Time::getTime().c_str());
        fclose(outfile);
    }

    /**
     * @brief Write a log message to the log file.
     * @details Uses a function from the printf() -family internally, so is used similarily.
     * @param fmt A C-string containing the formatting used.
     */
    virtual void write(const char* fmt, ...)
    {
        if (outfile != NULL)
        {
            fprintf(outfile, "[%s] ", Time::getTime().c_str());

            va_list args;
            va_start (args, fmt);
            vfprintf(outfile, fmt, args);
            va_end (args);
        }
    }

    /**
     * @brief Write an error message to the log file.
     * @details Uses a function from the printf() -family internally, so is used similarily.
     * @param fmt A C-string containing the formatting used.
     * @param severity An integer for severity of the error (0 == terminate)
     */
    virtual void error(int severity, const char* fmt, ...)
    {
        if (outfile != NULL)
        {
            fprintf(outfile, "[%s] ERROR: ", Time::getTime().c_str());

            va_list args;
            va_start (args, fmt);
            vfprintf(outfile, fmt, args);
            va_end (args);
        }

        if (severity == 0)
        {
            write("Error cannot be handled, terminating..\n");
            Game::terminate(EXIT_FAILURE);
        }
    }

private:
    /** The log file pointer */
    FILE* outfile;
};

#endif // LOGGERFILE_H
