#include "cpsr.h"

bool checkCPSR(state *state) {

    bool flagN, flagZ, flagV;
    u_word flags = state -> registers[REG_CPSR];

    flagN = flags >> 31;
    flagZ = flags >> 30 & 0x1;
    flagV = flags >> 28 & 0x1;

    switch (state -> decoded -> cond) {
        case EQ:
            return flagZ;
        case NE:
            return !flagZ;
        case GE:
            return flagN == flagV;
        case LT:
            return flagN != flagV;
        case GT:
            return !flagZ && (flagN == flagV);
        case LE:
            return flagZ || (flagN != flagV);
        case AL:
            return true;
        default:
            return false;
    }
}

static void set(state *state, u_byte flags) {
    state -> registers[REG_CPSR] = (state -> registers[REG_CPSR] & ~COND_MASK)
                                | (flags << 28);
}


void setCPSR(flags flags, state *state, bool flag) {

    u_byte codes = state -> registers[REG_CPSR] >> 28;

    switch (flags) {
      case N:
        set(state, ((codes & 0x7) | (flag << 3)));
        break;
      case Z:
        set(state, ((codes & 0xb) | (flag << 2)));
        break;
      case C:
        set(state, ((codes & 0xd) | (flag << 1)));
        break;
      case V:
        set(state, ((codes & 0xe) | flag));
        break;
      default: errorAndExit("Invalid flag.");
    }

}
