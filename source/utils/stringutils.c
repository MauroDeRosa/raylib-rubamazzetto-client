#include "utils/stringutils.h"
#include <string.h>

void StringLimit(char *string, size_t maxlen)
{
    size_t length = strlen(string);
    size_t pos = (maxlen <= length) ? maxlen : length;
    while (pos <= length)
    {
        string[pos] = '\0';
        pos++;
    }
}
