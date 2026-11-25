#include "gpio.h"
#include "rcc.h"

int main(void)
{
    rcc_set_bit_on(GPIO_PA);
    gpio_set_mode(GPIO_PA, 5, OUTPUT_MODE);
    gpio_set_pin(GPIO_PA, 5, ON);


    while(1)
   {
   }
}