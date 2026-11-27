# stm32f446-bare-metal-drivers

Register-level drivers for the STM32F446 in C, written from scratch.
No HAL, no CubeMX, no vendor startup code: every line between reset and `main()` is part of this repo.

**Hardware:** NUCLEO-F446RE (Cortex-M4F, 512 kB flash, 128 kB RAM)

## Why

I am building a hardware synthesizer on this board and want to understand every layer of it:
clock tree, registers, interrupts, startup and memory layout.
The drivers are written with secure coding in mind (CERT C, MISRA C:2012) and validate every input
before touching a register.

## Status

| Module | What it does | Tested on hardware |
|---|---|---|
| `startup/stm32f446re.ld` | Memory layout (FLASH/RAM), sections `.isr_vector`, `.text`, `.rodata`, `.data`, `.bss` | ✅ |
| `startup/startup_stm32f446.c` | Vector table (SysTick + `Default_Handler`), `Reset_Handler` copies `.data`, zeroes `.bss`, calls `main()` | ✅ |
| `rcc` | Enable GPIO port clocks (`AHB1ENR`) | ✅ |
| `gpio` | Pin mode (`MODER`), set/reset pin (`BSRR`), read pin (`IDR`), ports A–D and H | ✅ |
| `systick` | 1 ms tick interrupt, `systick_get_tick()` for non-blocking timing | ✅ |

**Next:** Makefile, UART, NVIC, PLL (180 MHz), PLLI2S, DMA, I2S (audio output), ADC, I2C (OLED).

## Example

`examples/button_blink`: the blue user button (PC13) toggles the green LED (PA5) between steady and blinking.

```c
rcc_set_bit_on(GPIO_PA);
gpio_set_mode(GPIO_PA, 5, OUTPUT_MODE);
gpio_set_pin(GPIO_PA, 5, ON);

systick_init();
uint32_t blink_start = systick_get_tick();
```

Blinking is non-blocking: the main loop compares `systick_get_tick()` with a stored timestamp
instead of waiting, so the button is read in every iteration.

## Build and flash

Toolchain: `arm-none-eabi-gcc` (e.g. from the STM32CubeIDE / STM32CubeCLT bundle) and `STM32_Programmer_CLI`.

```sh
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c17 -pedantic -Wall -Wextra -nostdlib \
  -T startup/stm32f446re.ld -I inc \
  examples/button_blink/main.c startup/startup_stm32f446.c src/gpio.c src/rcc.c src/systick.c \
  -o build/button_blink.elf

STM32_Programmer_CLI -c port=SWD -w build/button_blink.elf -v -rst
```

A Makefile is planned.

## Design notes

- **Input validation:** every public function checks port, pin and enum ranges and returns a status code (`0` = ok, `1` = rejected) instead of writing to an invalid address.
- **Safe defaults:** invalid modes fall back to input (the reset state), unhandled exceptions end in `Default_Handler`.
- **No dynamic memory**, all hardware addresses come from one table per peripheral.
- **Static analysis:** checked with `cppcheck --addon=misra`. Remaining deviations (e.g. rule 11.4, integer-to-pointer casts for memory-mapped registers) will be documented.

## References

- RM0390: STM32F446xx reference manual (GPIO, RCC)
- PM0214: STM32 Cortex-M4 programming manual (SysTick, vector table)
- UM1724: STM32 Nucleo-64 user manual (LD2 = PA5, B1 = PC13)
- Joseph Yiu, *The Definitive Guide to ARM Cortex-M3 and Cortex-M4 Processors*

## About

I am retraining as a software developer (Fachinformatiker Anwendungsentwicklung) with a focus on embedded security.
All code in this repository is written by me. I use an AI tutor (Claude) that asks questions and reviews my code
instead of writing it, similar to working with a mentor.

## License

MIT, see [LICENSE](LICENSE)
