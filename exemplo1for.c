#include "SanUSB.h"

int8 i,j;

void main()
{
clock_int_4MHz();

while (1)
   {
 for(i=0; i<5; ++i) {
            for(j=0; j<i; ++j) {
               output_toggle(pin_B7); // comuta Led na fun��o principal
                 delay_ms(100);
            }
             delay_ms(500);
         }


   //output_toggle(pin_B7); // comuta Led na fun��o principal
   //delay_ms(500);

   }
}




