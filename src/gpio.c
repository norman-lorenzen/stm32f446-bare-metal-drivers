#include "gpio.h"



static const uintptr_t gpio_offset_ports[GPIO_COUNT] = {0x40020000, // A
                                                        0x40020400, // B
                                                        0x40020800, // C
                                                        0x40020C00, // D
                                                        0x40021C00}; // H


static uint8_t check_port(gpio_port_set gpio_port)
{
    if ((gpio_port < GPIO_PA) || (gpio_port >= GPIO_COUNT))
    {
        return 1;
    }

    return 0;
}


uint8_t gpio_set_mode(gpio_port_set gpio_port, uint8_t gpio_pin, gpio_mode mode)
{
    if (check_port(gpio_port) == 1u)
    {
        return 1;
    }

    volatile uint32_t *moder = (volatile uint32_t *) gpio_offset_ports[gpio_port];

    // a port has only pins 0-15
    // larger values would shift by 32 or more bits 
    // (undefined behaviour INT34-C)
    if (gpio_pin > 15u)
    {
        return 1;
    }

    // invalid mode fall back to input 
    // (reset state, drivers no current)
    if ((mode < INPUT_MODE) || (mode >= RETURN_MODE))
    {
        mode = INPUT_MODE;
    }

    uint32_t pin_shift = 2u * (uint32_t)gpio_pin;

    // each pin use two bits, so the pin's field
    // starts at bit 2 * pin
    uint32_t mask = (uint32_t)3u << pin_shift;

    // clear the field first: |= can only set bits
    // to 1, never to 0
    *moder &= ~mask;

    // set mode on the right gpio_pin
    *moder |= (uint32_t)mode << pin_shift;

    return 0;
}


uint8_t gpio_set_pin(gpio_port_set gpio_port, uint8_t gpio_pin, pin_on_off set_pin)
{
    if (check_port(gpio_port) == 1u)
    {
        return 1;
    }

    if ((set_pin < OFF) || (set_pin >= COUNT))
    {
        return 1;
    }

    // a port has only pins 0-15
    // larger values would shift by 32 or more bits 
    // (undefined behaviour INT34-C)
    if (gpio_pin > 15u)
    {
        return 1;
    }


    uintptr_t bsrr_address = gpio_offset_ports[gpio_port] + 0x18u;


    volatile uint32_t *bsrr = (volatile uint32_t *) bsrr_address;

    switch (set_pin)
    {
        case OFF:
            *bsrr = (uint32_t)1u << (gpio_pin + 16u);
            break;

        case ON:
            *bsrr = (uint32_t)1u << gpio_pin;
            break;

        default:
            return 1;
    }

    return 0;
}