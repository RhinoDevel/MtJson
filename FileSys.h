
// MT, 2016mar19

#ifndef MT_FILESYS
#define MT_FILESYS

#ifdef __cplusplus
extern "C" {
#endif

enum FileSys_EntryType
{
    FileSys_EntryType_Invalid = -1,
    FileSys_EntryType_Unsupported = 0,
    FileSys_EntryType_File = 1,
    FileSys_EntryType_Dir = 2
};

/** Concatenates given strings and adds directory separator between them
 *  (e.g.: inPath=="/home/marc", inName=="readme.txt" => return value "/home/marc/readme.txt").
 *
 *  - Caller takes ownership of returned value.
 */
char * FileSys_GetFullPath(char const * const inPath, char const * const inName);

/** Get absolute path (e.g. inPath=="../some_folder" => return value "/home/marc/some_folder").
 *
 * - If realpath() is not found, try to disable __STRICT_ANSI__ (e.g. by setting compiler parameter -std=gnu11).
 * - Caller takes ownership of returned pointer.
 */
char * FileSys_GetAbsPath(char const * const inPath);

enum FileSys_EntryType FileSys_GetEntryType(char const * const inPath);

off_t FileSys_GetFileSize(char const * const inPath);

#ifdef __cplusplus
}
#endif

#endif // MT_FILESYS