#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>

#include "../definitions.h"

#define GPIO_CLEAR    0x20200028u
#define GPIO_CONTROL  0x2020001Cu

#define GPIO_CLEAR_CONTROL_SIZE 4

#define GPIO_20_29    0x20200008u
#define GPIO_10_19    0x20200004u
#define GPIO_0_9      0x20200000u

u_word read_from_gpio(u_word i);
void set_gpio(u_word i);

#endif
