#include "relay.h"
#include "headers.h"

/* ------------------------------------------------ */
/* RELAY COUNT                                      */
/* ------------------------------------------------ */

#define RELAY_COUNT 9

#define VOLTAGE_RELAY_COUNT 3

/* ------------------------------------------------ */
/* RELAY PORT TABLE                                 */
/* ------------------------------------------------ */

static GPIO_Regs *relay_ports[RELAY_COUNT] = {
    Relay_RELAY_EN_1_PORT, Relay_RELAY_EN_2_PORT, Relay_RELAY_EN_3_PORT,
    Relay_RELAY_EN_4_PORT, Relay_RELAY_EN_5_PORT, Relay_RELAY_EN_6_PORT,
    Relay_RELAY_EN_7_PORT, Relay_RELAY_EN_8_PORT, Relay_RELAY_EN_9_PORT};

/* ------------------------------------------------ */
/* RELAY PIN TABLE                                  */
/* ------------------------------------------------ */

static uint32_t relay_pins[RELAY_COUNT] = {
    Relay_RELAY_EN_1_PIN, Relay_RELAY_EN_2_PIN, Relay_RELAY_EN_3_PIN,
    Relay_RELAY_EN_4_PIN, Relay_RELAY_EN_5_PIN, Relay_RELAY_EN_6_PIN,
    Relay_RELAY_EN_7_PIN, Relay_RELAY_EN_8_PIN, Relay_RELAY_EN_9_PIN};

/* ------------------------------------------------ */
/* INIT ALL                                         */
/* ------------------------------------------------ */

void relay_init_all(void) {
  DL_GPIO_initDigitalOutput(Relay_RELAY_EN_1_IOMUX);

  DL_GPIO_enableOutput(Relay_RELAY_EN_1_PORT, Relay_RELAY_EN_1_PIN);

  DL_GPIO_initDigitalOutput(Relay_RELAY_EN_2_IOMUX);

  DL_GPIO_enableOutput(Relay_RELAY_EN_2_PORT, Relay_RELAY_EN_2_PIN);

  DL_GPIO_initDigitalOutput(Relay_RELAY_EN_3_IOMUX);

  DL_GPIO_enableOutput(Relay_RELAY_EN_3_PORT, Relay_RELAY_EN_3_PIN);

  DL_GPIO_initDigitalOutput(Relay_RELAY_EN_4_IOMUX);

  DL_GPIO_enableOutput(Relay_RELAY_EN_4_PORT, Relay_RELAY_EN_4_PIN);

  DL_GPIO_initDigitalOutput(Relay_RELAY_EN_5_IOMUX);

  DL_GPIO_enableOutput(Relay_RELAY_EN_5_PORT, Relay_RELAY_EN_5_PIN);

  DL_GPIO_initDigitalOutput(Relay_RELAY_EN_6_IOMUX);

  DL_GPIO_enableOutput(Relay_RELAY_EN_6_PORT, Relay_RELAY_EN_6_PIN);

  DL_GPIO_initDigitalOutput(Relay_RELAY_EN_7_IOMUX);

  DL_GPIO_enableOutput(Relay_RELAY_EN_7_PORT, Relay_RELAY_EN_7_PIN);

  DL_GPIO_initDigitalOutput(Relay_RELAY_EN_8_IOMUX);

  DL_GPIO_enableOutput(Relay_RELAY_EN_8_PORT, Relay_RELAY_EN_8_PIN);

  DL_GPIO_initDigitalOutput(Relay_RELAY_EN_9_IOMUX);

  DL_GPIO_enableOutput(Relay_RELAY_EN_9_PORT, Relay_RELAY_EN_9_PIN);

  relay_disable_all();
}

/* ------------------------------------------------ */
/* DISABLE ALL                                      */
/* ------------------------------------------------ */

void relay_disable_all(void) {
  for (uint8_t i = 0; i < RELAY_COUNT; i++) {
    DL_GPIO_clearPins(

        relay_ports[i],

        relay_pins[i]

    );
  }
}

/* ------------------------------------------------ */
/* VOLTAGE RELAYS OFF                               */
/* ------------------------------------------------ */

void relay_voltage_off(void) 
{
  for (uint8_t i = 0; i < VOLTAGE_RELAY_COUNT; i++) {
    DL_GPIO_clearPins(relay_ports[i],relay_pins[i]);
  }
}

/* ------------------------------------------------ */
/* RESISTOR RELAYS OFF                              */
/* ------------------------------------------------ */

void relay_resistor_off(void) {
  for (uint8_t i = VOLTAGE_RELAY_COUNT; i < RELAY_COUNT; i++) 
  {
    DL_GPIO_clearPins(relay_ports[i],relay_pins[i]);
  }
}

/* ------------------------------------------------ */
/* RELAY ON                                         */
/* ------------------------------------------------ */

void relay_on(relay_select number) {
  if ((number < Relay_EN_1) || (number > Relay_EN_9)) {
    return;
  }

  DL_GPIO_setPins(relay_ports[number - 1],relay_pins[number - 1]);
}

/* ------------------------------------------------ */
/* RELAY OFF                                        */
/* ------------------------------------------------ */

void relay_off(relay_select number) {
  if ((number < Relay_EN_1) || (number > Relay_EN_9)) {
    return;
  }

  DL_GPIO_clearPins(relay_ports[number - 1], relay_pins[number - 1]);
}

/* ------------------------------------------------ */
/* SELECT ONLY ONE RELAY                            */
/* ------------------------------------------------ */

void relay_select_only(relay_select number) {
  if ((number < Relay_EN_1) || (number > Relay_EN_9)) {
    return;
  }

  relay_disable_all();

  relay_on(number);
}

/* ------------------------------------------------ */
/* SELECT ONLY VOLTAGE RELAY                        */
/* ------------------------------------------------ */

void relay_on_voltage(relay_select number) {
  if ((number >= Relay_EN_1) && (number <= Relay_EN_3)) {
    relay_voltage_off();

    relay_on(number);
  }
}

/* ------------------------------------------------ */
/* SELECT ONLY RESISTOR RELAY                       */
/* ------------------------------------------------ */

void relay_on_resistor_select(relay_select number) {
  if ((number >= Relay_EN_4) && (number <= Relay_EN_9)) {
    relay_resistor_off();

    relay_on(number);
  }
}