/* AmigaOS 3.x file enumeration for Vanilla Conquer
 * Replaces file_posix.cpp -- uses dos.library ExNext() for directory scanning.
 * No dirent.h or fnmatch.h needed.
 */
#include "file.h"

#include <proto/dos.h>
#include <proto/exec.h>

/* proto/dos.h defines Close as a macro/inline that conflicts
   with our Find_File_Data::Close() virtual method */
#undef Close

#include <string.h>

/* Simple case-insensitive wildcard match (supports * and ?) */
static bool WildcardMatch(const char* pattern, const char* str)
{
    while (*pattern) {
        if (*pattern == '*') {
            pattern++;
            if (*pattern == '\0') {
                return true;
            }
            while (*str) {
                if (WildcardMatch(pattern, str)) {
                    return true;
                }
                str++;
            }
            return false;
        } else if (*pattern == '?') {
            if (*str == '\0') {
                return false;
            }
            pattern++;
            str++;
        } else {
            /* Case-insensitive compare */
            char pc = *pattern;
            char sc = *str;
            if (pc >= 'A' && pc <= 'Z') pc += 32;
            if (sc >= 'A' && sc <= 'Z') sc += 32;
            if (pc != sc) {
                return false;
            }
            pattern++;
            str++;
        }
    }
    return *str == '\0';
}

class Find_File_Data_Amiga : public Find_File_Data
{
public:
    Find_File_Data_Amiga();
    virtual ~Find_File_Data_Amiga();

    virtual const char* GetName() const;
    virtual const char* GetFullName() const
    {
        return FullName[0] ? FullName : NULL;
    }
    virtual unsigned int GetTime() const;

    virtual bool FindFirst(const char* fname);
    virtual bool FindNext();
    virtual void Close();

private:
    BPTR DirLock;
    struct FileInfoBlock* Fib;
    char FileFilter[108];
    char FullName[256];
    char DirName[256];
    bool Active;

    bool MatchesFilter();
};

Find_File_Data_Amiga::Find_File_Data_Amiga()
    : DirLock(0)
    , Fib(NULL)
    , Active(false)
{
    FullName[0] = '\0';
    DirName[0] = '\0';
    FileFilter[0] = '\0';
}

Find_File_Data_Amiga::~Find_File_Data_Amiga()
{
    Close();
}

const char* Find_File_Data_Amiga::GetName() const
{
    if (!Active || Fib == NULL) {
        return NULL;
    }
    return Fib->fib_FileName;
}

unsigned int Find_File_Data_Amiga::GetTime() const
{
    if (!Active || Fib == NULL) {
        return 0;
    }
    /* Convert Amiga DateStamp to a comparable timestamp */
    return (unsigned int)(Fib->fib_Date.ds_Days * 86400
                          + Fib->fib_Date.ds_Minute * 60
                          + Fib->fib_Date.ds_Tick / 50);
}

bool Find_File_Data_Amiga::MatchesFilter()
{
    if (Fib == NULL) {
        return false;
    }
    /* Skip directories */
    if (Fib->fib_DirEntryType > 0) {
        return false;
    }
    return WildcardMatch(FileFilter, Fib->fib_FileName);
}

bool Find_File_Data_Amiga::FindFirst(const char* fname)
{
    Close();

    /* Split directory and filename pattern */
    const char* sep = strrchr(fname, '/');
    const char* col = strrchr(fname, ':');
    if (col > sep) {
        sep = col;
    }

    if (sep != NULL) {
        int dirlen = (int)(sep - fname + 1);
        if (dirlen >= (int)sizeof(DirName)) {
            dirlen = sizeof(DirName) - 1;
        }
        strncpy(DirName, fname, dirlen);
        DirName[dirlen] = '\0';
        strncpy(FileFilter, sep + 1, sizeof(FileFilter) - 1);
        FileFilter[sizeof(FileFilter) - 1] = '\0';
    } else {
        DirName[0] = '\0';
        strncpy(FileFilter, fname, sizeof(FileFilter) - 1);
        FileFilter[sizeof(FileFilter) - 1] = '\0';
    }

    /* Lock the directory */
    const char* dir = DirName[0] ? DirName : "PROGDIR:";
    DirLock = Lock((CONST_STRPTR)dir, ACCESS_READ);
    if (DirLock == 0) {
        return false;
    }

    /* Allocate FileInfoBlock (must be longword aligned) */
    Fib = (struct FileInfoBlock*)AllocDosObject(DOS_FIB, NULL);
    if (Fib == NULL) {
        UnLock(DirLock);
        DirLock = 0;
        return false;
    }

    if (!Examine(DirLock, Fib)) {
        FreeDosObject(DOS_FIB, Fib);
        Fib = NULL;
        UnLock(DirLock);
        DirLock = 0;
        return false;
    }

    /* Scan for first matching entry */
    Active = true;
    while (ExNext(DirLock, Fib)) {
        if (MatchesFilter()) {
            /* Build full name */
            strncpy(FullName, DirName, sizeof(FullName) - 1);
            strncat(FullName, Fib->fib_FileName,
                    sizeof(FullName) - strlen(FullName) - 1);
            return true;
        }
    }

    Active = false;
    return false;
}

bool Find_File_Data_Amiga::FindNext()
{
    if (!Active || DirLock == 0 || Fib == NULL) {
        return false;
    }

    while (ExNext(DirLock, Fib)) {
        if (MatchesFilter()) {
            strncpy(FullName, DirName, sizeof(FullName) - 1);
            strncat(FullName, Fib->fib_FileName,
                    sizeof(FullName) - strlen(FullName) - 1);
            return true;
        }
    }

    Active = false;
    return false;
}

void Find_File_Data_Amiga::Close()
{
    if (Fib != NULL) {
        FreeDosObject(DOS_FIB, Fib);
        Fib = NULL;
    }
    if (DirLock != 0) {
        UnLock(DirLock);
        DirLock = 0;
    }
    Active = false;
    FullName[0] = '\0';
}

Find_File_Data* Find_File_Data::CreateFindData()
{
    return new Find_File_Data_Amiga();
}
