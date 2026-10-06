#define NULL 0
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

extern uint32_t _sbss, _ebss, _etext, _edata, _sdata, _sidata, _estack;

uint32_t *const MSP = &_estack;

extern int main(void);

void TIM2_Handler(void);
void Reset_Handler(void);
void NMI_Handler(void) __attribute__((alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((alias("Default_Handler")));
void SVC_Handler(void) __attribute__((alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((alias("Default_Handler")));

uint32_t *Vector_Table[] __attribute__((section(".isr_vector"))) = {
    (uint32_t *)MSP,
    (uint32_t *)Reset_Handler,
    (uint32_t *)NMI_Handler,
    (uint32_t *)HardFault_Handler,
    (uint32_t *)MemManage_Handler,
    (uint32_t *)BusFault_Handler,
    (uint32_t *)UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t *)SVC_Handler,
    (uint32_t *)DebugMon_Handler,
    0,
    (uint32_t *)PendSV_Handler,
    (uint32_t *)SysTick_Handler,

    0,                       // IRQ 0
    0,                       // IRQ 1
    0,                       // IRQ 2
    0,                       // IRQ 3
    0,                       // IRQ 4
    0,                       // IRQ 5
    0,                       // IRQ 6
    0,                       // IRQ 7
    0,                       // IRQ 8
    0,                       // IRQ 9
    0,                       // IRQ 10
    0,                       // IRQ 11
    0,                       // IRQ 12
    0,                       // IRQ 13
    0,                       // IRQ 14
    0,                       // IRQ 15
    0,                       // IRQ 16
    0,                       // IRQ 17
    0,                       // IRQ 18
    0,                       // IRQ 19
    0,                       // IRQ 20
    0,                       // IRQ 21
    0,                       // IRQ 22
    0,                       // IRQ 23
    0,                       // IRQ 24
    0,                       // IRQ 25
    0,                       // IRQ 26
    0,                       // IRQ 27
    (uint32_t *)TIM2_Handler // IRQ 28
};

void system_init(void) {
  // clock configurations
}

void TIM2_Handler(void) {
  volatile uint16_t *tim2_status = (uint16_t *)(0x40000000 + 0x10);
  extern volatile uint32_t counter;
  counter++;
  *tim2_status = *tim2_status & ~(1 << 0);
}

void Reset_Handler(void) {
  uint32_t sec_size = 0;
  uint32_t *mem_src;
  uint32_t *mem_dest;

  // copy .data from flash to RAM
  sec_size = &_edata - &_sdata;
  mem_src = (uint32_t *)&_sidata;
  mem_dest = (uint32_t *)&_sdata;

  for (int i = 0; i < sec_size; i++) {
    *mem_dest = *mem_src;
    mem_src++;
    mem_dest++;
  }

  // zero out .bss section in RAM
  sec_size = &_ebss - &_sbss;
  mem_src = (uint32_t *)&_sbss;

  for (int i = 0; i < sec_size; i++) {
    *mem_src = 0;
    mem_src++;
  }

  system_init(); // empty for now

  main();
}

void Default_Handler(void) {}
