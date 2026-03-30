/* SDL_mixer stub implementation for AmigaOS 3.x fheroes2 port.
 * All functions are no-ops. Audio initialization "succeeds" but
 * no sound is produced. Replace with real SDL2_mixer when ready. */

#include "SDL.h"
#include "SDL_mixer.h"

int Mix_Init(int flags)
{
    (void)flags;
    return 0;
}

void Mix_Quit(void) {}

int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize)
{
    (void)frequency; (void)format; (void)channels; (void)chunksize;
    return -1; /* signal failure so fheroes2 skips audio setup */
}

void Mix_CloseAudio(void) {}

int Mix_QuerySpec(int *frequency, Uint16 *format, int *channels)
{
    (void)frequency; (void)format; (void)channels;
    return 0;
}

int Mix_AllocateChannels(int numchans)
{
    (void)numchans;
    return 0;
}

Mix_Chunk *Mix_LoadWAV(const char *file)
{
    (void)file;
    return NULL;
}

Mix_Chunk *Mix_LoadWAV_RW(SDL_RWops *src, int freesrc)
{
    (void)src; (void)freesrc;
    return NULL;
}

void Mix_FreeChunk(Mix_Chunk *chunk) { (void)chunk; }

Mix_Music *Mix_LoadMUS(const char *file)
{
    (void)file;
    return NULL;
}

Mix_Music *Mix_LoadMUS_RW(SDL_RWops *src, int freesrc)
{
    (void)src; (void)freesrc;
    return NULL;
}

void Mix_FreeMusic(Mix_Music *music) { (void)music; }

int Mix_PlayChannel(int channel, Mix_Chunk *chunk, int loops)
{
    (void)channel; (void)chunk; (void)loops;
    return -1;
}

int Mix_PlayMusic(Mix_Music *music, int loops)
{
    (void)music; (void)loops;
    return -1;
}

int Mix_FadeInMusic(Mix_Music *music, int loops, int ms)
{
    (void)music; (void)loops; (void)ms;
    return -1;
}

int Mix_FadeInMusicPos(Mix_Music *music, int loops, int ms, double position)
{
    (void)music; (void)loops; (void)ms; (void)position;
    return -1;
}

void Mix_Pause(int channel) { (void)channel; }
void Mix_Resume(int channel) { (void)channel; }

int Mix_HaltChannel(int channel)
{
    (void)channel;
    return 0;
}

int Mix_HaltMusic(void) { return 0; }
int Mix_Playing(int channel) { (void)channel; return 0; }
int Mix_PlayingMusic(void) { return 0; }

int Mix_Volume(int channel, int volume)
{
    (void)channel; (void)volume;
    return MIX_MAX_VOLUME;
}

int Mix_VolumeChunk(Mix_Chunk *chunk, int volume)
{
    (void)chunk; (void)volume;
    return MIX_MAX_VOLUME;
}

int Mix_VolumeMusic(int volume)
{
    (void)volume;
    return MIX_MAX_VOLUME;
}

int Mix_SetPosition(int channel, Sint16 angle, Uint8 distance)
{
    (void)channel; (void)angle; (void)distance;
    return 0;
}

void Mix_ChannelFinished(void (*channel_finished)(int channel))
{
    (void)channel_finished;
}

void Mix_HookMusicFinished(void (*music_finished)(void))
{
    (void)music_finished;
}

int Mix_SetSoundFonts(const char *paths)
{
    (void)paths;
    return 1;
}

int Mix_SetTimidityCfg(const char *path)
{
    (void)path;
    return 1;
}

const char *Mix_GetError(void)
{
    return "SDL_mixer stub - no audio on AmigaOS 3.x";
}
