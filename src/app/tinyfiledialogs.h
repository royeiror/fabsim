/* minimal tinyfiledialogs.h stub for our build */
#ifndef TINYFILEDIALOGS_H
#define TINYFILEDIALOGS_H

#ifdef __cplusplus
extern "C" {
#endif

extern const char * tinyfd_openFileDialog(
    char const * aTitle,
    char const * aDefaultPathAndFile,
    int aNumOfFilterPatterns,
    char const * const * aFilterPatterns,
    char const * aSingleFilterDescription,
    int aAllowMultipleSelects);

extern const char * tinyfd_saveFileDialog(
    char const * aTitle,
    char const * aDefaultPathAndFile,
    int aNumOfFilterPatterns,
    char const * const * aFilterPatterns,
    char const * aSingleFilterDescription);

#ifdef __cplusplus
}
#endif

#endif
