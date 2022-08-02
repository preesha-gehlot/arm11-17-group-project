#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "io.h"
#include "fetch.h"
#include "decode.h"
#include "execute/execute.h"
#include "../definitions.h"
#include "../utils.h"
#include "utils.h"
#include "decompiler.h"
#include "definitions.h"

static const state INIT_STATE = {
  .memory = {0},
  .registers = {0},
  .endOfBinary = 0,
  .fetched = 0,
  .has_fetched = false,
  .decoded = NULL
};

void free_decoded(decodedInstruction *decoded) {
  switch (decoded -> i) {
    case DPC:
      free(decoded -> instruction -> dataProcessingInstr);
      break;
    case MUL:
      free(decoded -> instruction -> multiplyInstr);
      break;
    case SDT:
      free(decoded -> instruction -> SDTInstr);
      break;
    case BRA:
      free(decoded -> instruction -> branchInstr);
      break;
    case BDT:
      free(decoded -> instruction -> blockInstr);
      break;
    case SWP:
      free(decoded -> instruction -> swpInstr);
  }
  free(decoded -> instruction);
  free(decoded);
}

void output(state *state, bool debug) {

    char *binary[16] = {
      "0000",
      "0001",
      "0010",
      "0011",
      "0100",
      "0101",
      "0110",
      "0111",
      "1000",
      "1001",
      "1010",
      "1011",
      "1100",
      "1101",
      "1111"
  };

  printf("Registers:\n");
  for (int i = 0; i < NO_REGISTERS; i++) {
    if (i == 13 || i == 14) continue;
    if (i == REG_PC) {
        printf("%-4s", "PC");
    } else if (i == REG_CPSR) {
        if (debug) {
          printf("%-4s: %10s (0x%08x)\n", "CPSR", binary[state -> registers[i] >> 28], state -> registers[i]);
          continue;
        } else {
          printf("%-4s", "CPSR");
        }
    } else {
        printf("$%-3d", i);
    }
    printf(": %10d (0x%08x)\n", state -> registers[i], state -> registers[i]);
  }
  printf("Non-zero memory:\n");
  for (int i = 0; i < MEMORY_SIZE; i += 4) {
    u_word data = getWordFromMem(i, state, true);
    if (data != 0) {
      printf("0x%08x: 0x%08x\n", i, data);
    }
  }
}

void terminate(state *state, bool debug) {
  output(state, debug);
  free(state);

}

int main(int argc, char **argv) {

  if (argc < 2 || argc > 4) {
    errorAndExit("Invalid arguments. Usage: emulate <file.bin> [-debug] [-log]");
  }

  bool debug = false;
  bool log = false;
  if (argc > 2) {
    debug |= strcmp(argv[2], "-debug") == 0;
    log |= strcmp(argv[2], "-log") == 0;
  }
  if (argc > 3) {
    debug |= strcmp(argv[3], "-debug") == 0;
    log |= strcmp(argv[3], "-log") == 0;
  }

  char *file = argv[1];
  state *raspi = malloc(sizeof(state));

  if (!raspi) {
    errorAndExit("Unable to allocate memory for state.");
  }

  if (debug) {
    printf("** Debugging enabled. **\n");
  }
  if (log) {
    printf("**  Logging enabled.  **\n");
  }

  *raspi = INIT_STATE;
  raspi -> endOfBinary = loadFile(file, raspi -> memory);
  create_stack(raspi);

  while (raspi -> registers[REG_PC] < raspi -> endOfBinary + 8) {

    if (log) {
      output(raspi, debug || log);
    }

    if (raspi -> decoded != NULL) {
      if (debug || log) {
        printf(" -- Executing ");
        printDecoded(raspi);
      }

      bool executeCode = execute(raspi);
      free_decoded(raspi -> decoded);
      raspi -> decoded = NULL;
      if (!executeCode) break;
    }

    if (raspi -> has_fetched) {
      raspi -> decoded = decode(raspi -> fetched);
      raspi -> has_fetched = false;
    }

    if (raspi -> registers[REG_PC] < raspi -> endOfBinary) {
      raspi -> fetched = fetch(raspi);
      raspi -> has_fetched = true;
    }

    raspi -> registers[REG_PC] = raspi -> registers[REG_PC] + 4;

    if (debug) {
      if (raspi -> has_fetched) {
        printf("Fetched: %x\n", raspi -> fetched);
      }
      if (raspi -> decoded != NULL) {
        printf("Decoded: %d\n", raspi -> decoded -> i);
      }
    }

  }

  terminate(raspi, debug || log);
  return EXIT_SUCCESS;
}
