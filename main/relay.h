#ifndef RELAY_H_
#define RELAY_H_

#include <stdint.h>

/* ------------------------------------------------ */
/* RELAY ENUM                                       */
/* ------------------------------------------------ */

typedef enum {
  Relay_EN_1 = 1,
  Relay_EN_2,
  Relay_EN_3,
  Relay_EN_4,
  Relay_EN_5,
  Relay_EN_6,
  Relay_EN_7,
  Relay_EN_8,
  Relay_EN_9

} relay_select;

/* ------------------------------------------------ */
/* FUNCTION PROTOTYPES                              */
/* ------------------------------------------------ */

/**
 * @brief Initialize all relay GPIOs as outputs and disable them.
 */
void relay_init_all(void);

/**
 * @brief Disable all relays.
 */
void relay_disable_all(void);

/**
 * @brief Turn off all voltage relays (Relay_EN_1 to Relay_EN_3).
 */
void relay_voltage_off(void);

/**
 * @brief Turn off all resistor relays (Relay_EN_4 to Relay_EN_9).
 */
void relay_resistor_off(void);

/**
 * @brief Turn on a specific relay.
 * @param number Relay selection (Relay_EN_1 to Relay_EN_9).
 */
void relay_on(relay_select number);

/**
 * @brief Turn off a specific relay.
 * @param number Relay selection (Relay_EN_1 to Relay_EN_9).
 */
void relay_off(relay_select number);

/**
 * @brief Disable all relays and then enable only the selected relay.
 * @param number Relay selection (Relay_EN_1 to Relay_EN_9).
 */
void relay_select_only(relay_select number);

/**
 * @brief Enable only one voltage relay (Relay_EN_1 to Relay_EN_3).
 *        Automatically disables other voltage relays.
 * @param number Relay selection (Relay_EN_1 to Relay_EN_3).
 */
void relay_on_voltage(relay_select number);

/**
 * @brief Enable only one resistor relay (Relay_EN_4 to Relay_EN_9).
 *        Automatically disables other resistor relays.
 * @param number Relay selection (Relay_EN_4 to Relay_EN_9).
 */
void relay_on_resistor_select(relay_select number);

#endif
