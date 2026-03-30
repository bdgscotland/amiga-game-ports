/* AmigaOS 3.x shims for SDLPoP */
#include <string.h>
#include <math.h>

/* libnix doesn't have strnlen */
size_t strnlen(const char *s, size_t maxlen)
{
    size_t len = 0;
    while (len < maxlen && s[len]) len++;
    return len;
}

/* libnix doesn't have log2f */
float log2f(float x)
{
    return (float)(log((double)x) / log(2.0));
}
