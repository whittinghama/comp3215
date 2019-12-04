// System abstraction for GPIO on KW41Z

// Function declarations header
#include "openthread-system.h"

#include <string.h>

// OpenThread instance header
#include <openthread/instance.h>

// Drivers for KW41Z functions
#include <board/MKW41Z4.h>
#include <board/LED.h>
#include <board/GPIO.h>
#include <board/fsl_gpio.h>
#include <board/fsl_common.h>

// LED Pin config function
void otSysLEDInit(void){
  LED_Initialize();
  LED_Off(0);
  LED_Off(1);
  LED_Off(2);
  LED_Off(3);
}

// LED mode set function
void otSysLEDSet(uint32_t nLed, bool ledon){
  if(ledon){
    LED_On(nLed);
  }
  else{
    LED_Off(nLed);
  }
}

void otSysPinsInit(void){
  GPIO_Initialize();
}

uint32_t otSysPinsRead(uint8_t pin_no){
  return getPinState(pin_no);
}
