// FLASH: 0x0800 0000 - 0x0807 FFFF (512 kB), code + vector table
// RAM  : 0x2000 0000 - 0x2001 FFFF (128 kB), stack starts at top

int main(void);

void Reset_Handler(void)
{
    main();

    while (1)
    {

    }
}

#include <stdint.h>


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
const uint32_t vector_table[2] =
{
    0x20020000u,
    (uint32_t)&Reset_Handler
};