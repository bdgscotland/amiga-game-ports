# Vanilla Conquer - Tiberian Dawn for AmigaOS 3.x
# Cross-compile via bebbo-gcc in Docker

DOCKER_IMAGE = amigadev/crosstools:m68k-amigaos
SDL2_DIR     = /work/libSDL2-amigaos3
UPSTREAM     = /work/amiga-game-ports/vanilla-conquer-upstream
SHIMS        = /work/amiga-game-ports/vanilla-conquer/amiga_shims
BUILDDIR     = /work/amiga-game-ports/vanilla-conquer/obj

# Mount the parent of amiga-game-ports so we can reach libSDL2 too
DOCKER_RUN = docker run --rm \
  -v $(HOME)/Developer:/work \
  -w /work/amiga-game-ports/vanilla-conquer \
  $(DOCKER_IMAGE)

CXX = m68k-amigaos-g++
LD  = m68k-amigaos-g++

CXXFLAGS_BASE = -std=c++11 -m68020 -fno-exceptions -fno-rtti -fpermissive \
           -fno-strict-aliasing \
           -DTRUE_FALSE_DEFINED -DENGLISH -DMEGAMAPS \
           -DSDL_BUILD -DSDL2_BUILD -DNEW_VIDEO_BUILD \
           -I$(SHIMS) -include amiga_compat.h \
           -I$(UPSTREAM)/common \
           -I$(UPSTREAM)/tiberiandawn \
           -I$(UPSTREAM) \
           -I$(SDL2_DIR)/include

# Default optimization: -O2 for speed, -O0 for safety
OPT_DEFAULT = -O2

# Files that MUST be compiled at -O0 (bebbo-gcc codegen bugs).
# Binary search: move files between O0_FILES and O2 to find which break terrain.
# bebbo-gcc -O2 codegen bugs: these files MUST stay at -O0
# cdata.cpp: terrain template data corrupted at -O2 (binary searched 2026-03-31)
O0_FILES = cdata.cpp

CXXFLAGS = $(CXXFLAGS_BASE) $(OPT_DEFAULT)
CXXFLAGS_O0 = $(CXXFLAGS_BASE) -O0

LDFLAGS = -m68020 -noixemul
LIBS = $(SDL2_DIR)/libSDL2.a -lm

TARGET = vanillatd

