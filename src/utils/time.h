/* Copyright Eetu "Razbit" Pesonen, 2015
 * Any kind of redistribution without explicit permission is prohibited. */

/* Platform-independent time thingy */

#ifndef TIME_H
#define TIME_H

#include <string>
#include "platform.h"

#if defined PLATFORM_WIN32
#include <atltime.h>
#else // Linux, OS X
#include <time.h>
#endif // PLATFORM

class Time
{
public:
    static const std::string getTime()
    {
        std::ostringstream oss;

#if defined PLATFORM_WIN32

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

        return oss;
    }
};

#endif // TIME_H
