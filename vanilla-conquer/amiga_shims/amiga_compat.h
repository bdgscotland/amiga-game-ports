/* AmigaOS 3.x compatibility shim for Vanilla Conquer */
#ifndef AMIGA_COMPAT_H
#define AMIGA_COMPAT_H

/* Pull in sys/types.h early to get ssize_t before NDK socket headers */
#include <sys/types.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>

/* Declare stricmp/strnicmp for C++ template contexts */
#ifdef __cplusplus
extern "C" {
#endif
int stricmp(const char *s1, const char *s2);
int strnicmp(const char *s1, const char *s2, size_t n);
char *strdup(const char *s);
#ifdef __cplusplus
}
#endif

/* exec/types.h defines VOLATILE as the volatile keyword, which conflicts
   with Vanilla Conquer's VOLATILE enum value in trigger.h */
#ifdef VOLATILE
#undef VOLATILE
#endif

/* Map POSIX names to libnix names */
#ifndef strcasecmp
#define strcasecmp stricmp
#endif
#ifndef strncasecmp
#define strncasecmp strnicmp
#endif

/* Microsoft _stricmp/_strnicmp -> libnix stricmp/strnicmp */
#ifndef _stricmp
#define _stricmp stricmp
#endif
#ifndef _strnicmp
#define _strnicmp strnicmp
#endif

#endif /* AMIGA_COMPAT_H */
