#include <SanUSB.h>

main(){
clock_int_4MHz();

while (1)
{
output_high(pin_B0); // Pisca Led na fun��o principal
delay_ms(500);

output_low(pin_B0);
output_high(pin_B6);
delay_ms(500);

output_low(pin_B6);
output_high(pin_B7);
delay_ms(500);

output_low(pin_B7);
}
}
