#ifndef VARIABLES_H_
#define VARIABLES_H_

 UART_Interface USB_UART;
 Timer_Timeout USB_Timeout;
 UART_DATA USB_DATA;
 USB_command_map_t *executing_command;
 Delay_Timer USB_BUFFER;
 SPI_Interface ADC;

#endif