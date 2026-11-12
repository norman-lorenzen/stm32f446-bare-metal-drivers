#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>



typedef enum
{
    INPUT_MODE    = 0,
    OUTPUT_MODE   = 1,
    FUNCTION_MODE = 2,
    ANALOG_MODE   = 3,
    RETURN_MODE   = 4
} gpio_mode;


uint8_t gpio_set_mode(uint8_t gpio_port, uint8_t gpio_pin, gpio_mode mode);


#endif