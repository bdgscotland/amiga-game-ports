# CMake toolchain file for AmigaOS 3.x (m68k) cross-compilation
# Uses bebbo-gcc via Docker (amigadev/crosstools:m68k-amigaos-gcc10)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR m68k)

set(CMAKE_C_COMPILER m68k-amigaos-gcc)
set(CMAKE_CXX_COMPILER m68k-amigaos-g++)
set(CMAKE_AR m68k-amigaos-ar)
set(CMAKE_RANLIB m68k-amigaos-ranlib)

set(CMAKE_C_FLAGS_INIT "-noixemul -m68030 -O0")
# -fpermissive: allows int/long implicit conversions (both 32-bit on 68k)
# On 68k, int and long are both 32-bit but different types. This causes
# lambda return type deduction failures and std::clamp/max type mismatches.
# Force int32_t to be int (not long) to match code expectations.
set(CMAKE_C_FLAGS_INIT "-noixemul -m68030 -O0 -D__INT32_TYPE__=int -D'__UINT32_TYPE__=unsigned int' -D'__INT_LEAST32_TYPE__=int' -D'__UINT_LEAST32_TYPE__=unsigned int'")
set(CMAKE_CXX_FLAGS_INIT "-noixemul -m68030 -O0 -std=c++17 -fpermissive -D__INT32_TYPE__=int -D'__UINT32_TYPE__=unsigned int' -D'__INT_LEAST32_TYPE__=int' -D'__UINT_LEAST32_TYPE__=unsigned int'")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-noixemul -Wl,--allow-multiple-definition")

# Don't try to run test executables during cmake configure
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# SDL2 paths (mounted at /sdl2 in Docker)
set(SDL2_DIR "/sdl2" CACHE PATH "SDL2 root")
set(SDL2_INCLUDE_DIR "/sdl2/include" CACHE PATH "SDL2 include")
set(SDL2_LIBRARY "/sdl2/libSDL2.a" CACHE FILEPATH "SDL2 library")
