#ifndef TIME_H
#define TIME_H

#include <string>
#include <sstream>

#include "platform.h"

#ifdef PLATFORM_WIN32
#include <atltime.h>
#else // Linux, OS X
#include <time.h>
#endif // PLATFORM

/**
 * @file
 * @brief A static class for getting time and date.
 */

/**
 * @brief A platform-independent time thingy.
 * @author Eetu "Razbit" Pesonen
 * @version 0.01
 * @date 2015
 * @copyright Any kind of redistribution without explicit permission is prohibited.
 */
class Time
{
public:
    /**
     * @brief Get current time formatted as HH:MM:SS.
     * @return A string containing the current time.
     */
    static const std::string getTime()
    {
        std::ostringstream oss;

#ifdef PLATFORM_WIN32

        Ctime time = Ctime::GetCurrentTime();
        oss << time.GetHour() << ":" \
            << time.GetMinute() << ":" \
            << time.GetSecond();

#else // Linux, OS X

        time_t raw;
        struct tm* timeinfo;
        char buf[50];

        time(&raw);
        timeinfo = localtime(&raw);

        strftime(buf, 50, "%H:%M:%S", timeinfo);
        oss << buf;

#endif // PLATFORM

        return oss.str();
    }

    /**
     * @brief Get current date formatted as YYYY-MM-DD.
     * @return A string containing the date.
     */
    static const std::string getDate()
    {
        std::ostringstream oss;

#ifdef PLATFORM_WIN32

        CTime time = CTime::GetCurrentTime();
        oss << time.GetYear() << "-" \
            << time.GetMonth() << "-" \
            << time.GetDay();

#else // Linux, OS X

        time_t raw;
        struct tm* timeinfo;
        char buf[50];

        time(&raw);
        timeinfo = localtime(&raw);

        strftime(buf, 50, "%Y-%m-%d", timeinfo);
        oss << buf;

#endif

        return oss.str();
    }
};

#endif // TIME_H
