#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include <stdbool.h>

#include <limits.h>

#include "../cpsr.h"
#include "../../utils.h"
#include "barrel_shifter.h"
#include "../definitions.h"

#define WORD_MAX UINT_MAX

bool execute_data_processing(state *state);

#endif
