#include "rcc.h"

static const uintptr_t rcc_base = 0x40023800u;

// GPIO A = 0, B = 1, C = 2, D = 3 and H = 7
// bits 4-6 belong to GPIOE-G, which the 64-pin F446RE does not have
static const uint8_t gpio_bits[GPIO_COUNT] = {0, 1, 2, 3, 7};


uint8_t rcc_set_bit_on(gpio_port_set gpio_port)
{
    // if lower or higher value as gpio_port enum
    // fail
    if ((gpio_port < GPIO_PA) || (gpio_port >= GPIO_COUNT))
    {
        return 1;
    }

    // set on ahb1enr address
    uintptr_t ahb1enr_address = rcc_base + 0x30u;

    // save variable ahb1enr_address
    volatile uint32_t *ahb1enr = (volatile uint32_t *) ahb1enr_address;

    // set bit A,B,C,D or H on
    *ahb1enr |= (uint32_t)1u << gpio_bits[gpio_port];

    return 0;
}
