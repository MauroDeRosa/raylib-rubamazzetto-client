#include "logger.h"

#include <time.h>
#include <raylib.h>

#define LOG_STYLE_INDENTED 0
#define LOG_STYLE_BLANK_LINE 1
#define LOG_STYLE_USE_COLOR

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

void Log(int msgType, const char *text, ...)
{
    char timeStr[64] = {0};
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    FILE *outputStream = (msgType == LOG_WARNING) || (msgType == LOG_ERROR) || (msgType == LOG_FATAL) ? stderr : stdout;
    va_list args;

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);

#ifdef LOG_STYLE_USE_COLOR
    fprintf(outputStream, LOG_COLOR_GREEN "[%s] " LOG_COLOR_RESET, timeStr);
#else
    fprintf(outputStream, "[%s] ", timeStr);
#endif // LOG_STYLE_USE_COLOR

    switch (msgType)
    {
    case LOG_INFO:
#ifdef LOG_STYLE_USE_COLOR
        fprintf(outputStream, LOG_COLOR_BLUE "[INFO]" LOG_COLOR_RESET "  : ");
#else
        fprintf(outputStream, "[INFO]  : ");
#endif // LOG_STYLE_USE_COLOR
        break;
    case LOG_ERROR:
#ifdef LOG_STYLE_USE_COLOR
        fprintf(outputStream, LOG_COLOR_RED "[ERROR]" LOG_COLOR_RESET " : ");
#else
        fprintf(outputStream, "[ERROR] : ");
#endif // LOG_STYLE_USE_COLOR
        break;
    case LOG_WARNING:
#ifdef LOG_STYLE_USE_COLOR
        fprintf(outputStream, LOG_COLOR_YELLOW "[WARN]" LOG_COLOR_RESET "  : ");
#else
        fprintf(outputStream, "[WARN]  : ");
#endif // LOG_STYLE_USE_COLOR
        break;
    case LOG_DEBUG:
#ifdef LOG_STYLE_USE_COLOR
        fprintf(outputStream, LOG_COLOR_CYAN "[DEBUG]" LOG_COLOR_RESET " : ");
#else
        fprintf(outputStream, "[DEBUG] : ");
#endif // LOG_STYLE_USE_COLOR
        break;
    default:
        break;
    }

    if (LOG_STYLE_INDENTED)
        fprintf(outputStream, "\n    ");

    va_start(args, text);
    vfprintf(outputStream, text, args);
    va_end(args);
    fprintf(outputStream, "\n");

    if (LOG_STYLE_BLANK_LINE)
        fprintf(outputStream, "\n");
}