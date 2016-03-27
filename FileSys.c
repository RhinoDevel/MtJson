
// MT, 2016mar19

#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "Deb.h"
#include "FileSys.h"

static char const * const _dir_separator = "/";

char * FileSys_GetFullPath(char const * const inPath, char const * const inName)
{
    assert((inPath!=NULL)&&(inPath[0]!='\0'));
    assert((inName!=NULL)&&(inName[0]!='\0'));

    char * retVal = NULL;
    size_t const folderPathLen = strlen(inPath),
        pathLen = (folderPathLen+1+strlen(inName)+1)*(sizeof *retVal);

    retVal = malloc(pathLen);
    assert(retVal!=NULL);

    retVal[0] = '\0';
    strlcat(retVal, inPath, pathLen);
    strlcat(retVal, _dir_separator, pathLen);
    strlcat(retVal, inName, pathLen);

    return retVal;
}

char * FileSys_GetAbsPath(char const * const inPath)
{
    char * retVal = malloc(PATH_MAX*(sizeof *retVal));

    assert(retVal!=NULL);

    if(realpath(inPath, retVal)==NULL)
    {
        free(retVal);
        retVal = NULL;
    }

    return retVal;
}

enum FileSys_EntryType FileSys_GetEntryType(char const * const inPath)
{
    enum FileSys_EntryType retVal = FileSys_EntryType_Invalid;
    struct stat s;

    assert(inPath!=NULL);

    if(lstat(inPath, &s)==0) // Because entry->d_type may not work on all platforms.
    {
        if(S_ISDIR(s.st_mode))
        {
            retVal = FileSys_EntryType_Dir;
        }
        else
        {
            if(S_ISREG(s.st_mode))
            {
                retVal = FileSys_EntryType_File;
            }
            else // Add more types, here..
            {
                retVal = FileSys_EntryType_Unsupported;
            }
        }
    }
    else
    {
        Deb_line("lstat() ERROR: %d!", errno);
        errno = 0;
    }

    return retVal;
}

/** Source: http://stackoverflow.com/questions/8236/how-do-you-determine-the-size-of-a-file-in-c
 */
off_t FileSys_GetFileSize(char const * const inPath)
{
    struct stat s;

    assert(inPath!=NULL);

    if(stat(inPath, &s)==0)
    {
        return s.st_size; // *** RETURN ***
    }

    return -1;
}

bool FileSys_arePathsToSameFile(char const * const inA, char const * const inB, bool * const inOutSame)
{
    bool retVal = true; // Indicates no error (true = no error).
    struct stat sA;

    assert(inA!=NULL);
    assert(inB!=NULL);
    assert(inOutSame!=NULL);

    *inOutSame = false;

    if(lstat(inA, &sA)==0)
    {
        struct stat sB;

        if(lstat(inB, &sB)==0)
        {
            assert(sA.st_ino!=0);
            assert(sA.st_dev!=0);
            assert(sB.st_ino!=0);
            assert(sB.st_dev!=0);

            if((sA.st_dev==sB.st_dev)&&(sA.st_ino==sB.st_ino))
            {
                *inOutSame = true;
            }
            //
            // Otherwise: Different files.
        }
        else
        {
            Deb_line("lstat() ERROR: %d!", errno);
            errno = 0;
            retVal = false; // Error!
        }
    }
    else
    {
        Deb_line("lstat() ERROR: %d!", errno);
        errno = 0;
        retVal = false; // Error!
    }

    return retVal;
}

bool FileSys_exists(char const * const inPath, bool * const inOutExists)
{
    bool retVal = true; // Indicates no error (true = no error).
    struct stat s;

    assert(inPath!=NULL);
    assert(inOutExists!=NULL);

    *inOutExists = false;

    if(lstat(inPath, &s)==0)
    {
        *inOutExists = true;
    }
    else
    {
        if(errno!=ENOENT)
        {
            Deb_line("lstat() ERROR: %d!", errno);
            retVal = false; // Unexpected error!
        }
        //
        // Otherwise: Does not exist.

        errno = 0;
    }

    return retVal;
}

/** Original source: http://stackoverflow.com/questions/6383584/check-if-a-directory-is-empty-using-c-on-linux
 */
bool FileSys_isDirEmpty(char const * const inPath, bool * const inOutEmpty)
{
    bool retVal = true; // Indicates no error (true = no error).
    DIR* d = NULL;

    assert(inPath!=NULL);
    assert(inOutEmpty!=NULL);

    *inOutEmpty = false;

    d = opendir(inPath);
    if(d!=NULL)
    {
        int n = 0;
        struct dirent * e = readdir(d);

        while(e!=NULL)
        {
            ++n;
            if(n==3) // "." & ".." are OK to be found as "entries" of an empty array.
            {
                break;
            }

            e = readdir(d);
        }
        if(errno==0)
        {
            if(n<3)
            {
                *inOutEmpty = true;
            }
        }
        else
        {
            Deb_line("readdir() ERROR: %d!", errno);
            errno = 0;
            retVal = false;
        }

        closedir(d); // (return value ignored..)
        errno = 0;
        d = NULL;
    }
    else
    {
        Deb_line("opendir() ERROR: %d!", errno);
        errno = 0;
        retVal = false;
    }

    return retVal;
}

bool FileSys_delete(char const * const inPath)
{
    bool retVal = false;

    switch(FileSys_GetEntryType(inPath))
    {
        case FileSys_EntryType_File:
            if(unlink(inPath)==0)
            {
                retVal = true;
            }
#ifndef NDEBUG
            else
            {
                Deb_line("Error: Failed to remove file \"%s\" (error %d)!", inPath, errno);
            }
#endif //NDEBUG
            errno = 0;
            break;

        case FileSys_EntryType_Dir:
        {
            DIR * const d = opendir(inPath);

            if(d!=NULL)
            {
                bool errOcc = false;
                struct dirent * e = readdir(d);

                while(e!=NULL)
                {
                    if((strcmp(e->d_name, ".")!=0)&&(strcmp(e->d_name, "..")!=0))
                    {
                        char * const fullPath = FileSys_GetFullPath(inPath, e->d_name);

                        if(!FileSys_delete(fullPath)) // *** RECURSION ***
                        {
                            errOcc = true;
                            free(fullPath);
                            break;
                        }
                        free(fullPath);
                    }

                    e = readdir(d);
                }
                if(errOcc)
                {
                    break;
                }
                if(errno==0) // For readdir().
                {
                    if(rmdir(inPath)==0)
                    {
                        retVal = true;
                    }
#ifndef NDEBUG
                    else
                    {
                        Deb_line("Error: Failed to remove folder \"%s\" (error %d)!", inPath, errno);
                    }
#endif //NDEBUG
                    errno = 0;
                }
#ifndef NDEBUG
                else
                {
                    Deb_line("Error: Failed to read an entry of folder \"%s\" (error %d)!", inPath, errno);
                }
#endif //NDEBUG
                errno = 0;

                closedir(d); // (return value ignored..)
            }
#ifndef NDEBUG
            else
            {
                Deb_line("Error: Failed to open folder \"%s\" (error %d)!", inPath, errno);
            }
#endif //NDEBUG
            errno = 0;
            break;
        }

        case FileSys_EntryType_Unsupported:
            Deb_line("Warning: Unsupported entry type received for \"%s\".", inPath);
            break;

        case FileSys_EntryType_Invalid:
            Deb_line("Error: Invalid entry type received for \"%s\".", inPath);
            break;
        default:
            Deb_line("Error: Unknown entry type received for \"%s\"!", inPath);
            break;
    }

    return retVal;
}
