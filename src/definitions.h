// Makes 'DEFINITIONS' a once-only header
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Include headers needed.
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>

// Define some types for useful byte lengths.
typedef uint8_t u_byte;
typedef uint16_t u_address;
typedef uint32_t u_word;
typedef int32_t s_word;

#define REG_SP 13
// #define REG_LR 14
#define REG_PC 15
#define REG_CPSR 16

#define WORD_IN_BYTES 4
#define WORD_IN_BITS  32

// condition codes for all instructions
typedef enum {
    EQ = 0,
    NE = 1,
    GE = 10,
    LT = 11,
    GT = 12,
    LE = 13,
    AL = 14
} conditionCode;

#endif
