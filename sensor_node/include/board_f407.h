#ifndef BOARD_F407_H
#define BOARD_F407_H

/*
* Clock calculations according to RM0090 p. 165
* f(VCO clock) = f(PLL clock input) x (PLLN / PLLM)  
* f(PLL general clock output) = f(VCO clock) / PLLP
* f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLLQ 
*/

/*
* 100MHz <= f(VCO clock) <= 432MHZ 
* PLL clock input = BOARD_HSE_HZ = 8MHz
* f(PLL general clock output) = SYSCLK_HZ = 168MHz (target)
* f(USB OTG FS, SDIO, RNG clock output) will be set to 48MHz so all of them would work
* 50 <= PLLN <= 432
* 2 <= PLLM <= 63 chose to set f(PLL clock input) / PLLM between 1Mhz and 2Mhz, ideally 2MHz
* PLLP in {2, 4, 6, 8}
* 2 <= PLLQ <= 15
*
* Known values: 
*   f(PLL general clock output)             = 168MHZ
*   f(USB OTG FS, SDIO, RNG clock output)   = 48MHz
*
* Using f(PLL general clock output) = f(VCO clock) / PLLP
*    168MHZ = f(VCO clock) / {2, 4, 6, 8} 
*    possible values for f(VCO clock):
*        168MHz * 2 = 336MHZ
*        168MHz * 4 = 672MHZ which is already too large as upper limit is 432MHz
*
*        => f(VCO clock) = 336MHz
*        => PLLP = 2
*
* Using f(VCO clock) = f(PLL clock input) x (PLLN / PLLM) 
*   336MHz = 8MHz x (PLLN / PLLM) 
*   336Mhz / 8MHz = 42 = (PLLN / PLLM) 
*   
*   Considering f(PLL clock input) / PLLM  = 8MHz / PLLM should be between  1MHz and 2MHz
*   Ideal PLLM = 4
*   One possible solution: Set PLLM = 4 then PLLN = 42 * 4 = 168
*
*   => PLLM = 4
*   => PLLN = 168
*
* Using f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLLQ 
*   48MHz = 336MHz / PPLQ
*   336MHz / 48MHz = 7 = PPLQ
*
*   => PPLQ = 7
*/

#define BOARD_HSE_HZ            8000000U    // Crystal used on the STM32f407-disc1

#define BOARD_PLL_P             2U          // See calculations above
#define BOARD_PLL_M             4U          // See calculations above
#define BOARD_PLL_N             168U        // See calculations above
#define BOARD_PLL_Q             7U          // See calculations above
             
// Bus prescalers
#define BOARD_AHB_PRESCALER     1U          // HCLK  = SYSCLK / 1 = 168 MHz (max)       
#define BOARD_APB1_PRESCALER    4U          // PCLK1 = HCLK   / 4 = 42 MHz (max)
#define BOARD_APB2_PRESCALER    2U          // PCLK2 = HCLK   / 2 = 84 MHz (max)

// Resulting frequencies in Hz
#define BOARD_SYSCLK_HZ         168000000U
#define BOARD_HCLK_HZ           168000000U
#define BOARD_PCLK1_HZ          42000000U
#define BOARD_PCLK2_HZ          84000000U

#define BOARD_APB1_TIMER_HZ     84000000U   // Twice as fast as BOARD_PCLK1_HZ because BOARD_APB1_PRESCALER != 1
#define BOARD_APB2_TIMER_HZ     168000000U  // Twice as fast as BOARD_PCLK2_HZ because BOARD_APB2_PRESCALER != 1



#endif
