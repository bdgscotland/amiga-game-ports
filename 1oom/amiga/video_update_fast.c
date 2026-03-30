/* video_update_fast.c -- Bypass SDL_Renderer for AmigaOS 3.x
 *
 * The standard SDL_Renderer pipeline does 5 copies per frame:
 *   1. game buf -> screen surface (memcpy)
 *   2. screen -> interbuffer (SDL_BlitSurface palette convert) [18ms]
 *   3. interbuffer -> texture (SDL_UpdateTexture memcpy) [18ms]
 *   4. texture -> renderer surface (SDL_RenderCopy software blit) [49ms]
 *   5. renderer surface -> VRAM (SDL_RenderPresent/WritePixelArray) [243ms]
 *   Total: 328ms per frame = 3 FPS
 *
 * This replaces steps 2-5 with:
 *   2. screen -> window surface (palette convert via lookup table)
 *   3. SDL_UpdateWindowSurface (single WritePixelArray)
 *   Total target: ~260ms per frame = ~4 FPS (still limited by WPA)
 *
 * This file is #included from hwsdl2_video.c when __AMIGAOS3__ is defined.
 */

/* Forward declarations for functions defined later in hwsdl2_video.c */
static void video_create_upscaled_texture(bool force);
static void video_adjust_window_size(int *wptr, int *hptr);

/* 32-bit palette lookup table */
static uint32_t fast_palette_rgb[256];

/* Cached window surface for direct writes */
static SDL_Surface *amiga_winsurface = NULL;

static void video_update_amiga(void)
{
    Uint32 t0, t1, t2;
    static int vframe = 0;

    if (video.noblit) {
        return;
    }

    /* Get or cache the window surface */
    if (!amiga_winsurface) {
        amiga_winsurface = SDL_GetWindowSurface(video.window);
        if (amiga_winsurface) {
            /* Clear to black -- surface may be larger than game area */
            SDL_memset(amiga_winsurface->pixels, 0,
                amiga_winsurface->pitch * amiga_winsurface->h);
            SDL_Log("AMIGA_FB: window surface %dx%d fmt=0x%x bpp=%d",
                amiga_winsurface->w, amiga_winsurface->h,
                (unsigned)amiga_winsurface->format->format,
                (int)amiga_winsurface->format->BytesPerPixel);
        }
    }

    if (!amiga_winsurface) {
        /* Can't get window surface -- fall back to original path */
        return;
    }

    /* Rebuild palette lookup table every frame using the window surface format.
     * 256 iterations is negligible vs 64K+ pixel conversions. */
    {
        SDL_PixelFormat *fmt = amiga_winsurface->format;
        for (int i = 0; i < 256; ++i) {
            fast_palette_rgb[i] = SDL_MapRGB(fmt,
                video.color[i].r,
                video.color[i].g,
                video.color[i].b);
        }
    }

    t0 = SDL_GetTicks();

    /* Palette convert 8-bit screen directly into window surface.
     * This replaces SDL_BlitSurface + SDL_UpdateTexture + SDL_RenderCopy.
     * The window surface is at window size; we write at game resolution
     * (top-left corner). */
    {
        uint8_t *src = (uint8_t *)video.screen->pixels;
        int src_pitch = video.screen->pitch;
        int dst_bpp = amiga_winsurface->format->BytesPerPixel;
        int w = video.bufw;
        int h = video.bufh;

        if (dst_bpp == 4) {
            /* 32-bit destination: direct palette lookup */
            uint32_t *dst_base = (uint32_t *)amiga_winsurface->pixels;
            int dst_pitch32 = amiga_winsurface->pitch / 4;

            for (int y = 0; y < h; ++y) {
                uint32_t *dst_row = dst_base + y * dst_pitch32;
                for (int x = 0; x < w; ++x) {
                    dst_row[x] = fast_palette_rgb[src[x]];
                }
                src += src_pitch;
            }
        }
    }

    t1 = SDL_GetTicks();

    /* Single call to push pixels to screen */
    SDL_UpdateWindowSurface(video.window);

    t2 = SDL_GetTicks();

    if (vframe < 20) {
        SDL_Log("AF%d: convert=%lu present=%lu total=%lu",
            vframe, (unsigned long)(t1 - t0), (unsigned long)(t2 - t1),
            (unsigned long)(t2 - t0));
    }
    ++vframe;
}
