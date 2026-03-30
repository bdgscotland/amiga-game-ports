/* os.c -- AmigaOS 3.x platform layer for 1oom */
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os.h"
#include "options.h"
#include "lib.h"
#include "util.h"
#include "types.h"

/* -------------------------------------------------------------------------- */

const struct cmdline_options_s os_cmdline_options[] = {
    { NULL, 0, NULL, NULL, NULL, NULL }
};

/* -------------------------------------------------------------------------- */

#define NUM_ALL_DATA_PATHS 16

static char *data_path = NULL;
static char *user_path = NULL;
static char *all_data_paths[NUM_ALL_DATA_PATHS] = {NULL};
static int num_data_paths = 0;

/* -------------------------------------------------------------------------- */

const char *idstr_os = "amigaos3";

int os_early_init(void)
{
    return 0;
}

int os_init(void)
{
    return 0;
}

void os_shutdown(void)
{
    lib_free(user_path);
    user_path = NULL;
    lib_free(data_path);
    data_path = NULL;
    for (int i = 0; i < num_data_paths; ++i) {
        lib_free(all_data_paths[i]);
        all_data_paths[i] = NULL;
    }
    num_data_paths = 0;
}

const char **os_get_paths_data(void)
{
    if (num_data_paths == 0) {
        int i = 0;
        if (data_path) {
            all_data_paths[i++] = lib_stralloc(data_path);
        }
        /* PROGDIR: is the directory where the binary lives */
        all_data_paths[i++] = lib_stralloc("PROGDIR:data");
        all_data_paths[i++] = lib_stralloc("PROGDIR:");
        /* current directory */
        all_data_paths[i++] = lib_stralloc(".");
        all_data_paths[i++] = lib_stralloc("data");
        all_data_paths[i] = NULL;
        num_data_paths = i;
    }
    return (const char **)all_data_paths;
}

const char *os_get_path_data(void)
{
    return data_path;
}

void os_set_path_data(const char *path)
{
    if (data_path) {
        lib_free(data_path);
        data_path = NULL;
    }
    data_path = lib_stralloc(path);
}

const char *os_get_path_user(void)
{
    if (user_path == NULL) {
        user_path = lib_stralloc("PROGDIR:");
    }
    return user_path;
}

void os_set_path_user(const char *path)
{
    if (user_path) {
        lib_free(user_path);
        user_path = NULL;
    }
    user_path = lib_stralloc(path);
}

int os_make_path(const char *path)
{
    /* AmigaOS paths -- just check if it works, don't try to mkdir */
    (void)path;
    return 0;
}

int os_make_path_user(void)
{
    return os_make_path(os_get_path_user());
}

int os_make_path_for(const char *filename)
{
    (void)filename;
    return 0;
}

const char *os_get_fname_save_slot(char *buf, size_t bufsize, int savei)
{
    return NULL;
}

const char *os_get_fname_save_year(char *buf, size_t bufsize, int year)
{
    return NULL;
}

const char *os_get_fname_cfg(char *buf, size_t bufsize, const char *gamestr, const char *uistr, const char *hwstr)
{
    return NULL;
}

const char *os_get_fname_log(char *buf, size_t bufsize)
{
    if (buf) {
        lib_strcpy(buf, "1oom_log.txt", bufsize);
        return buf;
    }
    return "1oom_log.txt";
}
