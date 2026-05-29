

#include "headers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ------------------------------------------------ */
/* RESISTOR TABLE                                   */
/* ------------------------------------------------ */

static const Resistor_Map_t resistor_table[] = {{"120K", Relay_EN_4},

                                                {"33K", Relay_EN_5},

                                                {"3R3K", Relay_EN_6},

                                                {"330", Relay_EN_7},

                                                {"200", Relay_EN_8},

                                                {"100", Relay_EN_9}};

/* ------------------------------------------------ */
/* DAC VALUE CONVERSION                             */
/* ------------------------------------------------ */

/*
 * Convert millivolt value to DAC code
 *
 * Modify this table based on your calibration
 */

static uint32_t voltage_to_dac(uint32_t millivolt) 
{
millivolt=millivolt*1048575UL/5000UL; 
return millivolt;
}

/* ------------------------------------------------ */
/* POWER COMMAND HANDLER                            */
/* ------------------------------------------------ */

/*
 * COMMAND FORMAT:
 *
 * POWER_SET_3300_1
 *
 * tokens[0] = POWER
 * tokens[1] = SET
 * tokens[2] = 3300
 * tokens[3] = 1
 */

void power_command_handler(

    UART_DATA *usb_data,

    Parsed_Command_t *cmd) {
  uint32_t voltage_mv;

  uint32_t site;

  uint32_t dac_code;

  /* -------------------------------------------- */
  /* TOKEN COUNT CHECK                            */
  /* -------------------------------------------- */

  if (cmd->token_count < 4) {
    UART_Target_Transmit(

        usb_data->uartTargetIndex,

        (uint8_t *)"INVALID_POWER_FORMAT\r\n",

        22);

    return;
  }

  /* -------------------------------------------- */
  /* SUBCOMMAND CHECK                             */
  /* -------------------------------------------- */

  if (strcmp(

          cmd->tokens[1],

          "SET"

          ) != 0) {
    UART_Target_Transmit(

        usb_data->uartTargetIndex,

        (uint8_t *)"INVALID_POWER_CMD\r\n",

        19);

    return;
  }

  /* -------------------------------------------- */
  /* PARSE VALUES                                 */
  /* -------------------------------------------- */

  voltage_mv = atoi(cmd->tokens[2]);

  site = atoi(cmd->tokens[3]);

  /* -------------------------------------------- */
  /* DAC VALUE                                    */
  /* -------------------------------------------- */

  dac_code = voltage_to_dac(voltage_mv);

  if (dac_code == 0) {
    UART_Target_Transmit(

        usb_data->uartTargetIndex,

        (uint8_t *)"INVALID_VOLTAGE\r\n",

        17);

    return;
  }

  /* -------------------------------------------- */
  /* DAC WRITE                                    */
  /* -------------------------------------------- */

  Max5719GSD_write(dac_code);

  /* -------------------------------------------- */
  /* SITE SELECTION                               */
  /* -------------------------------------------- */

  switch (site) {
  case 1:

    relay_on_voltage(Relay_EN_1);

    break;

  case 2:

    relay_on_voltage(Relay_EN_2);

    break;

  case 3:

    relay_on_voltage(Relay_EN_3);

    break;

  default:

    UART_Target_Transmit(

        usb_data->uartTargetIndex,

        (uint8_t *)"INVALID_SITE\r\n",

        14);

    return;
  }

  /* -------------------------------------------- */
  /* RESPONSE                                     */
  /* -------------------------------------------- */

  sprintf(

      (char *)usb_data->tx_buffer,

      "POWER_%u_SITE_%u_OK\r\n",

      voltage_mv,

      site);

  UART_Target_Transmit(

      usb_data->uartTargetIndex,

      usb_data->tx_buffer,

      strlen((char *)usb_data->tx_buffer));
}

/* ------------------------------------------------ */
/* RESISTOR COMMAND HANDLER                         */
/* ------------------------------------------------ */

/*
 * COMMAND FORMAT:
 *
 * RESISTOR_SET_120K
 *
 * tokens[0] = RESISTOR
 * tokens[1] = SET
 * tokens[2] = 120K
 */

void resistor_command_handler(

    UART_DATA *usb_data,

    Parsed_Command_t *cmd) {
  /* -------------------------------------------- */
  /* TOKEN COUNT CHECK                            */
  /* -------------------------------------------- */

  if (cmd->token_count < 3) {
    UART_Target_Transmit(

        usb_data->uartTargetIndex,

        (uint8_t *)"INVALID_RESISTOR_FORMAT\r\n",

        25);

    return;
  }

  /* -------------------------------------------- */
  /* SUBCOMMAND CHECK                             */
  /* -------------------------------------------- */

  if (strcmp(

          cmd->tokens[1],

          "SET"

          ) != 0) {
    UART_Target_Transmit(

        usb_data->uartTargetIndex,

        (uint8_t *)"INVALID_RESISTOR_CMD\r\n",

        22);

    return;
  }

  /* -------------------------------------------- */
  /* SEARCH TABLE                                 */
  /* -------------------------------------------- */

  for (uint8_t i = 0;

       i < (sizeof(resistor_table) / sizeof(resistor_table[0]));

       i++) {
    if (strcmp(

            cmd->tokens[2],

            resistor_table[i].resistor_name

            ) == 0) {
      relay_on_resistor_select(

          resistor_table[i].relay);

      sprintf(

          (char *)usb_data->tx_buffer,

          "RESISTOR_%s_OK\r\n",

          resistor_table[i].resistor_name);

      UART_Target_Transmit(

          usb_data->uartTargetIndex,

          usb_data->tx_buffer,

          strlen((char *)usb_data->tx_buffer));

      return;
    }
  }

  /* -------------------------------------------- */
  /* UNKNOWN VALUE                                */
  /* -------------------------------------------- */

  UART_Target_Transmit(

      usb_data->uartTargetIndex,

      (uint8_t *)"INVALID_RESISTOR\r\n",

      19);
}
