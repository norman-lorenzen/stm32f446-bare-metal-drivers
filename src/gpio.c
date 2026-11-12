#include "gpio.h"


// base GPIOA + OFFSET MODER (RM0390 Manual)
static volatile uint32_t *gpioa_moder = (volatile uint32_t *) 0x40020000; // GPIO MODER OFF SET


uint8_t gpio_set_mode(uint8_t gpio_port, uint8_t gpio_pin, gpio_mode mode)
{
    // a port has only pins 0-15
    // larger values would shift by 32 or more bits 
    // (undefined behaviour INT34-C)
    if (gpio_pin < 0 || gpio_pin > 15)
    {
        return 1;
    }

    // invalid mode fall back to input 
    // (reset state, drivers no current)
    if (mode < 0 || mode >= RETURN_MODE)
    {
        mode = INPUT_MODE;
    }

    // each pin use two bits, so the pin's field
    // starts at bit 2 * pin
    uint32_t mask = 3u << (2 * gpio_pin);

    // clear the field first: |= can only set bits
    // to 1, never to 0
    *gpioa_moder &= ~mask;

    // set mode on the right gpio_pin
    *gpioa_moder |= mode << (2 * gpio_pin);

    return 0;
}