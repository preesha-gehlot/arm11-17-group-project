#ifndef EMU_DEFINIITONS_H
#define EMU_DEFINIITONS_H

#include "../definitions.h"

// Define some useful constants for later.
#define NO_REGISTERS  17
#define MEMORY_SIZE   65536

//unique masks for our single data transfer instructions
#define OFFSET_SDT_MASK           0x00000fffu
#define P_MASK                    0x01000000u
#define U_MASK                    0x00800000u
#define L_MASK                    0x00100000u

//mask for all instructions
//#define SBIT_MASK                 0x00100000u
#define COND_MASK                 0xf0000000u

typedef enum {
    DPC,
    MUL,
    SDT,
    BRA,
    BDT,
    SWP,
    HLT,
    NUL
} instruction_type;

// opcodes for the data processing instructions
typedef enum {
    AND = 0,
    EOR = 1,
    SUB = 2,
    RSB = 3,
    ADD = 4,
    TST = 8,
    TEQ = 9,
    CMP = 10,
    ORR = 12,
    MOV = 13
} opcode;

typedef struct {
    u_word offset;
} branch;

typedef struct {
    bool i_flag;
    u_byte opcode;
    bool set_flag;
    u_byte rn;
    u_byte rd;
    u_address operand2;
} dataProcessing;

typedef struct {
    bool accum_flag;
    bool set_flag;
    u_byte rd;
    u_byte rn;
    u_byte rs;
    u_byte rm;
} multiply;

typedef struct {
    bool i_flag;
    bool p_flag;
    bool u_flag;
    bool l_flag;
    u_byte rn;
    u_byte rd;
    u_address offset;
} singleDataTransfer;

typedef struct{
  bool p_flag;
  bool u_flag;
  bool s_flag;
  bool w_flag;
  bool ldm;
  u_byte rn;
  u_address reg_list;
}block;

typedef struct{
  bool b_flag;
  u_byte rn;
  u_byte rd;
  u_byte rm;
}singleDataSwap;

typedef union {
    dataProcessing *dataProcessingInstr;
    multiply *multiplyInstr;
    singleDataTransfer *SDTInstr;
    branch *branchInstr;
    block *blockInstr;
    singleDataSwap *swpInstr;
} instruction;

typedef struct {
    instruction_type i;
    conditionCode cond;
    instruction *instruction;
} decodedInstruction;

typedef struct {
    u_word registers[NO_REGISTERS];
    u_byte memory[MEMORY_SIZE];
    u_address endOfBinary;
    u_word stack_size;
    u_word fetched;
    bool has_fetched;
    decodedInstruction *decoded;
} state;

#endif
