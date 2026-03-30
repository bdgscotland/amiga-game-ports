# FindSDL2_mixer.cmake for AmigaOS 3.x cross-compilation
# Builds and links the stub SDL_mixer library with POSIX stubs.

set(SDL2_mixer_FOUND TRUE)
set(SDL2_MIXER_FOUND TRUE)
set(SDL2_mixer_VERSION "2.6.0")

# Build the stub library
if(NOT TARGET sdl2_mixer_stub)
    add_library(sdl2_mixer_stub STATIC /amiga/sdl2_mixer_stub/SDL_mixer_stub.c)
    target_include_directories(sdl2_mixer_stub PRIVATE /sdl2/include /amiga/sdl2_mixer_stub)
endif()

# Create imported target that links to our stub
if(NOT TARGET SDL2_mixer::SDL2_mixer)
    add_library(SDL2_mixer::SDL2_mixer INTERFACE IMPORTED)
    set_target_properties(SDL2_mixer::SDL2_mixer PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "/amiga/sdl2_mixer_stub"
        INTERFACE_LINK_LIBRARIES "sdl2_mixer_stub"
    )
endif()
