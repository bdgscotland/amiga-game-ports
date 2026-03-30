/* video_update_fast.c -- Fast palette conversion for AmigaOS 3.x
 *
 * Replaces the SDL_BlitSurface palette conversion path with a direct
 * 8-bit to 32-bit lookup table conversion. SDL_BlitSurface goes through
 * SDL_blit_1.c (Blit1to4) which is very slow on 68k.
 *
 * This file is #included from hwsdl2_video.c when __AMIGAOS3__ is defined.
 */

/* Forward declarations for functions defined later in hwsdl2_video.c */
static void video_create_upscaled_texture(bool force);
static void video_adjust_window_size(int *wptr, int *hptr);

/* 32-bit palette lookup table -- rebuilt every frame (256 entries is cheap) */
static uint32_t fast_palette_rgb[256];

/* Direct 8-bit paletted -> 32-bit conversion, no SDL_BlitSurface */
static void video_update_amiga(void)
{
    if (video.noblit) {
        return;
    }
    if (video.need_resize) {
        if (SDL_GetTicks() > (video.last_resize_time + RESIZE_DELAY)) {
            int flags, w, h;
            flags = SDL_GetWindowFlags(video.window);
            SDL_GetWindowSize(video.window, &w, &h);
            if ((flags & (SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)) == 0) {
                if (hw_opt_autotrim || video.shrink || video.enlarge) {
                    video_adjust_window_size(&w, &h);
                }
                SDL_SetWindowSize(video.window, w, h);
                hw_opt_screen_winw = w;
                hw_opt_screen_winh = h;
            }
            hw_mouse_set_scale(w, h);
            video_create_upscaled_texture(false);
            video.need_resize = false;
            video.shrink = false;
            video.enlarge = false;
        } else {
            return;
        }
    }

    /* Rebuild palette lookup table every frame.
     * 256 iterations is negligible vs 64K pixel conversions.
     * This avoids the dirty-flag issue where video_setpal calls
     * the original video_update() directly.
     */
    {
        SDL_PixelFormat *fmt = video.interbuffer->format;
        for (int i = 0; i < 256; ++i) {
            fast_palette_rgb[i] = SDL_MapRGB(fmt,
                video.color[i].r,
                video.color[i].g,
                video.color[i].b);
        }
    }

    /* Direct palette conversion: 8-bit -> 32-bit via lookup table. */
    {
        uint8_t *src = (uint8_t *)video.screen->pixels;
        int src_pitch = video.screen->pitch;
        uint32_t *dst = (uint32_t *)video.interbuffer->pixels;
        int dst_pitch = video.interbuffer->pitch / 4;
        int w = video.bufw;
        int h = video.bufh;
        for (int y = 0; y < h; ++y) {
            uint32_t *row = dst + y * dst_pitch;
            for (int x = 0; x < w; ++x) {
                row[x] = fast_palette_rgb[src[x]];
            }
            src += src_pitch;
        }
    }

    SDL_UpdateTexture(video.texture, NULL,
        video.interbuffer->pixels, video.interbuffer->pitch);

    SDL_RenderClear(video.renderer);

    SDL_SetRenderTarget(video.renderer, NULL);
    SDL_RenderCopy(video.renderer, video.texture, NULL, NULL);
    SDL_RenderPresent(video.renderer);
}
