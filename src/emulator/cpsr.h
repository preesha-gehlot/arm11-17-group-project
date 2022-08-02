#ifndef EMULATOR_CPSR_H
#define EMULATOR_CPSR_H

#include <stdbool.h>
#include "definitions.h"
#include "../definitions.h"
#include "../utils.h"

typedef enum {
  N,
  Z,
  C,
  V
} flags;

bool checkCPSR(state *state);
void setCPSR(flags flags, state *state, bool flag);

#endif
