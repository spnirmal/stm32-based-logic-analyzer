#include <stdint.h>
#ifndef memory_address
#define memory_address

//////////////GPIO ADDRESS//////////////////////////////////////////////
#define RCC_BASE_ADDR 0x40021000
#define GPIOC_BASE_ADDR 0x40011000
#define APB2ENR_ADDR (RCC_BASE_ADDR + 0x18)
// IO port C clock enable at bit 4

#define GPIOC_CRH (GPIOC_BASE_ADDR + 0x04)
// cfg bits 23 and 24 for pin 13, must be 00 for push-pull
// mode bits 21 and 20 for pin 13, must be  01 for output max speed 10 MHz

#define GPIOC_ODR (GPIOC_BASE_ADDR + 0x0C)
// bit 13 corresponds to output bit of pin 13
//
/////////////////////////////////////////////////////////////////////////
///
///
///
/////////////TIMER ADDRESS///////////////////////////////////////////////
#define APB1ENR_ADDR (RCC_BASE_ADDR + 0x1C) // set bit 0
#define TIM2_BASE_ADDR 0x40000000

#define TIM2_CTRL_REG (TIM2_BASE_ADDR + 0x00) // set bit 0 enable counter
#define TIM2_DIER_REG                                                          \
  (TIM2_BASE_ADDR + 0x0C) // set bit 0 , UIE update interrupt enable

#define TIM2_STATUS_REG                                                        \
  (TIM2_BASE_ADDR + 010) // bit 0 is UIF, update interrupt flag
#define TIM2_PSC_ADDR (TIM2_BASE_ADDR + 0x28) // 15:0 set this to 0
#define TIM2_ARR_ADDR                                                          \
  (TIM2_BASE_ADDR + 0x2C) // 15:0  make this 7 , so counts upto 7
#define NVIC_ISER0 0xE000E100
#define TIM2_EGR_REG (TIM2_BASE_ADDR + 0x14)

#endif
