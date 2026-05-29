#ifndef COMMAND_H_
#define COMMAND_H_

typedef struct {
  char resistor_name[16];

  relay_select relay;

} Resistor_Map_t;

/* ------------------------------------------------ */
/* POWER COMMAND HANDLER                            */
/* ------------------------------------------------ */

/*
 * COMMAND FORMAT:
 *
 * POWER_SET_3300_1
 */

void power_command_handler(UART_DATA *usb_data,Parsed_Command_t *cmd);

/* ------------------------------------------------ */
/* RESISTOR COMMAND HANDLER                         */
/* ------------------------------------------------ */

/*
 * COMMAND FORMAT:
 *
 * RESISTOR_SET_120K
 */

void resistor_command_handler(UART_DATA *usb_data,Parsed_Command_t *cmd);

#endif