# ============================================================
# Common library sources (non-platform, non-video)
# ============================================================
COMMON_BASE = \
  $(UPSTREAM)/common/_diptabl.cpp \
  $(UPSTREAM)/common/alloc.cpp \
  $(UPSTREAM)/common/auduncmp.cpp \
  $(UPSTREAM)/common/b64pipe.cpp \
  $(UPSTREAM)/common/b64straw.cpp \
  $(UPSTREAM)/common/base64.cpp \
  $(UPSTREAM)/common/bfiofile.cpp \
  $(UPSTREAM)/common/blowfish.cpp \
  $(UPSTREAM)/common/blowpipe.cpp \
  $(UPSTREAM)/common/blwstraw.cpp \
  $(UPSTREAM)/common/buff.cpp \
  $(UPSTREAM)/common/buffer.cpp \
  $(UPSTREAM)/common/buffglbl.cpp \
  $(UPSTREAM)/common/ccfile.cpp \
  $(UPSTREAM)/common/cdfile.cpp \
  $(UPSTREAM)/common/cliprect.cpp \
  $(UPSTREAM)/common/combuf.cpp \
  $(UPSTREAM)/common/control.cpp \
  $(UPSTREAM)/common/crc.cpp \
  $(UPSTREAM)/common/crew.cpp \
  $(UPSTREAM)/common/cstraw.cpp \
  $(UPSTREAM)/common/debugstring.cpp \
  $(UPSTREAM)/common/delay.cpp \
  $(UPSTREAM)/common/dipthong.cpp \
  $(UPSTREAM)/common/drawbuff.cpp \
  $(UPSTREAM)/common/drawline.cpp \
  $(UPSTREAM)/common/drawmisc.cpp \
  $(UPSTREAM)/common/face.cpp \
  $(UPSTREAM)/common/fading.cpp \
  $(UPSTREAM)/common/field.cpp \
  $(UPSTREAM)/common/file.cpp \
  $(UPSTREAM)/common/filepcx.cpp \
  $(UPSTREAM)/common/fixed.cpp \
  $(UPSTREAM)/common/font.cpp \
  $(UPSTREAM)/common/gadget.cpp \
  $(UPSTREAM)/common/getshape.cpp \
  $(UPSTREAM)/common/graphicsviewport.cpp \
  $(UPSTREAM)/common/hsv.cpp \
  $(UPSTREAM)/common/iff.cpp \
  $(UPSTREAM)/common/ini.cpp \
  $(UPSTREAM)/common/int.cpp \
  $(UPSTREAM)/common/internet.cpp \
  $(UPSTREAM)/common/irandom.cpp \
  $(UPSTREAM)/common/keybuff.cpp \
  $(UPSTREAM)/common/keyframe.cpp \
  $(UPSTREAM)/common/lcw.cpp \
  $(UPSTREAM)/common/lcwpipe.cpp \
  $(UPSTREAM)/common/lcwstraw.cpp \
  $(UPSTREAM)/common/linear.cpp \
  $(UPSTREAM)/common/link.cpp \
  $(UPSTREAM)/common/load.cpp \
  $(UPSTREAM)/common/memrev.cpp \
  $(UPSTREAM)/common/misc.cpp \
  $(UPSTREAM)/common/mixfile.cpp \
  $(UPSTREAM)/common/mp.cpp \
  $(UPSTREAM)/common/newdel.cpp \
  $(UPSTREAM)/common/packet.cpp \
  $(UPSTREAM)/common/palette.cpp \
  $(UPSTREAM)/common/palettec.cpp \
  $(UPSTREAM)/common/paths.cpp \
  $(UPSTREAM)/common/pipe.cpp \
  $(UPSTREAM)/common/pk.cpp \
  $(UPSTREAM)/common/pkpipe.cpp \
  $(UPSTREAM)/common/pkstraw.cpp \
  $(UPSTREAM)/common/ramfile.cpp \
  $(UPSTREAM)/common/random.cpp \
  $(UPSTREAM)/common/rawfile.cpp \
  $(UPSTREAM)/common/readline.cpp \
  $(UPSTREAM)/common/rect.cpp \
  $(UPSTREAM)/common/rgb.cpp \
  $(UPSTREAM)/common/rndstraw.cpp \
  $(UPSTREAM)/common/settings.cpp \
  $(UPSTREAM)/common/sha.cpp \
  $(UPSTREAM)/common/shape.cpp \
  $(UPSTREAM)/common/shapipe.cpp \
  $(UPSTREAM)/common/shastraw.cpp \
  $(UPSTREAM)/common/soscodec.cpp \
  $(UPSTREAM)/common/stamp.cpp \
  $(UPSTREAM)/common/straw.cpp \
  $(UPSTREAM)/common/timer.cpp \
  $(UPSTREAM)/common/timerdwn.cpp \
  $(UPSTREAM)/common/tobuff.cpp \
  $(UPSTREAM)/common/toggle.cpp \
  $(UPSTREAM)/common/vector.cpp \
  $(UPSTREAM)/common/winasm.cpp \
  $(UPSTREAM)/common/windows.cpp \
  $(UPSTREAM)/common/winhide.cpp \
  $(UPSTREAM)/common/winstub.cpp \
  $(UPSTREAM)/common/wsa.cpp \
  $(UPSTREAM)/common/xordelta.cpp \
  $(UPSTREAM)/common/xpipe.cpp \
  $(UPSTREAM)/common/xstraw.cpp

# Video/audio/input sources for vanilla SDL2 build
COMMON_VIDEO = \
  $(UPSTREAM)/common/framelimit.cpp \
  $(UPSTREAM)/common/gbuffer.cpp \
  $(UPSTREAM)/common/interpal.cpp \
  $(UPSTREAM)/common/soundio_null.cpp \
  $(UPSTREAM)/common/vqaaudio_null.cpp \
  $(UPSTREAM)/common/video_sdl2.cpp \
  $(UPSTREAM)/common/wwkeyboard.cpp \
  $(UPSTREAM)/common/wwkeyboard_sdl2.cpp \
  $(UPSTREAM)/common/wwmouse.cpp \
  $(UPSTREAM)/common/unvqbuff.cpp \
  $(UPSTREAM)/common/vqaconfig.cpp \
  $(UPSTREAM)/common/vqadrawer.cpp \
  $(UPSTREAM)/common/vqaloader.cpp \
  $(UPSTREAM)/common/vqapalette.cpp \
  $(UPSTREAM)/common/vqatask.cpp \
  $(UPSTREAM)/common/vqaver.cpp

