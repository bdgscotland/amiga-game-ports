/* AmigaOS 3.x shims for SDLPoP */
#include <string.h>
#include <math.h>

/* stb_image implementation -- compiled once here, declared extern in stub header */
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_ONLY_BMP
#define STBI_NO_STDIO
#include "stb_image.h"

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
