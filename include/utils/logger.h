#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <raylib.h> // required for LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_DEBUG 

// #define LOG_STYLE_INDENTED 
#define LOG_STYLE_BLANK_LINE 
#define LOG_STYLE_USE_COLOR

#ifdef LOG_STYLE_USE_COLOR

#define LOG_COLOR_RESET "\033[0m"
#define LOG_COLOR_RED "\033[31m"
#define LOG_COLOR_GREEN "\033[32m"
#define LOG_COLOR_YELLOW "\033[33m"
#define LOG_COLOR_BLUE "\033[34m"
#define LOG_COLOR_MAGENTA "\033[35m"
#define LOG_COLOR_CYAN "\033[36m"
#define LOG_COLOR_BLACK "\033[37m"
#define LOG_COLOR_WHITE "\033[38m"
#define LOG_COLOR_DEFAULT "\033[39m"

#else

#define LOG_COLOR_RESET ""
#define LOG_COLOR_RED ""
#define LOG_COLOR_GREEN ""
#define LOG_COLOR_YELLOW ""
#define LOG_COLOR_BLUE ""
#define LOG_COLOR_MAGENTA ""
#define LOG_COLOR_CYAN ""
#define LOG_COLOR_BLACK ""
#define LOG_COLOR_WHITE ""
#define LOG_COLOR_DEFAULT ""

#endif // LOG_STYLE_USE_COLOR

void LogVaList(int msgType, const char *text, va_list args);
void Log(int msgType, const char *text, ...);

#endif /* __LOGGER_H__ */

