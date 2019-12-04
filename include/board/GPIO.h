/* GPIO.h
 * Header for handling GPIO pins for LED number provisioning
 */

#include "MKW41Z4.h"
#include "fsl_gpio.h"

#define NUM_PINS 4

                          /*   LED1_IN,    LED2_IN,    LED3_IN,    LED4_IN*/
const uint32_t in_pin[]  = {        19,         16,          4,         17};
const uint32_t in_port[] = {PORTC_BASE, PORTC_BASE, PORTC_BASE, PORTC_BASE};
const uint32_t in_gpio[] = {GPIOC_BASE, GPIOC_BASE, GPIOC_BASE, GPIOC_BASE};

int32_t GPIO_Initialize(void){

  /* Port Initialization */
  // Sets required pins as GPIO (pin mux), Enables pull up and sets pull up
  for (int i = 0; i < NUM_PINS; i++) {
    ((PORT_Type *)in_port[i])->PCR[in_pin[i]] = (1U << 8) | (1U << 1) | (1U);
    ((PORT_Type *)in_port[i])->ISFR            &= (1U << in_pin[i]);
  }

  /* GPIO Initialization */
  for (int i = 0; i < NUM_PINS; i++) {
    ((GPIO_Type *)in_gpio[i])->PDOR           |=  (1U << in_pin[i]);
    ((GPIO_Type *)in_gpio[i])->PDDR           &=  ~(1U << in_pin[i]);
  }
  return 0;
}

uint32_t getPinState(uint8_t pin_no){
  uint32_t state = 2;
  switch(pin_no){
    case 1:
      state = GPIO_ReadPinInput(GPIOC,19);
      break;
    case 2:
      state = GPIO_ReadPinInput(GPIOC,16);
      break;
    case 3:
      state = GPIO_ReadPinInput(GPIOC,4);
      break;
    case 4:
      state = GPIO_ReadPinInput(GPIOC,17);
      break;
  }
  return state;
}
