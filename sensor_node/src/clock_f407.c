#include "clock.h"
#include "board_f407.h"

void clock_init(void){

}

uint32_t get_hclk_hz(void){
    uint32_t const sysclk = get_sysclk_hz();
    uint32_t const hpre_value = (RCC->CFGR & RCC_CFGR_HPRE_Msk) >> RCC_CFGR_HPRE_Pos; 
    uint32_t ahb_prescaler = 0;

    switch (hpre_value) {
        case 0b1000:
            ahb_prescaler = 2;
            break;
        case 0b1001:
            ahb_prescaler = 4;
            break;
        case 0b1010:
            ahb_prescaler = 8;
            break;
        case 0b1011:
            ahb_prescaler = 16;
            break;
        case 0b1100:
            ahb_prescaler = 64;
            break;
        case 0b1101:
            ahb_prescaler = 128;
            break;
        case 0b1110:
            ahb_prescaler = 256;
            break;
        case 0b1111:
            ahb_prescaler = 512;
            break;
        default:
            ahb_prescaler = 1;
    }

    return sysclk / ahb_prescaler;
    
}


uint32_t get_pclk1_hz(void){
    //return BOARD_PCLK1_HZ;
}

uint32_t get_pclk2_hz(void){
    //return BOARD_PCLK2_HZ;
}

uint32_t get_sysclk_hz(void){
    uint32_t sysclk_switch_status = RCC->CFGR & RCC_CFGR_SWS_Msk;
    uint32_t sysclk = 0;
    uint32_t reference_hz;
    uint32_t pll_m; 
    uint32_t pll_n; 
    uint32_t pll_p; 

    switch (sysclk_switch_status) {
        case RCC_CFGR_SWS_HSI:
            sysclk = BOARD_HSI_HZ;
            break;
        case RCC_CFGR_SWS_HSE:
            sysclk = BOARD_HSE_HZ;
            break;
        case RCC_CFGR_SWS_PLL:
            reference_hz = RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC_Msk ? BOARD_HSE_HZ : BOARD_HSI_HZ;
            pll_m = (RCC->PLLCFGR & RCC_PLLCFGR_PLLM_Msk) >> RCC_PLLCFGR_PLLM_Pos;
            pll_n = (RCC->PLLCFGR & RCC_PLLCFGR_PLLN_Msk) >> RCC_PLLCFGR_PLLN_Pos;
            pll_p = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP_Msk) >> RCC_PLLCFGR_PLLP_Pos) + 1) * 2; // 00 => 2; 01 => 4; 10 => 6; 11 => 8

            sysclk = (uint32_t)((uint64_t)reference_hz * pll_n / pll_m / pll_p);
            break;
        default:
            sysclk = 0;
    }
    return sysclk;
}