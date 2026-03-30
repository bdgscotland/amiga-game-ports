# FindSDL2.cmake for AmigaOS 3.x cross-compilation
# Points to libSDL2-amigaos3 mounted at /sdl2

set(SDL2_FOUND TRUE)
set(SDL2_INCLUDE_DIRS "/sdl2/include")
set(SDL2_LIBRARIES "/sdl2/libSDL2.a")
set(SDL2_VERSION "2.28.0")

# Create imported target expected by modern CMake
if(NOT TARGET SDL2::SDL2)
    add_library(SDL2::SDL2 STATIC IMPORTED)
    set_target_properties(SDL2::SDL2 PROPERTIES
        IMPORTED_LOCATION "/sdl2/libSDL2.a"
        INTERFACE_INCLUDE_DIRECTORIES "/sdl2/include;/sdl2/include/cxx"
        INTERFACE_COMPILE_OPTIONS "-I/sdl2/include/cxx;-include;amiga_cxx_compat.h"
    )
endif()

# SDL2main -- on AmigaOS we don't have a separate SDLmain library
if(NOT TARGET SDL2::SDL2main)
    add_library(SDL2::SDL2main INTERFACE IMPORTED)
endif()
