/* Stub functions for AmigaOS 3.x fheroes2 port.
 * Provides missing POSIX functions, stack cookie, version string,
 * and early startup debugging. */

#include <string.h>
#include <errno.h>
#include <stdio.h>

/* Stack cookie -- 256KB for C++ with deep call stacks */
long __stack = 262144;

/* AmigaOS version string */
static const char *verstag = "$VER: fheroes2 1.1.6 (30.03.2026)";

/* File-based debug log -- survives crashes */
static FILE *dbgfile = NULL;

static void dbg(const char *msg)
{
    if (!dbgfile) {
        dbgfile = fopen("WORK:fheroes2_dbg.txt", "w");
    }
    if (dbgfile) {
        fputs(msg, dbgfile);
        fputc('\n', dbgfile);
        fflush(dbgfile);
    }
}

/* This runs VERY early -- before C++ constructors */
__attribute__((constructor(101))) void amiga_early_debug(void)
{
    dbg("=== fheroes2 early init ===");
    dbg("constructor(101) reached");
}

/* This runs at default priority -- after most C++ statics */
__attribute__((constructor(65535))) void amiga_late_debug(void)
{
    dbg("constructor(65535) reached -- all statics done");
}

/* __xpg_strerror_r -- POSIX strerror_r variant used by libstdc++ system_error */
int __xpg_strerror_r(int errnum, char *buf, unsigned long buflen)
{
    const char *msg = strerror(errnum);
    if (!msg) msg = "Unknown error";
    strncpy(buf, msg, buflen);
    if (buflen > 0) buf[buflen - 1] = '\0';
    return 0;
}
