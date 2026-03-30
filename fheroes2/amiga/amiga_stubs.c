/* Stub functions for AmigaOS 3.x fheroes2 port.
 * Provides missing POSIX functions that libstdc++ references. */

#include <string.h>
#include <errno.h>

/* __xpg_strerror_r -- POSIX strerror_r variant used by libstdc++ system_error */
int __xpg_strerror_r(int errnum, char *buf, unsigned long buflen)
{
    const char *msg = strerror(errnum);
    if (!msg) msg = "Unknown error";
    strncpy(buf, msg, buflen);
    if (buflen > 0) buf[buflen - 1] = '\0';
    return 0;
}
