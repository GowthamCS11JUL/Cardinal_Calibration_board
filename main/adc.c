#include "headers.h"
#include <stdbool.h>

void Max5719GSD_init(void) {
  SPI_Initialize(&ADC, SPI_0_INST, 0);
  DL_GPIO_setPins(MCU_SPI_PORT, MCU_SPI_CS0_PIN);
  DL_GPIO_clearPins(MCU_SPI_PORT, MCU_SPI_LDAC_BAR_PIN);
}


bool Max5719GSD_write(uint32_t voltage_val) {
  uint32_t dac_value;

  uint16_t write_data[2] = {0};

  uint16_t read_data[2] = {0};

  dac_value = voltage_val & 0xFFFFF;

  write_data[0] = (dac_value >> 16) & 0x000F;

  write_data[1] = dac_value & 0xFFFF;

  DL_GPIO_clearPins(MCU_SPI_PORT, MCU_SPI_CS0_PIN);
  delay_cycles(20);
  DL_GPIO_setPins(MCU_SPI_PORT, MCU_SPI_LDAC_BAR_PIN);
  delay_cycles(20);
  DL_GPIO_clearPins(MCU_SPI_PORT, MCU_SPI_CS0_PIN);

  SPI_Transact(&ADC, write_data, 2, read_data, 2);

  DL_GPIO_setPins(MCU_SPI_PORT, MCU_SPI_CS0_PIN);
  delay_cycles(20);
  DL_GPIO_setPins(MCU_SPI_PORT, MCU_SPI_LDAC_BAR_PIN);
  delay_cycles(20);
  DL_GPIO_clearPins(MCU_SPI_PORT, MCU_SPI_LDAC_BAR_PIN);

  return true;
}
