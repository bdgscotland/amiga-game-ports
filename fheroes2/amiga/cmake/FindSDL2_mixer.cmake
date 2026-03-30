# FindSDL2_mixer.cmake for AmigaOS 3.x cross-compilation
# Points to our stub SDL_mixer library

set(SDL2_mixer_FOUND TRUE)
set(SDL2_MIXER_FOUND TRUE)
set(SDL2_mixer_INCLUDE_DIRS "/amiga/sdl2_mixer_stub")
set(SDL2_mixer_LIBRARIES "")
set(SDL2_mixer_VERSION "2.6.0")

# Create imported target
if(NOT TARGET SDL2_mixer::SDL2_mixer)
    add_library(SDL2_mixer::SDL2_mixer INTERFACE IMPORTED)
    set_target_properties(SDL2_mixer::SDL2_mixer PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "/amiga/sdl2_mixer_stub"
    )
endif()
