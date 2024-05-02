#include "project-defs.h"

static GpioConfig nmos = GPIO_PIN_CONFIG(NMOS_PORT, NMOS_PIN, GPIO_PUSH_PULL_MODE);

static GpioConfig pmos = GPIO_PIN_CONFIG(PMOS_PORT, PMOS_PIN, GPIO_PUSH_PULL_MODE);

static GpioConfig v_detect = GPIO_PIN_CONFIG(V_DETECT_PORT, V_DETECT_PIN, GPIO_HIGH_IMPEDANCE_MODE);

static GpioConfig red_led = GPIO_PIN_CONFIG(RED_LED_PORT, RED_LED_PIN, GPIO_PUSH_PULL_MODE);

static GpioConfig green_led = GPIO_PIN_CONFIG(GREEN_LED_PORT, GREEN_LED_PIN, GPIO_PUSH_PULL_MODE);

static GpioConfig blue_led = GPIO_PIN_CONFIG(BLUE_LED_PORT, BLUE_LED_PIN, GPIO_PUSH_PULL_MODE);

void main(void) {

  INIT_EXTENDED_SFR();
  EA = 1;

  gpioConfigure(&nmos);
  gpioConfigure(&pmos);
  gpioConfigure(&v_detect);
  gpioConfigure(&red_led);
  gpioConfigure(&green_led);
  gpioConfigure(&blue_led);

	serialConsoleInitialise(
		CONSOLE_UART, 
		CONSOLE_SPEED, 
		CONSOLE_PIN_CONFIG
	);

  adcInitialise(ADC_ALIGN_RIGHT, DISABLE_INTERRUPT);
  adcConfigureChannel(BAT_ADC_CHANNEL);

  uint8_t v_in_out_state;
  uint16_t v_bat;
  uint8_t nmos_state;
  uint8_t pmos_state;
  while(1) {

    v_in_out_state = !(gpioRead(&v_detect));
    v_bat = adcBlockingRead(BAT_ADC_CHANNEL);
    nmos_state = !((v_bat < V_BAT_MAX) && (v_in_out_state));
    pmos_state = ((v_bat > V_BAT_MIN) && !(v_in_out_state));

    gpioWrite(&nmos, nmos_state);
    gpioWrite(&pmos, pmos_state);
    gpioWrite(&red_led, !nmos_state);
    gpioWrite(&green_led, (nmos_state && !pmos_state));
    gpioWrite(&blue_led, pmos_state);

		printf("ADC = %u, v_inout = %u, nmos: %u, pmos: %u\r\n", v_bat, v_in_out_state, !nmos_state, pmos_state);

  }

}
