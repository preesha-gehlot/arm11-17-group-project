#ifndef EMULATOR_IO_H
#define EMULATOR_IO_H

#include <stdio.h>
#include "definitions.h"
#include "../utils.h"

size_t getFileSize(FILE *file);
u_address loadFile(char *path, u_byte *memory);

#endif
