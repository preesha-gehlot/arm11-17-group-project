#include "gpio.h"

u_word read_from_gpio(u_word i) {
    switch (i) {
        case GPIO_0_9:
            printf("One GPIO pin from 0 to 9 has been accessed\n");
            break;
        case GPIO_10_19:
            printf("One GPIO pin from 10 to 19 has been accessed\n");
            break;
        case GPIO_20_29:
            printf("One GPIO pin from 20 to 29 has been accessed\n");
            break;
    }
    return i;
}
void set_gpio(u_word i) {
    if (GPIO_0_9 <= i && i <= GPIO_20_29) {
      read_from_gpio(i);
    } else if (GPIO_CLEAR <= i && i <= GPIO_CLEAR + GPIO_CLEAR_CONTROL_SIZE) {
      printf("PIN OFF\n");
    } else if (GPIO_CONTROL <= i && i <= GPIO_CONTROL + GPIO_CLEAR_CONTROL_SIZE) {
      printf("PIN ON\n");
    }
}
