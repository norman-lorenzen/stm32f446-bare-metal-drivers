#include "gpio.h"
#include "rcc.h"
#include "systick.h"

#include <stdint.h>

typedef enum
{
    LIGHT_MODE_STEADY = 0,
    LIGHT_MODE_BLINK  = 1,
    LED_COUNTER
} on_off_button;

static on_off_button blink_steady = LIGHT_MODE_STEADY;

static pin_on_off led_state = ON;

int main (void)
{
    rcc_set_bit_on(GPIO_PA);
    gpio_set_mode(GPIO_PA, 5, OUTPUT_MODE);
    gpio_set_pin(GPIO_PA, 5, ON);

    uint8_t pin_state = 1;

    rcc_set_bit_on(GPIO_PC);
    gpio_pin_button(GPIO_PC, 13, &pin_state);

    uint8_t button_last = pin_state;

    systick_init();
    uint32_t blink_start = systick_get_tick();

    while (1)
    {
        gpio_pin_button(GPIO_PC, 13, &pin_state);


        if ((button_last == 1u) && (pin_state == 0u))
        {
            switch (blink_steady)
            {
                case LIGHT_MODE_BLINK:
                    blink_steady = LIGHT_MODE_STEADY;
                    break;

                case LIGHT_MODE_STEADY:
                    blink_steady = LIGHT_MODE_BLINK;
                    break;
                
                default:
                    break;
            }
        }

        uint32_t blink_now = systick_get_tick();


        switch (blink_steady)
        {
            case LIGHT_MODE_BLINK:
                if ((blink_now - blink_start) >= 500u)
                {
                    if (led_state == ON)
                    {
                        led_state = OFF;
                    }
                    else {
                    {
                        led_state = ON;
                    }
                    }
                    gpio_set_pin(GPIO_PA, 5, led_state);

                    blink_start = blink_now;
                }
                break;


            case LIGHT_MODE_STEADY:
                gpio_set_pin(GPIO_PA, 5, ON);
                break;
                
            default:
                break;
        }

        button_last = pin_state;
    }
}