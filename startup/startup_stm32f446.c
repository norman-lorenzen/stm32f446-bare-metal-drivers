// FLASH: 0x0800 0000 - 0x0807 FFFF (512 kB), code + vector table
// RAM  : 0x2000 0000 - 0x2001 FFFF (128 kB), stack starts at top

#include "systick.h"

#include <stdint.h>

// LINKER SCRIPT SECTIONS
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;


int main(void);

void Default_Handler(void)
{
    while (1)
    {

    }
}


void Reset_Handler(void)
{
    const uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    while (dst < &_edata)
    {
        *dst = *src;  
        
        dst++;
        src++;
    }

    dst = &_sbss;

    while (dst < &_ebss)
    {
        *dst = 0u;
        dst++;
    }

    main();

    while (1)
    {
    }
}


 /*
 * Vector table: the Cortex-M4 reads it at reset (flash is mirrored to 0x0).
 *   [0] initial stack pointer -> top of RAM (stack grows downwards)
 *   [1] reset vector          -> address of Reset_Handler (first code to run)
 *
 * section(".isr_vector"): label for the linker script, which places this
 *                         table at the very start of flash (0x08000000).
 * used:                   keep it, even though no C code references it.
 */

__attribute__((section(".isr_vector"), used))
const uint32_t vector_table[16] =
{
    0x20020000u,
    (uint32_t)&Reset_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&Default_Handler,
    (uint32_t)&SysTick_Handler
};