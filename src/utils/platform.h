/**
 * @file
 * @brief Macros for easily determining the platform.
 * @author Eetu "Razbit" Pesonen
 * @version 0.01
 * @date 2015
 * @copyright Any kind of redistribution without explicit permission is prohibited.
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#if defined linux || defined __linux__ || defined __linux
#define PLATFORM_LINUX
#define PLATFORM_NAME "Linux"

#elif defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
#define PLATFORM_WIN32
#define PLATFORM_NAME "Windows"

#elif (defined __MWERKS__ && defined __powerc && !defined macintosh) || defined __APPLE_CC__ || defined macosx
#define PLATFORM_OSX
#define PLATFORM_NAME "MacOS X"
#endif


#endif // PLATFORM_H
