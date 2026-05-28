#include "headers.h"

#define USB_CMD_TIMEOUT_US 1000000 // 1000 ms

static const char invalid_cmd[] = "INVALID_COMMAND\r\n";

/* ------------------------------------------------ */
/* COMMAND TABLE SETUP                              */
/* ------------------------------------------------ */

void usb_cmd_data_setup(UART_DATA *param, uint8_t index, const char *cmd,
                        const char *response, process_cmd_cb_t cb_fn) {
  if (index >= MAX_NUM_CMDS)
    return;

  uint8_t len = strlen(cmd);

  memcpy(param->command_table[index].command, cmd, len);

  param->command_table[index].command[len] = '\0';
  param->command_table[index].cmd_len = len;

  if (response != NULL) {
    uint8_t resp_len = strlen(response);

    memcpy(param->command_table[index].response, response, resp_len);

    param->command_table[index].resp_len = resp_len;
  } else {
    param->command_table[index].resp_len = 0;
  }

  param->command_table[index].actions_func = cb_fn;
}

/* ------------------------------------------------ */
/* USB INIT                                         */
/* ------------------------------------------------ */

void usb_init(void) {
  memset(&USB_DATA, 0, sizeof(USB_DATA));

  UART_Interface_Initialize(&USB_UART, UART0, 0, 255, 255);

  Timer_Timeout_Inialize(&USB_Timeout, TIMA0, 0, CPUCLK_FREQ);

  UART_Target_Initialize(&USB_UART, 0, &USB_Timeout, 0, 100000);

  Delay_Timer_Initialize(&USB_BUFFER, TIMG7, 7, CPUCLK_FREQ);

  Delay_Timer_Start(&USB_BUFFER);
}

/* ------------------------------------------------ */
/* USB FSM                                          */
/* ------------------------------------------------ */

void usb_fsm(UART_DATA *param) {
  UART_Target_State state;

  state = UART_Target_getState(param->uartTargetIndex);

  switch (state) {
    /* ---------------------------------------- */
    /* IDLE                                     */
    /* ---------------------------------------- */

  case UART_TARGET_IDLE: {
    param->cmd_index = 0;
    param->command_active = 0;

    UART_Target_Receive(param->uartTargetIndex, &param->rx_byte, 1);

    UART_Target_setState(param->uartTargetIndex, UART_TARGET_WAITING);

    break;
  }

    /* ---------------------------------------- */
    /* WAITING                                  */
    /* ---------------------------------------- */

  case UART_TARGET_WAITING: {
    break;
  }

    /* ---------------------------------------- */
    /* RECEIVING                                */
    /* ---------------------------------------- */

  case UART_TARGET_RECEIVING: {
    break;
  }

    /* ---------------------------------------- */
    /* RECEIVED                                 */
    /* ---------------------------------------- */

  case UART_TARGET_RECEIVED: {
    uint8_t byte = param->rx_byte;

    /* First byte received */
    if (param->command_active == 0) {
      param->command_active = 1;
    }

    /* Restart command timeout */
    param->cmd_start_time = Delay_Timer_Get(&USB_BUFFER);

    /* ---------------------------- */
    /* TERMINATION CHARACTER        */
    /* ---------------------------- */

    if (byte == '\r' || byte == '\n') {
      /* Ignore repeated CR/LF */
      if (param->cmd_index == 0) {
        UART_Target_setState(param->uartTargetIndex, UART_TARGET_WAITING);

        UART_Target_Receive(param->uartTargetIndex, &param->rx_byte, 1);

        break;
      }

      /* Null terminate */
      param->cmd_buffer[param->cmd_index] = '\0';

      param->cmd_len = param->cmd_index;

      /* Process command */
      process_usb_command(param);

      /* Reset command assembly */
      param->cmd_index = 0;
      param->command_active = 0;
    }

    /* ---------------------------- */
    /* NORMAL DATA BYTE             */
    /* ---------------------------- */

    else {
      if (param->cmd_index < (MAX_CMD_LEN - 1)) {
        param->cmd_buffer[param->cmd_index++] = byte;
      } else {
        /* Buffer overflow */
        param->cmd_index = 0;
        param->command_active = 0;

        UART_Target_Transmit(param->uartTargetIndex, (uint8_t *)invalid_cmd,
                             sizeof(invalid_cmd) - 1);
      }
    }

    /* Restart next byte receive */

    UART_Target_setState(param->uartTargetIndex, UART_TARGET_WAITING);

    UART_Target_Receive(param->uartTargetIndex, &param->rx_byte, 1);

    break;
  }

    /* ---------------------------------------- */
    /* SENDING                                  */
    /* ---------------------------------------- */

  case UART_TARGET_SENDING: {
    break;
  }

  default:
    break;
  }

  /* ------------------------------------------------ */
  /* COMMAND ASSEMBLY TIMEOUT                         */
  /* ------------------------------------------------ */

  if (param->command_active) {
    uint32_t now = Delay_Timer_Get(&USB_BUFFER);

    if ((now - param->cmd_start_time) >= USB_CMD_TIMEOUT_US) {
      /* Clear partial command */

      param->cmd_index = 0;
      param->command_active = 0;

      memset(param->cmd_buffer, 0, sizeof(param->cmd_buffer));

      UART_Target_Transmit(param->uartTargetIndex, (uint8_t *)invalid_cmd,
                           sizeof(invalid_cmd) - 1);
    }
  }
}

/* ------------------------------------------------ */
/* VALIDATE COMMAND                                 */
/* ------------------------------------------------ */

USB_errors_t validate_usb_rx_data(UART_DATA *usb_data) {
  for (uint8_t i = 0; i < MAX_NUM_CMDS; i++) {
    if (usb_data->cmd_len == usb_data->command_table[i].cmd_len) {
      if (memcmp(usb_data->cmd_buffer, usb_data->command_table[i].command,
                 usb_data->cmd_len) == 0) {
        executing_command = &usb_data->command_table[i];

        return ERROR_NONE;
      }
    }
  }

  return INVALID_COMMAND;
}

/* ------------------------------------------------ */
/* PROCESS COMMAND                                  */
/* ------------------------------------------------ */

void process_usb_command(UART_DATA *usb_data) {
  if (validate_usb_rx_data(usb_data) == ERROR_NONE) {
    if (executing_command->actions_func != NULL) {
      executing_command->actions_func();
    }

    if (executing_command->resp_len > 0) {
      UART_Target_Transmit(usb_data->uartTargetIndex,
                           executing_command->response,
                           executing_command->resp_len);
    }
  } else {
    UART_Target_Transmit(usb_data->uartTargetIndex, (uint8_t *)invalid_cmd,
                         sizeof(invalid_cmd) - 1);
  }
}


