#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>
#include <raylib.h>

#define LOG_STYLE_INDENTED 0
#define LOG_STYLE_BLANK_LINE 1
#define LOG_STYLE_USE_COLOR

void LogVaList(int msgType, const char *text, va_list args);
void Log(int msgType, const char *text, ...);

#endif /* __LOGGER_H__ */

