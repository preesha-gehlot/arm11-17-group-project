#include "utils.h"

// converts string (hex or dec) into int
u_word toInt(char *integer){
  // if string doesn't contain substring "0x"
  if (strstr(integer, "0x") == NULL) {
    // handles as decimal
    return strtol(integer, NULL, 10);
  }
  // handles as hexadecimal
  return strtol(integer, NULL, 0);
}

// converts register string to int
u_word regToInt(char *registers) {
    return toInt(&registers[1]);
}

// sets bits of result by shifting val by n and or'ing with result
void set_bits(int n, u_word val, u_word *result) {
  *result |= val << n;
}

// counts the number of commans in a string
int count_commas(char *line){
    int count = 0;
    for(int i = 0; line[i] != END_CHAR; i++){
        if(line[i] == COMMA_CHAR){
            count++;
        }
    }
    return count;
}
