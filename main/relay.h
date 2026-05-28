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
/* FUNCTIONS                                        */
/* ------------------------------------------------ */

void relay_init_all(void);

void relay_disable_all(void);

void relay_on(relay_select number);

void relay_off(relay_select number);

/*
 * Optional helper
 * Turns ON only selected relay
 * Turns OFF all others
 */

void relay_select_only(relay_select number);

#endif