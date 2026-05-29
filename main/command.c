#include "headers.h"

void resistor_120kohm(void)
{
relay_on_resistor_select(Relay_EN_4);
}

void resistor_33kohm(void)
{
relay_on_resistor_select(Relay_EN_5);
}

void resistor_3R3kohm(void)
{
relay_on_resistor_select(Relay_EN_6);
}

void resistor_330ohm(void)
{
relay_on_resistor_select(Relay_EN_7);
}

void resistor_200ohm(void)
{
relay_on_resistor_select(Relay_EN_8);
}

void resistor_100ohm(void)
{
relay_on_resistor_select(Relay_EN_9);
}

void turn_on_3v3_site_1(void)
{
Max5719GSD_write(0xCE3FF);
relay_on_voltage(Relay_EN_1);
}

void turn_on_3v3_site_2(void)
{
Max5719GSD_write(0xCE3FF);
relay_on_voltage(Relay_EN_2);  
}
void turn_on_3v3_site_3(void)
{
Max5719GSD_write(0xCE3FF);
relay_on_voltage(Relay_EN_3);   
}

void turn_on_2v7_site_1(void)
{
Max5719GSD_write(0xA8BFF);    
relay_on_voltage(Relay_EN_1);
}

void turn_on_2v7_site_2(void)
{
Max5719GSD_write(0xA8BFF);
relay_on_voltage(Relay_EN_2);     
}

void turn_on_2v7_site_3(void)
{
Max5719GSD_write(0xA8BFF);
relay_on_voltage(Relay_EN_3);   
}
