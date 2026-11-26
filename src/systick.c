#include "systick.h"

static const uintptr_t systick_begin = 0xE000E010u;

static volatile uint32_t systick_counter = 0u;



uint32_t systick_get_tick(void)
{
    return systick_counter;
}


void systick_init(void)
{
    uintptr_t load_adress = systick_begin + 0x04u;
    volatile uint32_t *load = (volatile uint32_t *) load_adress;

    *load = 15999u;


    uintptr_t val_adress = systick_begin + 0x08u;
    volatile uint32_t *val = (volatile uint32_t *) val_adress;

    *val = 0u;


    uintptr_t ctrl_adress = systick_begin + 0x00u;
    volatile uint32_t *ctrl = (volatile uint32_t *) ctrl_adress;

    *ctrl = 7u; // 4 = 1, 2 = 1 & 1 = 1, binary
}


void SysTick_Handler(void)
{
    systick_counter++;
}