#include "inc/memory_address.h"

#include <stdint.h>
#include <sys/types.h>

volatile uint32_t counter = 0;

int main() {

  volatile uint32_t *gpioc_ctrl_reg = (uint32_t *)GPIOC_CRH;
  volatile uint32_t *gpioc_output_reg = (uint32_t *)GPIOC_ODR;
  volatile uint32_t *gpioc_clock_en = (uint32_t *)APB2ENR_ADDR;

  volatile uint16_t *timer2_control_reg = (uint16_t *)TIM2_CTRL_REG;
  volatile uint32_t *timer2_clock_en = (uint32_t *)APB1ENR_ADDR;
  volatile uint16_t *timer2_int_en_reg = (uint16_t *)TIM2_DIER_REG;
  volatile uint16_t *timer2_status_reg = (uint16_t *)TIM2_STATUS_REG;
  volatile uint16_t *timer2_psc_reg = (uint16_t *)TIM2_PSC_ADDR;
  volatile uint16_t *timer2_arr_reg = (uint16_t *)TIM2_ARR_ADDR;
  volatile uint32_t *nvic_iser0 = (uint32_t *)NVIC_ISER0;
  volatile uint16_t *tim2_egr_reg = (uint16_t *)TIM2_EGR_REG;
  ////////////////////setup gpio////////////////////////////////////

  *gpioc_clock_en = *gpioc_clock_en | (1 << 4); // enable gpioc clock

  *gpioc_ctrl_reg =
      *gpioc_ctrl_reg & ~((1 << 23) | (1 << 24)); // clear bits 23 and 24
  *gpioc_ctrl_reg =
      *gpioc_ctrl_reg & ~((1 << 20) | (1 << 21)); // clear bits 21 and 20
  *gpioc_ctrl_reg = *gpioc_ctrl_reg | (1 << 20);  // set bit 20
  //////////////////////////////////////////////////////////////////
  ////////////////////setup timer///////////////////////////////////
  *timer2_clock_en = *timer2_clock_en | (1 << 0);     // enable timer clock
  *timer2_int_en_reg = *timer2_int_en_reg | (1 << 0); // enable UIE
  *timer2_psc_reg = (uint16_t)7999;
  *timer2_arr_reg = (uint16_t)9;
  *nvic_iser0 = *nvic_iser0 | (1 << 28);
  *tim2_egr_reg = *tim2_egr_reg | (1 << 0);
  *timer2_status_reg &= ~(1 << 0);
  *timer2_control_reg = *timer2_control_reg | (1 << 0); // counter enable
  asm volatile("cpsie i");
  ////////////////////////////////////////////////////////////////////
  while (1) {
    if (counter >= 50) {
      *gpioc_output_reg = *gpioc_output_reg ^ (1 << 13);
      counter = 0;
    }
  }
}
