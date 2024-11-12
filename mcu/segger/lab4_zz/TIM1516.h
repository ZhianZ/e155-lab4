// Header for TIM functions
#ifndef STM32L4_TIM_H
#define STM32L4_TIM_H

#include <stdint.h> // Include stdint header
#include "RCC.h"

#define __IO volatile

#define TIM15_BASE_ADR (0x40014000) // Base address for TIM15
#define TIM16_BASE_ADR (0x40014400) // Base address for TIM16

typedef struct {
    __IO uint32_t TIM_CR1;     //< tim control register 1 
    __IO uint32_t TIM_CR2;     // tim control register 2 
    __IO uint32_t TIM15_SMCR;  // tim15 slave mode control register
    __IO uint32_t TIM_DIER;   // tim DMA/Interrupt enable register
    __IO uint32_t TIM_SR;     // time status register
    __IO uint32_t TIM_EGR;    // tim event generation register
    __IO uint32_t TIM_CCMR1;    // tim capture/compare mode register
    __IO uint32_t reserve2;
    __IO uint32_t TIM_CCER;     // capture/compare mode register
    __IO uint32_t TIM_CNT;     // tim counter
    __IO uint32_t TIM_PSC;    // tim prescaler
    __IO uint32_t TIM_ARR;    // time auto reload register
    __IO uint32_t TIM_RCR;    // repetition counter register
    __IO uint32_t TIM_CCR1;    // capture/compare register 1
    __IO uint32_t reserve3;
    __IO uint32_t reserve4;
    __IO uint32_t reserve5;
    __IO uint32_t TIM_BDTR;    // tim  break and dead-time register 
    __IO uint32_t TIM_DCR;    // DMA control register
    __IO uint32_t TIM_DMAR;    // 6 DMA address for full transfer
    __IO uint32_t TIM_OR1;    //  option register 1
    __IO uint32_t reserve6;
    __IO uint32_t reserve7;
    __IO uint32_t reserve8;
    __IO uint32_t TIM_OR2;    //  option register 2
} TIM_TypeDef;

#define TIM15 ((TIM_TypeDef *) (TIM15_BASE_ADR))
#define TIM16 ((TIM_TypeDef *) (TIM16_BASE_ADR))

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void initTIM(TIM_TypeDef * TIMx);
void delay_millis(TIM_TypeDef * TIMx, uint32_t ms);

void initPWM(TIM_TypeDef * TIMx);
void setFreq(TIM_TypeDef * TIMx, uint32_t freq);

#endif