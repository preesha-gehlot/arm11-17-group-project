#include "io.h"

// counts the no of lines in the file
int countLines(FILE *file){
    int ch = 0;
    int lines = 0;
    lines++;
    while ((ch = fgetc(file)) != EOF){
        if (ch == '\n'){
            lines ++;
        }
    }

    return lines;
}

// mallocs space for assembler -> lines then reads instructions from file to assembler -> lines
void readInstr(assembler *assembler, char* path) {

    // opens the file
    FILE *file = fopen(path,"r");
    if (file == NULL) errorAndExit("Cannot read file from path at \"io.c::readInstr\".");

    int linesNum = countLines(file);
    assembler -> no_lines = linesNum - 1;

    assembler -> lines = malloc(linesNum * sizeof(char *));
    if (assembler -> lines == NULL) errorAndExit("Unable to allocate memory at \"io.c::readInstr\".");

    // set file pointer to start of file
    fseek(file, 0, SEEK_SET);

    // populate assembler -> lines with file lines
    int count = 0;
    char line[MAX_CHARS];
    while (fgets(line, sizeof(line), file)) {
      line[strcspn(line, "\r\n")] = 0;
      assembler -> lines[count] = malloc(strlen(line) + 1);
      strcpy(assembler -> lines[count++], line);
    }

    // closes the file
    fclose(file);
}

void writeInstr(assembler *ass, char* path) {

  // opens the file
  FILE *file = fopen(path, "wb");
  if (file == NULL) errorAndExit("Unable to write to file at \"io.c::writeInstr\".");

  // writes output and values arrays to file
  fwrite(ass -> output -> array, 4, ass -> output -> used, file);
  fwrite(ass -> values -> array, 4, ass -> values -> used, file);

  // closes the file
  fclose(file);

}
