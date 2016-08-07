#include <SanUSB.h>

void main(){
clock_int_4MHz();

while (TRUE)
{

output_high(pin_B0); // Verde
delay_ms(1000);

output_low(pin_B0);
output_high(pin_B6);  //Amarelo
delay_ms(500);

output_low(pin_B6); //Vermelho
output_high(pin_B7);
delay_ms(1000);
output_low(pin_B7);
}
}
