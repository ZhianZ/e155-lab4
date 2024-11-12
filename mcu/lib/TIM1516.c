// TIM functions

#include "TIM1516.h"

#define INT_CLK 80000000U
#define PSC 7999U

void initTIM(TIM_TypeDef * TIMx){
  // Set main output enable
  TIMx->TIM_BDTR |= (1<<15);
  // Set prescaler to give 0.1 ms time base
  TIMx->TIM_PSC = 7999;
  // Generate an update event to update prescaler value
  TIMx->TIM_EGR |= (1<<0);
  // Enable counter
  TIMx->TIM_CR1 |= (1<<0); // Set CEN = 1
  // Disable slave mode
  TIMx->TIM15_SMCR &= ~(1<<16);
  TIMx->TIM15_SMCR &= ~(0b111 << 0);
}

void delay_millis(TIM_TypeDef * TIMx, uint32_t ms){
  TIMx->TIM_ARR = ms*10;// Set timer max count
  TIMx->TIM_EGR |= (1<<0);     // Force update
  TIMx->TIM_SR &= ~(0x1); // Clear UIF
  TIMx->TIM_CNT = 0;      // Reset count

  while(!(TIMx->TIM_SR & 1)); // Wait for UIF to go high
}

void initPWM(TIM_TypeDef * TIMx){
  // Generate an update event to update prescaler value
  TIMx->TIM_EGR |= (1<<0);
  // Enable counter
  TIMx->TIM_CR1 |= (1<<0); // Set CEN = 1
  // Set main output enable
  TIMx->TIM_BDTR |= (1<<15);
  // Set prescaler to give 2.5 us time base
  TIMx->TIM_PSC = 799;
  // TIMx_ARR register is buffered
  TIMx->TIM_CR1 |= (0b1 << 7); 
  // Set auto-reload value, initialize 1kHz frequency
  TIMx->TIM_ARR = 7999;  
  // Output compare mode (CC1S) and PWM mode 1 (OC1M)   
  TIMx->TIM_CCMR1 |= (0b1 << 6);
  TIMx->TIM_CCMR1 |= (0b1 << 5); 
  // Enable preload register
  TIMx->TIM_CCMR1 |= (0b1 << 3); 
  // Enable output for channel 1 (CC1E bit)
  TIMx->TIM_CCER |= (0b1 << 0); 
}

void setFreq(TIM_TypeDef * TIMx, uint32_t freq){
    // Generate an update event to update prescaler value
    TIMx->TIM_EGR |= (1<<0);
    // Enable counter
    TIMx->TIM_CR1 |= (1<<0); // Set CEN = 1

    //TIMx->TIM_PSC = 0;
    if(freq == 0) TIMx->TIM_CR1 &= ~(1<<0); //Disable the counter
    else{
      TIMx->TIM_ARR = (100000/freq); // Change frequency
      TIMx->TIM_CCR1 = (TIMx->TIM_ARR) / 2; // Keep duty cycle 50% 
    }
}