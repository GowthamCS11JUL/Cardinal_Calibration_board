#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stdbool.h>

void Max5719GSD_init(void);

bool Max5719GSD_write(uint32_t voltage_val);

#endif /* ADC_H_ */