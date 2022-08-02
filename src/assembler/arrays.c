#include "definitions.h"

// mallocs space for word_array_t and initializes
void word_array_init(word_array_t *a) {
  a -> array = malloc(DEFAULT_ARRAY_SIZE * sizeof(u_word));
  if (a -> array == NULL) errorAndExit("Unable to allocate memory for \"arrays.c::word_array_init\".");
  a -> size = DEFAULT_ARRAY_SIZE;
  a -> used = 0;
}

// adds val to the array and dynamically allocates extra space
void word_array_add(word_array_t *a, u_word val) {
  if (a -> used == a -> size) {
    a -> size++;
    a -> array = realloc(a -> array, a -> size * sizeof(u_word));
    if (a -> array == NULL) errorAndExit("Unable to re-allocate memory for \"arrays.c::word_array_add\".");
  }
  a -> array[a -> used++] = val;
}

// frees memory used by the array
void word_array_free(word_array_t *a) {
  free(a -> array);
  a -> array = NULL;
  a -> used = a -> size = 0;
}

// mallocs space for instruction_array_t and initializes
void instruction_array_init(instruction_array_t *a) {
  a -> array = malloc(DEFAULT_ARRAY_SIZE * sizeof(instruction_t *));
  if (a -> array == NULL) errorAndExit("Unable to allocate memory for \"arrays.c::instruction_array_init\".");
  a -> size = DEFAULT_ARRAY_SIZE;
  a -> used = 0;
}

// adds val to the array and dynamically allocates extra space
void instruction_array_add(instruction_array_t *a, instruction_t *val) {
  if (a -> used == a -> size) {
    a -> size++;
    a -> array = realloc(a -> array, a -> size * sizeof(instruction_t *));
    if (a -> array == NULL) errorAndExit("Unable to re-allocate memory for \"arrays.c::instruction_array_add\".");
  }
  a -> array[a -> used++] = val;
}

// frees memory used by the array
void instruction_array_free(instruction_array_t *a) {
  free(a -> array);
  a -> array = NULL;
  a -> used = a -> size = 0;
}
