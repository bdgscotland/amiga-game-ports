/* AmigaOS 3.x paths implementation for Vanilla Conquer
 * Replaces paths_posix.cpp -- uses PROGDIR: for program path,
 * current directory for data, T: for temp.
 */
#include "paths.h"
#include "debugstring.h"
#include <cstring>
#include <cstdlib>

const char* PathsClass::Program_Path()
{
    if (ProgramPath.empty()) {
        /* PROGDIR: is set by AmigaOS to the directory containing
         * the running executable. */
        ProgramPath = "PROGDIR:";
    }
    return ProgramPath.c_str();
}

const char* PathsClass::Data_Path()
{
    if (DataPath.empty()) {
        /* Data files live alongside the executable on Amiga */
        DataPath = "PROGDIR:";

        if (!Suffix.empty()) {
            DataPath += Suffix;
        }
    }
    return DataPath.c_str();
}

const char* PathsClass::User_Path()
{
    if (UserPath.empty()) {
        /* Save games and config in PROGDIR: (no XDG on Amiga) */
        UserPath = "PROGDIR:";

        if (!Suffix.empty()) {
            UserPath += Suffix;
        }

        Create_Directory(UserPath.c_str());
    }
    return UserPath.c_str();
}

/* libnix provides mkdir() */
extern "C" int mkdir(const char*, int);

bool PathsClass::Create_Directory(const char* dirname)
{
    /* AmigaOS mkdir via libnix -- just attempt it, ignore EEXIST */
    if (dirname == NULL) {
        return true;
    }
    mkdir(dirname, 0);
    return true;
}

bool PathsClass::Is_Absolute(const char* path)
{
    if (path == NULL) {
        return false;
    }
    /* Amiga absolute paths contain ':' (volume:path) */
    return strchr(path, ':') != NULL;
}

std::string PathsClass::Concatenate_Paths(const char* path1, const char* path2)
{
    std::string result(path1);
    if (!result.empty()) {
        char last = result[result.length() - 1];
        /* Amiga path separators: '/' and ':' */
        if (last != '/' && last != ':') {
            result += '/';
        }
    }
    result += path2;
    return result;
}

std::string PathsClass::Get_Filename(const char* path)
{
    if (path == NULL) {
        return std::string();
    }
    /* Find last separator (/ or :) */
    const char* sep = strrchr(path, '/');
    const char* col = strrchr(path, ':');
    if (col > sep) {
        sep = col;
    }
    if (sep != NULL) {
        return std::string(sep + 1);
    }
    return std::string(path);
}

std::string PathsClass::Argv_Path(const char* cmd_arg)
{
    /* On AmigaOS, argv[0] is just the program name, not a full path.
     * PROGDIR: is the canonical way to find the executable. */
    return std::string("PROGDIR:");
}
