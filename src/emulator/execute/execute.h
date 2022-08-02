#ifndef EXECUTE_H
#define EXECUTE_H

#include "data_processing.h"
#include "branch.h"
#include "single_data_transfer.h"
#include "multiply.h"
#include "../../extension/emulator/execute/block_data_transfer.h"
#include "../../extension/emulator/execute/single_data_swap.h"

bool execute(state *state);

#endif
