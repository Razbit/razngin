/* Copyright Eetu "Razbit" Pesonen, 2015
 * Any kind of redistribution without explicit permission is prohibited. */

/* Platform macros */

#ifndef PLATFORM_H
#define PLATFORM_H

#if defined linux || defined __linux__ || defined __linux
#define PLATFORM_LINUX
#define PLATFORM_NAME "Linux"

#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
#define PLATFORM_WIN32
#define PLATFORM_NAME "Windows"

#if (defined __MWERKS__ && defined __powerc && !defined macintosh) || defined __APPLE_CC__ || defined macosx
#define PLATFORM_OSX
#define PLATFORM_NAME "MacOS X"
#endif


#endif // PLATFORM_H
