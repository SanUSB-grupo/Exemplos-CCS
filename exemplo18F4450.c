#include <SanUSB4450.h>

void main()
{
//clock_int_4MHz();

while (1)
   {
   output_toggle(pin_B7); // comuta Led na fun��o principal
   delay_ms(500);
   }
}
