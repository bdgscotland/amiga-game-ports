/* SDL_mixer stub header for AmigaOS 3.x fheroes2 port.
 * Provides type definitions and function declarations with no-op
 * implementations. Replace with real SDL2_mixer when audio is ported. */

#ifndef SDL_MIXER_H_STUB
#define SDL_MIXER_H_STUB

#include "SDL.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Version */
typedef struct {
    Uint8 major;
    Uint8 minor;
    Uint8 patch;
} SDL_mixer_version;

/* Audio format constants */
#define MIX_DEFAULT_FREQUENCY 22050
#define MIX_DEFAULT_FORMAT    AUDIO_S16SYS
#define MIX_DEFAULT_CHANNELS  2
#define MIX_MAX_VOLUME        128
#define MIX_CHANNELS          8

/* Init flags */
#define MIX_INIT_FLAC   0x00000001
#define MIX_INIT_MOD    0x00000002
#define MIX_INIT_MP3    0x00000008
#define MIX_INIT_OGG    0x00000010
#define MIX_INIT_MID    0x00000020

/* Opaque types */
typedef struct Mix_Chunk {
    int allocated;
    Uint8 *abuf;
    Uint32 alen;
    Uint8 volume;
} Mix_Chunk;

typedef struct Mix_Music Mix_Music;

/* Fading status */
typedef enum {
    MIX_NO_FADING,
    MIX_FADING_OUT,
    MIX_FADING_IN
} Mix_Fading;

/* Music type */
typedef enum {
    MUS_NONE,
    MUS_CMD,
    MUS_WAV,
    MUS_MOD,
    MUS_MID,
    MUS_OGG,
    MUS_MP3,
    MUS_FLAC
} Mix_MusicType;

/* Function declarations -- all no-ops in stub */
int Mix_Init(int flags);
void Mix_Quit(void);

int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);
void Mix_CloseAudio(void);
int Mix_QuerySpec(int *frequency, Uint16 *format, int *channels);

int Mix_AllocateChannels(int numchans);

Mix_Chunk *Mix_LoadWAV(const char *file);
Mix_Chunk *Mix_LoadWAV_RW(SDL_RWops *src, int freesrc);
void Mix_FreeChunk(Mix_Chunk *chunk);

Mix_Music *Mix_LoadMUS(const char *file);
Mix_Music *Mix_LoadMUS_RW(SDL_RWops *src, int freesrc);
void Mix_FreeMusic(Mix_Music *music);

int Mix_PlayChannel(int channel, Mix_Chunk *chunk, int loops);
int Mix_PlayMusic(Mix_Music *music, int loops);
int Mix_FadeInMusic(Mix_Music *music, int loops, int ms);
int Mix_FadeInMusicPos(Mix_Music *music, int loops, int ms, double position);

void Mix_Pause(int channel);
void Mix_Resume(int channel);
int Mix_HaltChannel(int channel);
int Mix_HaltMusic(void);
int Mix_Playing(int channel);
int Mix_PlayingMusic(void);

int Mix_Volume(int channel, int volume);
int Mix_VolumeChunk(Mix_Chunk *chunk, int volume);
int Mix_VolumeMusic(int volume);

int Mix_SetPosition(int channel, Sint16 angle, Uint8 distance);

void Mix_ChannelFinished(void (*channel_finished)(int channel));
void Mix_HookMusicFinished(void (*music_finished)(void));

int Mix_SetSoundFonts(const char *paths);
int Mix_SetTimidityCfg(const char *path);

const char *Mix_GetError(void);

#ifdef __cplusplus
}
#endif

#endif /* SDL_MIXER_H_STUB */
