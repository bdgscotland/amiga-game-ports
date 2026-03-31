/* AmigaOS 3.x sleep shim for Vanilla Conquer
 * Replaces mssleep.h -- uses SDL_Delay() instead of nanosleep/Sleep.
 * This header is force-included before the original mssleep.h via
 * -include and takes priority because we define MSSLEEP_H first.
 */
#ifndef MSSLEEP_H
#define MSSLEEP_H

/* Use SDL_Delay for sleep since we're already linking SDL2 */
#include <SDL.h>

static inline void us_sleep(unsigned us)
{
    unsigned ms = (us + 999) / 1000;
    if (ms == 0) {
        ms = 1;
    }
    SDL_Delay(ms);
}

static inline void ms_sleep(unsigned ms)
{
    if (ms == 0) {
        ms = 1;
    }
    SDL_Delay(ms);
}

#endif /* MSSLEEP_H */
