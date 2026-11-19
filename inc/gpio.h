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


typedef enum
{
    OFF   = 0,
    ON    = 1,
    COUNT = 2
} pin_on_off;


uint8_t gpio_set_mode(gpio_port_set gpio_port, uint8_t gpio_pin, gpio_mode mode);

uint8_t gpio_set_pin(gpio_port_set gpio_port, uint8_t gpio_pin, pin_on_off set_pin);


#endif