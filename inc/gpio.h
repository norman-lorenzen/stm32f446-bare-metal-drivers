#ifndef GPIO_H
#define GPIO_H



#include <stdint.h>


typedef enum
{
    GPIO_PA = 0,
    GPIO_PB = 1,
    GPIO_PC = 2,
    GPIO_PD = 3,
    GPIO_PH = 4,
    GPIO_COUNT
} gpio_port_set;


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