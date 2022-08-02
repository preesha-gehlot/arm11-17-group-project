#include "execute.h"

bool execute(state *state) {

  if (state -> decoded -> i == HLT) return 0;

  if (!checkCPSR(state)) return 1;
  switch (state -> decoded -> i) {
    case DPC:
      execute_data_processing(state);
      return 1;
    case MUL:
      execute_multiply(state);
      return 1;
    case SDT:
      execute_sdt(state);
      return 1;
    case BRA:
      execute_branch(state);
      return 1;
    case NUL:
      return 1;
    case BDT:
      execute_bdt(state);
      return 1;
    case SWP:
      execute_swp(state);
      return 1;
    default:
      errorAndExit("cannot recognise instruction to execute");

  }
}
