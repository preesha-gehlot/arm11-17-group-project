#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

#include "../../emulator/definitions.h"
#include "../../utils.h"

#define STACK_STARTING_ADDRESS MEMORY_SIZE - WORD_SIZE
#define WORD_SIZE 4

void create_stack(state *state);
u_word peek(state *state);
u_word pop(state *state);
void push(state *state, u_word data);
void print_stack(state *state);

#endif