# AmigaOS shims (replace POSIX-specific files)
AMIGA_SHIMS = \
  $(SHIMS)/paths_amiga.cpp \
  $(SHIMS)/file_amiga.cpp \
  $(SHIMS)/gitinfo.cpp

# ============================================================
# Tiberian Dawn game sources
# ============================================================
TIBDAWN = \
  $(UPSTREAM)/tiberiandawn/aadata.cpp \
  $(UPSTREAM)/tiberiandawn/abstract.cpp \
  $(UPSTREAM)/tiberiandawn/adata.cpp \
  $(UPSTREAM)/tiberiandawn/aircraft.cpp \
  $(UPSTREAM)/tiberiandawn/anim.cpp \
  $(UPSTREAM)/tiberiandawn/audio.cpp \
  $(UPSTREAM)/tiberiandawn/base.cpp \
  $(UPSTREAM)/tiberiandawn/bbdata.cpp \
  $(UPSTREAM)/tiberiandawn/bdata.cpp \
  $(UPSTREAM)/tiberiandawn/building.cpp \
  $(UPSTREAM)/tiberiandawn/bullet.cpp \
  $(UPSTREAM)/tiberiandawn/cargo.cpp \
  $(UPSTREAM)/tiberiandawn/ccini.cpp \
  $(UPSTREAM)/tiberiandawn/cdata.cpp \
  $(UPSTREAM)/tiberiandawn/cell.cpp \
  $(UPSTREAM)/tiberiandawn/checkbox.cpp \
  $(UPSTREAM)/tiberiandawn/cheklist.cpp \
  $(UPSTREAM)/tiberiandawn/colrlist.cpp \
  $(UPSTREAM)/tiberiandawn/combat.cpp \
  $(UPSTREAM)/tiberiandawn/confdlg.cpp \
  $(UPSTREAM)/tiberiandawn/conquer.cpp \
  $(UPSTREAM)/tiberiandawn/const.cpp \
  $(UPSTREAM)/tiberiandawn/coord.cpp \
  $(UPSTREAM)/tiberiandawn/credits.cpp \
  $(UPSTREAM)/tiberiandawn/debug.cpp \
  $(UPSTREAM)/tiberiandawn/dial8.cpp \
  $(UPSTREAM)/tiberiandawn/dialog.cpp \
  $(UPSTREAM)/tiberiandawn/display.cpp \
  $(UPSTREAM)/tiberiandawn/door.cpp \
  $(UPSTREAM)/tiberiandawn/drive.cpp \
  $(UPSTREAM)/tiberiandawn/drop.cpp \
  $(UPSTREAM)/tiberiandawn/edit.cpp \
  $(UPSTREAM)/tiberiandawn/ending.cpp \
  $(UPSTREAM)/tiberiandawn/event.cpp \
  $(UPSTREAM)/tiberiandawn/expand.cpp \
  $(UPSTREAM)/tiberiandawn/facing.cpp \
  $(UPSTREAM)/tiberiandawn/factory.cpp \
  $(UPSTREAM)/tiberiandawn/findpath.cpp \
  $(UPSTREAM)/tiberiandawn/flasher.cpp \
  $(UPSTREAM)/tiberiandawn/fly.cpp \
  $(UPSTREAM)/tiberiandawn/foot.cpp \
  $(UPSTREAM)/tiberiandawn/fuse.cpp \
  $(UPSTREAM)/tiberiandawn/gamedlg.cpp \
  $(UPSTREAM)/tiberiandawn/gauge.cpp \
  $(UPSTREAM)/tiberiandawn/globals.cpp \
  $(UPSTREAM)/tiberiandawn/goptions.cpp \
  $(UPSTREAM)/tiberiandawn/gscreen.cpp \
  $(UPSTREAM)/tiberiandawn/hdata.cpp \
  $(UPSTREAM)/tiberiandawn/heap.cpp \
  $(UPSTREAM)/tiberiandawn/help.cpp \
  $(UPSTREAM)/tiberiandawn/house.cpp \
  $(UPSTREAM)/tiberiandawn/iconset.cpp \
  $(UPSTREAM)/tiberiandawn/idata.cpp \
  $(UPSTREAM)/tiberiandawn/infantry.cpp \
  $(UPSTREAM)/tiberiandawn/init.cpp \
  $(UPSTREAM)/tiberiandawn/intro.cpp \
  $(UPSTREAM)/tiberiandawn/iomap.cpp \
  $(UPSTREAM)/tiberiandawn/ioobj.cpp \
  $(UPSTREAM)/tiberiandawn/jshell.cpp \
  $(UPSTREAM)/tiberiandawn/layer.cpp \
  $(UPSTREAM)/tiberiandawn/lib.cpp \
  $(UPSTREAM)/tiberiandawn/list.cpp \
  $(UPSTREAM)/tiberiandawn/loaddlg.cpp \
  $(UPSTREAM)/tiberiandawn/logic.cpp \
  $(UPSTREAM)/tiberiandawn/map.cpp \
  $(UPSTREAM)/tiberiandawn/mapeddlg.cpp \
  $(UPSTREAM)/tiberiandawn/mapedit.cpp \
  $(UPSTREAM)/tiberiandawn/mapedplc.cpp \
  $(UPSTREAM)/tiberiandawn/mapedsel.cpp \
  $(UPSTREAM)/tiberiandawn/mapedtm.cpp \
  $(UPSTREAM)/tiberiandawn/mapsel.cpp \
  $(UPSTREAM)/tiberiandawn/menus.cpp \
  $(UPSTREAM)/tiberiandawn/miscasm.cpp \
  $(UPSTREAM)/tiberiandawn/mission.cpp \
  $(UPSTREAM)/tiberiandawn/monoc.cpp \
  $(UPSTREAM)/tiberiandawn/mouse.cpp \
  $(UPSTREAM)/tiberiandawn/mplayer.cpp \
  $(UPSTREAM)/tiberiandawn/msgbox.cpp \
  $(UPSTREAM)/tiberiandawn/msglist.cpp \
  $(UPSTREAM)/tiberiandawn/nulldlg.cpp \
  $(UPSTREAM)/tiberiandawn/object.cpp \
  $(UPSTREAM)/tiberiandawn/odata.cpp \
  $(UPSTREAM)/tiberiandawn/options.cpp \
  $(UPSTREAM)/tiberiandawn/overlay.cpp \
  $(UPSTREAM)/tiberiandawn/power.cpp \
  $(UPSTREAM)/tiberiandawn/profile.cpp \
  $(UPSTREAM)/tiberiandawn/queue.cpp \
  $(UPSTREAM)/tiberiandawn/radar.cpp \
  $(UPSTREAM)/tiberiandawn/radio.cpp \
  $(UPSTREAM)/tiberiandawn/reinf.cpp \
  $(UPSTREAM)/tiberiandawn/rules.cpp \
  $(UPSTREAM)/tiberiandawn/saveload.cpp \
  $(UPSTREAM)/tiberiandawn/scenario.cpp \
  $(UPSTREAM)/tiberiandawn/scenarioini.cpp \
  $(UPSTREAM)/tiberiandawn/score.cpp \
  $(UPSTREAM)/tiberiandawn/scroll.cpp \
  $(UPSTREAM)/tiberiandawn/sdata.cpp \
  $(UPSTREAM)/tiberiandawn/shapebtn.cpp \
  $(UPSTREAM)/tiberiandawn/sidebar.cpp \
  $(UPSTREAM)/tiberiandawn/slider.cpp \
  $(UPSTREAM)/tiberiandawn/smudge.cpp \
  $(UPSTREAM)/tiberiandawn/sounddlg.cpp \
  $(UPSTREAM)/tiberiandawn/special.cpp \
  $(UPSTREAM)/tiberiandawn/startup.cpp \
  $(UPSTREAM)/tiberiandawn/stats.cpp \
  $(UPSTREAM)/tiberiandawn/super.cpp \
  $(UPSTREAM)/tiberiandawn/tab.cpp \
  $(UPSTREAM)/tiberiandawn/tarcom.cpp \
  $(UPSTREAM)/tiberiandawn/target.cpp \
  $(UPSTREAM)/tiberiandawn/tdata.cpp \
  $(UPSTREAM)/tiberiandawn/team.cpp \
  $(UPSTREAM)/tiberiandawn/teamtype.cpp \
  $(UPSTREAM)/tiberiandawn/techno.cpp \
  $(UPSTREAM)/tiberiandawn/template.cpp \
  $(UPSTREAM)/tiberiandawn/terrain.cpp \
  $(UPSTREAM)/tiberiandawn/textbtn.cpp \
  $(UPSTREAM)/tiberiandawn/theme.cpp \
  $(UPSTREAM)/tiberiandawn/trigger.cpp \
  $(UPSTREAM)/tiberiandawn/turret.cpp \
  $(UPSTREAM)/tiberiandawn/txtlabel.cpp \
  $(UPSTREAM)/tiberiandawn/udata.cpp \
  $(UPSTREAM)/tiberiandawn/unit.cpp \
  $(UPSTREAM)/tiberiandawn/visudlg.cpp \
  $(UPSTREAM)/tiberiandawn/winstub.cpp

