/* Minimal SDL2_image stub for AmigaOS 3.x */
#ifndef SDL_IMAGE_STUB_H
#define SDL_IMAGE_STUB_H

#include <SDL.h>

static inline SDL_Surface* IMG_Load(const char *file) {
    return SDL_LoadBMP(file);
}

static inline SDL_Surface* IMG_Load_RW(SDL_RWops *src, int freesrc) {
    return SDL_LoadBMP_RW(src, freesrc);
}

static inline int IMG_SavePNG(SDL_Surface *surface, const char *file) {
    (void)surface; (void)file;
    return -1;
}

static inline const char* IMG_GetError(void) {
    return SDL_GetError();
}

#endif
