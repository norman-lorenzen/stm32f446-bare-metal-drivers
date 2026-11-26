#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>



uint32_t systick_get_tick(void);
void systick_init(void);
void SysTick_Handler(void);

#endif