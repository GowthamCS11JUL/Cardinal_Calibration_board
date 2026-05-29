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
  usb_cmd_data_setup(&USB_DATA, 2, "turn_on_3v3_site_1","OK",turn_on_3v3_site_1);
  usb_cmd_data_setup(&USB_DATA, 3, "turn_on_3v3_site_2","OK",turn_on_3v3_site_2);
  usb_cmd_data_setup(&USB_DATA, 4, "turn_on_3v3_site_3","OK",turn_on_3v3_site_3);
  usb_cmd_data_setup(&USB_DATA, 5, "turn_on_2v7_site_1","OK",turn_on_2v7_site_1);
  usb_cmd_data_setup(&USB_DATA, 6, "turn_on_2v7_site_2","OK",turn_on_2v7_site_2);
  usb_cmd_data_setup(&USB_DATA, 7, "turn_on_2v7_site_3","OK",turn_on_2v7_site_3);
  usb_cmd_data_setup(&USB_DATA, 8, "resistor_120kohm","OK",resistor_120kohm);
  usb_cmd_data_setup(&USB_DATA, 9, "resistor_33kohm","OK",resistor_33kohm);
  usb_cmd_data_setup(&USB_DATA, 10, "resistor_3R3kohm","OK",resistor_3R3kohm);
  usb_cmd_data_setup(&USB_DATA, 11, "resistor_330ohm","OK",resistor_330ohm);
  usb_cmd_data_setup(&USB_DATA, 12, "resistor_200ohm","OK",resistor_200ohm);
  usb_cmd_data_setup(&USB_DATA, 12, "resistor_100ohm","OK",resistor_100ohm);
}

void UART0_IRQHandler(void) { UART_Interface_IRQ(&USB_UART); }

void TIMA0_IRQHandler(void) { Timer_Timeout_IRQ(&USB_Timeout); }

void TIMG7_IRQHandler(void) { Delay_Timer_IRQ(&USB_BUFFER); }

void SPI0_IRQHandler(void) { SPI_IRQ(&ADC); }
