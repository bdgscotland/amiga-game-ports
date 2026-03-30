/* SDL2_image stub using stb_image for PNG loading on AmigaOS 3.x */
#ifndef SDL_IMAGE_STUB_H
#define SDL_IMAGE_STUB_H

#include <SDL.h>

/* stb_image functions -- implemented in amiga_shims.c */
extern unsigned char *stbi_load_from_memory(unsigned char const *buffer, int len,
    int *x, int *y, int *channels_in_file, int desired_channels);
extern void stbi_image_free(void *retval_from_stbi_load);

static inline SDL_Surface* IMG_Load(const char *file) {
    int w, h, channels;
    SDL_RWops *rw = SDL_RWFromFile(file, "rb");
    if (!rw) return NULL;

    Sint64 size = SDL_RWsize(rw);
    if (size <= 0) { SDL_RWclose(rw); return NULL; }

    unsigned char *buf = (unsigned char *)SDL_malloc((size_t)size);
    if (!buf) { SDL_RWclose(rw); return NULL; }

    SDL_RWread(rw, buf, 1, (size_t)size);
    SDL_RWclose(rw);

    unsigned char *pixels = stbi_load_from_memory(buf, (int)size, &w, &h, &channels, 4);
    SDL_free(buf);
    if (!pixels) return NULL;

    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormatFrom(
        pixels, w, h, 32, w * 4, SDL_PIXELFORMAT_RGBA32);
    if (surf) {
        surf->flags &= ~SDL_PREALLOC;
    } else {
        stbi_image_free(pixels);
    }
    return surf;
}

static inline SDL_Surface* IMG_Load_RW(SDL_RWops *src, int freesrc) {
    int w, h, channels;
    Sint64 size = SDL_RWsize(src);
    if (size <= 0) {
        if (freesrc) SDL_RWclose(src);
        return NULL;
    }

    unsigned char *buf = (unsigned char *)SDL_malloc((size_t)size);
    if (!buf) { if (freesrc) SDL_RWclose(src); return NULL; }

    SDL_RWread(src, buf, 1, (size_t)size);
    if (freesrc) SDL_RWclose(src);

    unsigned char *pixels = stbi_load_from_memory(buf, (int)size, &w, &h, &channels, 4);
    SDL_free(buf);
    if (!pixels) return NULL;

    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormatFrom(
        pixels, w, h, 32, w * 4, SDL_PIXELFORMAT_RGBA32);
    if (surf) {
        surf->flags &= ~SDL_PREALLOC;
    } else {
        stbi_image_free(pixels);
    }
    return surf;
}

static inline int IMG_SavePNG(SDL_Surface *surface, const char *file) {
    (void)surface; (void)file;
    return -1;
}

static inline const char* IMG_GetError(void) {
    return SDL_GetError();
}

#endif
