#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

void clock_init(void);
uint32_t get_sysclk_hz(void);
uint32_t get_hclk_hz(void);
uint32_t get_pclk1_hz(void);
uint32_t get_pclk2_hz(void);

#endif