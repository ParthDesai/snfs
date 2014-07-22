#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED


#include <unistd.h>

#include <stdint.h>

#include <stdlib.h>

#include "diskStruct.h"

#include "diskManager.h"

#define BLOCK_SIZE 1024

#define MAX_FILESYSTEM_SIZE (FILE_METADATA_MAX_SIZE + (2 * 1024 * 1024 * 1024) )

#define FILE_METADATA_MAX_SIZE (256 * 1024 * 1024)

typedef unsigned char byte;

#endif // COMMON_H_INCLUDED
