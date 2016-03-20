
// MT, 2016mar19

#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <sys/stat.h>
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
