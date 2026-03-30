/* config.h -- hand-crafted for AmigaOS 3.x cross-compile with bebbo-gcc */
#ifndef INC_1OOM_CONFIG_H
#define INC_1OOM_CONFIG_H

/* Package info */
#define PACKAGE "1oom"
#define PACKAGE_NAME "1oom"
#define PACKAGE_VERSION "1.11.8"
#define VERSION "1.11.8"

/* C99 headers available via libnix */
#define HAVE_INTTYPES_H 1
#define HAVE_STDBOOL_H 1

/* libnix provides atexit and strcasecmp */
#define HAVE_ATEXIT 1
#define HAVE_STRCASECMP 1

/* SDL2 HW backend */
#define USE_HWSDL2 1

/* No SDL2_mixer for now -- disable audio */
/* #define HAVE_SDL2MIXER 1 */

/* No readline on AmigaOS */
/* #define HAVE_READLINE 1 */

/* No libsamplerate */
/* #define HAVE_SAMPLERATE 1 */

/* Not Windows, not MSDOS */
/* #define IS_WINDOWS 1 */
/* #define IS_MSDOS 1 */

/* No SDLmain on AmigaOS -- we provide our own main() */
/* #define HAVE_SDLMAIN 1 */

/* Byte order -- 68k is big-endian */
#define WORDS_BIGENDIAN 1

#endif