ALL_SRCS = $(COMMON_BASE) $(COMMON_VIDEO) $(AMIGA_SHIMS) $(TIBDAWN)

# mssleep_amiga.h must be found before the upstream mssleep.h
# Added to BASE so both CXXFLAGS and CXXFLAGS_O0 get it
CXXFLAGS_BASE += -include $(SHIMS)/mssleep_amiga.h

# Object files go into obj/ with flat names to avoid path conflicts
OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(notdir $(ALL_SRCS)))

# VPATH for finding sources
VPATH = $(UPSTREAM)/common:$(UPSTREAM)/tiberiandawn:$(SHIMS)

.PHONY: all clean compile-test

all: $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Compile inside Docker
# Object files are prefixed with directory name to avoid collisions
# (e.g. common/winstub.cpp -> obj/common_winstub.o)
$(TARGET):
	$(DOCKER_RUN) sh -c '\
		mkdir -p obj && \
		echo "=== Compiling Vanilla Conquer (Tiberian Dawn) ===" && \
		echo "=== Default: $(OPT_DEFAULT), O0 overrides: $(words $(O0_FILES)) files ===" && \
		PASS=0 && FAIL=0 && O0_COUNT=0 && \
		O0_LIST=" $(O0_FILES) " && \
		for f in $(ALL_SRCS); do \
			DIR=$$(basename $$(dirname $$f)) && \
			BASE=$$(basename $${f%.cpp}) && \
			OBJ=obj/$${DIR}_$${BASE}.o && \
			FNAME=$$(basename $$f) && \
			FLAGS="$(CXXFLAGS)" && \
			case "$$O0_LIST" in \
				*" $$FNAME "*) FLAGS="$(CXXFLAGS_O0)"; O0_COUNT=$$((O0_COUNT + 1));; \
			esac && \
			$(CXX) $$FLAGS -c $$f -o $$OBJ 2>&1 | tail -5 && \
			if [ $$? -eq 0 ]; then \
				PASS=$$((PASS + 1)); \
			else \
				echo "FAIL: $$f"; \
				FAIL=$$((FAIL + 1)); \
			fi; \
		done && \
		echo "" && \
		echo "=== Compile: $$PASS passed, $$FAIL failed ($$O0_COUNT at -O0) ===" && \
		if [ $$FAIL -eq 0 ]; then \
			echo "=== Linking ===" && \
			$(LD) $(LDFLAGS) obj/*.o -o $(TARGET) $(LIBS) 2>&1 | grep -v "ms_struct" | head -40; \
		else \
			echo "Skipping link due to compile errors"; \
		fi'

# Quick compile test - just compile, count pass/fail
compile-test:
	$(DOCKER_RUN) sh -c '\
		mkdir -p obj && \
		PASS=0 && FAIL=0 && \
		for f in $(ALL_SRCS); do \
			DIR=$$(basename $$(dirname $$f)) && \
			BASE=$$(basename $${f%.cpp}) && \
			OBJ=obj/$${DIR}_$${BASE}.o && \
			if $(CXX) $(CXXFLAGS) -c $$f -o $$OBJ 2>/dev/null; then \
				PASS=$$((PASS + 1)); \
			else \
				echo "FAIL: $$f"; \
				$(CXX) $(CXXFLAGS) -c $$f -o $$OBJ 2>&1 | grep "error:" | head -1; \
				FAIL=$$((FAIL + 1)); \
			fi; \
		done && \
		echo "" && \
		echo "=== Results: $$PASS passed, $$FAIL failed ==="'

clean:
	rm -rf obj $(TARGET)
