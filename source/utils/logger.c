#include "utils/logger.h"

#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <raylib.h>

void Log(int msgType, const char *text, ...)
{
        va_list args;
        va_start(args, text);

        if (args != NULL)
        {
                LogVaList(msgType, text, args);
        }
        else
        {
                LogVaList(LOG_ERROR, LOG_COLOR_RED "[Logger] " LOG_COLOR_RESET "Error on Log() variable arguments specified in text but never passed!", NULL);
        }
}

void LogVaList(int msgType, const char *text, va_list args)
{
        char timeStr[64] = {0};
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        FILE *outputStream = (msgType == LOG_WARNING) || (msgType == LOG_ERROR) || (msgType == LOG_FATAL) ? stderr : stdout;

        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
        fprintf(outputStream, LOG_COLOR_GREEN "[%s] " LOG_COLOR_RESET, timeStr);

        switch (msgType)
        {
        case LOG_INFO:
                fprintf(outputStream, LOG_COLOR_BLUE "[INFO]" LOG_COLOR_RESET "  : ");
                break;
        case LOG_ERROR:
                fprintf(outputStream, LOG_COLOR_RED "[ERROR]" LOG_COLOR_RESET " : ");
                break;
        case LOG_WARNING:
                fprintf(outputStream, LOG_COLOR_YELLOW "[WARN]" LOG_COLOR_RESET "  : ");
                break;
        case LOG_DEBUG:
                fprintf(outputStream, LOG_COLOR_CYAN "[DEBUG]" LOG_COLOR_RESET " : ");
                break;
        }

#ifdef LOG_STYLE_INDENTED
        fprintf(outputStream, "\n    ");
#endif // LOG_STYLE_INDENTED

        if (args != NULL)
        {
                vfprintf(outputStream, text, args);
                va_end(args);
        }
        fprintf(outputStream, "\n");

#ifdef LOG_STYLE_BLANK_LINE
        fprintf(outputStream, "\n");
#endif // LOG_STYLE_BLANK_LINE
}