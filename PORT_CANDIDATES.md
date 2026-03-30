# Port Candidates

Games researched for porting to AmigaOS 3.x via [libSDL2-amigaos3](https://github.com/bdgscotland/libSDL2-amigaos3).

## Toolchain Constraints

- **bebbo GCC 6.5.0b**: C99, C++14 max
- **No C++17**: The experimental GCC 15 Docker image has broken libstdc++ (static constructor crashes)
- **No OpenGL**: Software rendering only (SDL_Renderer + SDL_Texture)
- **No dlopen**: Static linking only

## Tier 1: High Impact, Low Risk

These are pure C or C++11, small codebases, minimal deps, and have Amiga heritage.

### 1oom (Master of Orion 1)
- **Repo:** https://github.com/1oom-fork/1oom
- **Language:** Pure C99 (`-std=c99 -pedantic`)
- **SDL2 deps:** SDL2, SDL2_mixer (audio can be disabled)
- **Size:** ~320 source files (~184 .c, ~136 .h)
- **Build:** Autotools
- **Rendering:** 8-bit paletted framebuffer -> SDL_UpdateTexture (same as Chocolate Doom)
- **Other:** Integer math only, no threading, no floating point
- **Data:** Requires original MoO1 v1.3 LBX files
- **Amiga port:** None exists
- **Notes:** Clean OS abstraction layer (`src/os/`), needs ~100 lines for AmigaOS. Code inspired by Chocolate Doom. Should be a near-repeat of the Doom porting process.

### SDLPoP (Prince of Persia)
- **Repo:** https://github.com/NagyD/SDLPoP
- **Language:** C99
- **SDL2 deps:** SDL2, SDL2_image
- **Size:** ~28 source files
- **Build:** Makefile
- **Rendering:** Software, no OpenGL
- **Data:** Bundled (freeware assets included)
- **Amiga port:** None exists (original PoP ran on Amiga natively)
- **Notes:** Tiny codebase, easiest port on this list. Prince of Persia is iconic on Amiga.

### REminiscence (Flashback)
- **Repo:** https://github.com/cyxx/REminiscence
- **Language:** C++ (pre-C++11 style, should compile as C++03)
- **SDL2 deps:** SDL2
- **Other deps:** libmodplug (music), zlib
- **Size:** ~60 files
- **Build:** Makefile
- **Rendering:** Software, SDL_Renderer
- **Data:** Requires original Flashback data files
- **Amiga port:** None exists (Flashback was THE iconic Amiga game)
- **Notes:** Same author as blues and hode (cyxx). Tiny codebase, simple build.

### Another World (Out of This World)
- **Repo:** https://github.com/fabiensanglard/Another-World-Bytecode-Interpreter
- **Language:** C++11
- **SDL2 deps:** SDL2
- **Other deps:** zlib
- **Size:** ~28 files
- **Build:** CMake
- **Rendering:** Polygon-based software renderer, SDL_Texture
- **Data:** Requires original game data
- **Amiga port:** None of this reimplementation (original was Amiga-native)
- **Notes:** Legendary title. Maximum community impact. Tiny codebase.

## Tier 2: Good Candidates

### OpenTyrian (Tyrian)
- **Repo:** https://github.com/opentyrian/opentyrian
- **Language:** C99
- **SDL2 deps:** SDL2 (SDL2_net optional for multiplayer)
- **Size:** ~98 files
- **Build:** Makefile
- **Data:** Freeware (Tyrian 2.1 data is free)
- **Notes:** Fast-paced shmup, good for showing off rendering performance. Free game data is a huge plus.

### NXEngine-evo (Cave Story)
- **Repo:** https://github.com/nxengine/nxengine-evo
- **Language:** C++11
- **SDL2 deps:** SDL2, SDL2_mixer, SDL2_image (+libpng, libjpeg)
- **Size:** ~136 .cpp/.c files
- **Build:** CMake
- **Notes:** The real Cave Story (we already have the demake via ccleste). Heavier dependency chain.

### Omnispeak (Commander Keen 4/5/6)
- **Repo:** https://github.com/sulix/omnispeak
- **Language:** Pure C
- **SDL2 deps:** SDL2 only
- **Size:** ~96 files
- **Build:** Makefile + CMake
- **Data:** Requires original Keen data files
- **Notes:** Zero external deps. Has a software-only SDL2 renderer option (no GL).

### Blues / Prehistorik 2 / Jukebox Adventure
- **Repo:** https://github.com/cyxx/blues
- **Language:** Pure C
- **SDL2 deps:** SDL2
- **Other deps:** libmodplug
- **Size:** ~45 files
- **Build:** Makefile
- **Notes:** Three games in one engine, by the REminiscence author (cyxx).

### Heart of Darkness (hode)
- **Repo:** https://github.com/cyxx/hode
- **Language:** C++ (pre-C++11)
- **SDL2 deps:** SDL2 only
- **Size:** ~52 files
- **Build:** Makefile
- **Notes:** By Eric Chahi (Another World creator). Visually spectacular hand-animated game.

### OpenSupaplex (Supaplex)
- **Repo:** https://github.com/sergiou87/open-supaplex
- **Language:** Pure C
- **SDL2 deps:** SDL2 only
- **Size:** ~60 files
- **Build:** CMake
- **Notes:** Zero external deps. Already ported to many retro platforms (PSP, Vita, Switch, 3DS).

## Tier 3: More Candidates (from second research round)

### Cosmo-Engine (Cosmo's Cosmic Adventure)
- **Repo:** https://github.com/yuv422/cosmo-engine
- **Language:** Pure C
- **SDL2 deps:** SDL2, SDL_mixer
- **Size:** ~217 commits, small
- **Data:** Original Cosmo game files
- **Notes:** Tiny codebase, classic Apogee platformer (1992). Easy quick win.

### Raptor (Call of the Shadows)
- **Repo:** https://github.com/skynettx/raptor
- **Language:** C (88%), some C++ (10%)
- **SDL2 deps:** SDL2
- **Size:** ~283 commits
- **Data:** Original Raptor GLB files (shareware or full)
- **Notes:** Reverse-engineered DOS shmup. The 10% C++ needs checking.

### SDL Sopwith
- **Repo:** https://github.com/fragglet/sdl-sopwith
- **Language:** C (91.5%)
- **SDL2 deps:** SDL2 only
- **Size:** Small
- **Data:** Self-contained (no data files needed)
- **Notes:** Classic bi-plane shooter. Self-contained, easy test candidate.

### DDWolf (Wolfenstein 3D)
- **Language:** C
- **SDL2 deps:** SDL2, SDL2_mixer
- **Data:** Original Wolf3D data files
- **Notes:** Wolfenstein 3D with SDL2 backend. Software renderer.

### Cannonball (OutRun)
- **Repo:** https://github.com/djyt/cannonball
- **Language:** C++11
- **SDL2 deps:** SDL2, Boost
- **Data:** Original OutRun arcade ROMs
- **Notes:** OutRun on 68k! Boost dependency is problematic. Original ran on 68000 hardware.

### OpenJazz (Jazz Jackrabbit)
- **Repo:** https://github.com/AlisterT/openjazz
- **Language:** C++14
- **SDL2 deps:** SDL2 only
- **Data:** Original Jazz Jackrabbit data files
- **Notes:** Minimal dependencies. C++14 is at the limit of GCC 6.5.

### Simutrans (Transport Tycoon)
- **Repo:** https://github.com/simutrans/simutrans
- **Language:** C++14 (C++17 only for Steam)
- **SDL2 deps:** SDL2
- **Other deps:** zlib, libpng, bzip2, freetype
- **Size:** 408 .cc files
- **Amiga port:** OS4 only (PPC), no 68k
- **Notes:** Makefile already has OSTYPE=amiga. Needs libpng + bzip2 cross-compiled. Most ambitious candidate.

### Angband (roguelike)
- **Repo:** https://github.com/angband/angband
- **Language:** C (93.5%)
- **SDL2 deps:** SDL2, SDL2_ttf, SDL2_image, SDL2_mixer
- **Size:** Large (10k+ commits)
- **Data:** Self-contained
- **Notes:** Classic roguelike. SDL2 is one of several frontends. Heavy SDL2 addon deps.

### UQM (Ur-Quan Masters / Star Control II)
- **Repo:** https://github.com/keylimesoda/sc2-uqm
- **Language:** C (94.6%)
- **SDL2 deps:** SDL2, libogg, libvorbis, libpng
- **Data:** Free content packs available
- **Notes:** One of the greatest games ever. Pure C. Free content. Worth investigating despite deps.

### Chocolate Quake
- **Repo:** https://github.com/Henrique194/chocolate-quake
- **Language:** C99
- **SDL2 deps:** SDL2, SDL2_net, libvorbis, libflac, libmad
- **Data:** Quake PAK files
- **Notes:** Pure software renderer. Would be very slow on 68k but iconic.

### C-Dogs SDL
- **Repo:** https://github.com/cxong/cdogs-sdl
- **Language:** C (gnu99)
- **SDL2 deps:** SDL2, SDL2_mixer, ENet
- **Size:** Large (4.4k commits)
- **Data:** Self-contained
- **Notes:** Overhead run-and-gun. Editor needs OpenGL but game doesn't.

## Already On Amiga (don't duplicate)

| Game | Port | Notes |
|------|------|-------|
| OpenDUNE (Dune II) | Aminet: OpenDUNE_RTG, OpenDUNE_AGA | By Novacoder, requires 68040+ |
| Dethrace (Carmageddon) | os4depot + 68k | By BSzili, using dethrace 0.8 |

## Rejected

| Game | Reason |
|------|--------|
| fheroes2 (HoMM2) | C++17. GCC 15 libstdc++ broken |
| Commander Genius | C++17 required |
| Hurrican (Turrican) | C++17 + OpenGL |
| DevilutionX (Diablo) | C++20 required |
| RigelEngine (Duke Nukem II) | C++17 required |
| FreeOrion | C++17, Boost, OpenGL |
| OpenMW (Morrowind) | Massive codebase |
| Exult (Ultima 7) | C++17 required |
| CorsixTH (Theme Hospital) | C++17 required |
| OpenTTD (Transport Tycoon) | C++17 required |
| GemRB (Baldur's Gate) | OpenGL required |
| Abuse (1996) | OpenGL required |
| Stratagus/Wargus (Warcraft) | C++17 required |

## Already Ported (by us)

| Game | Language | Status |
|------|----------|--------|
| [1oom](1oom/) (Master of Orion 1) | C99 | Running, ~43 FPS, no audio |
| [Chocolate Doom](chocolate-doom/) | C | Running, with sound |
| [ccleste](ccleste/) (Celeste Classic) | C | Running, no audio |
| [Julius](julius/) (Caesar III) | C99 | Running, no audio |
