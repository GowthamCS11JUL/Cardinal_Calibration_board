#include "headers.h"
#include "usb.h"
#include "variables.h"

void app_init() {
  usb_init();
  cmd_data_setup();
  relay_init_all();
  led_init();
  Max5719GSD_init();
}

void cmd_data_setup() {
  usb_cmd_data_setup(&USB_DATA, 0, "LED_ON", "OK", led_on);
  usb_cmd_data_setup(&USB_DATA, 1, "LED_OFF", "OK", led_off);
}

void command_dispatcher(UART_DATA *usb_data, Parsed_Command_t *cmd) {
  /* -------------------------------------------- */ /* POWER */ /* --------------------------------------------
                                                                  */
  if (strcmp(cmd->tokens[0], "POWER") == 0) {
    power_command_handler(usb_data, cmd);
    return;
  } /* -------------------------------------------- */ /* RESISTOR */ /* --------------------------------------------
                                                                       */
  if (strcmp(cmd->tokens[0], "RESISTOR") == 0) {
    resistor_command_handler(usb_data, cmd);
    return;
  } /* -------------------------------------------- */ /* UNKNOWN */ /* --------------------------------------------
                                                                      */
  UART_Target_Transmit(usb_data->uartTargetIndex,
                       (uint8_t *)"UNKNOWN_COMMAND\r\n", 17);
}

void UART0_IRQHandler(void) { UART_Interface_IRQ(&USB_UART); }

void TIMA0_IRQHandler(void) { Timer_Timeout_IRQ(&USB_Timeout); }

void TIMG7_IRQHandler(void) { Delay_Timer_IRQ(&USB_BUFFER); }

void SPI0_IRQHandler(void) { SPI_IRQ(&ADC); }
