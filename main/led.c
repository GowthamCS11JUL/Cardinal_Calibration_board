#include "headers.h"
#include "ti/driverlib/dl_gpio.h"
#include "variables.h"

void led_init(void)
{
  DL_GPIO_initDigitalOutput(Led_D4_IOMUX);
  DL_GPIO_enableOutput(Led_PORT, Led_D4_PIN);
}
void led_on(void)
{
    DL_GPIO_setPins(Led_PORT, Led_D4_PIN);
      memcpy(executing_command->response,"PASS",4);
      executing_command->resp_len=4;
}
void led_off(void)
{
DL_GPIO_clearPins(Led_PORT, Led_D4_PIN);
      memcpy(executing_command->response,"PASS",4);
      executing_command->resp_len=4;
}