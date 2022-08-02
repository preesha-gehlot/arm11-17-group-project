#include "io.h"

/* Safe way of determining size of file/pointer to EOF. */
size_t getFileSize(FILE *file) {
    /* Finds relative pointer of the end of file. */
    fseek(file, 0, SEEK_END);
    /* Gets the pointer corresponding to size. */
    size_t size = ftell(file);
    /* Resets the relative pointer to start of file. */
    fseek(file, 0, SEEK_SET);
    return size;
}

u_address loadFile(char *path, u_byte *memory) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) errorAndExit("Cannot read file from path.");

    /* Gets size of the file (pointer is 0-indexed so add 1 for size). */
    size_t size = getFileSize(file) + 1;
    /* Checks for memory overflow. */
    if (size > MEMORY_SIZE) errorAndExit("Memory overflow.");

    /* Checks if memory can be allocated to pointer given. */
    if (!memory) errorAndExit("Cannot allocate memory.");

    /* Read the binary to the memory starting at the pointer given.
       Each element is of size WORD_IN_BYTES (4 bytes) */
    u_address result = fread(memory, 1, size, file);
    fclose(file);
    return result;
}
