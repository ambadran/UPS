#ifndef PROJECT_DEFS_H
#define PROJECT_DEFS_H

#include <STC/15W4xxAS/DIP16.h>
#define SMALL_FLASH
#define SMALL_RAM
#define BASIC_GPIO_HAL

#define NMOS_PORT GPIO_PORT1
#define NMOS_PIN GPIO_PIN1

#define PMOS_PORT GPIO_PORT1
#define PMOS_PIN GPIO_PIN2

#define V_DETECT_PORT GPIO_PORT1
#define V_DETECT_PIN GPIO_PIN3

#define RED_LED_PORT GPIO_PORT1
#define RED_LED_PIN GPIO_PIN4

#define GREEN_LED_PORT GPIO_PORT1
#define GREEN_LED_PIN GPIO_PIN5

#define BLUE_LED_PORT GPIO_PORT5
#define BLUE_LED_PIN GPIO_PIN4

#define BAT_ADC_CHANNEL ADC_CHANNEL0


#define CONSOLE_SPEED 115200
#define CONSOLE_UART UART1
#define CONSOLE_PIN_CONFIG 0

#define DEBUG_MODE

#define V_BAT_MAX 930  // 
#define V_BAT_MIN 734  //10.5v

#include <gpio-hal.h>
#include <delay.h>
#include <adc-comp-hal.h>
#include <uart-hal.h>
#include <serial-console.h>
#include <stdio.h>

#endif
