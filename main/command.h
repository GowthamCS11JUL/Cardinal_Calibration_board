#ifndef COMMAND_H_
#define COMMAND_H_

typedef struct {
  char resistor_name[16];
  relay_select relay;
} Resistor_Map_t;
    /* ------------------------------------------------ */ /* FUNCTIONS */ /* ------------------------------------------------
                                                                            */
void power_command_handler(UART_DATA *usb_data, Parsed_Command_t *cmd);
void resistor_command_handler(UART_DATA *usb_data, Parsed_Command_t *cmd);

#endif