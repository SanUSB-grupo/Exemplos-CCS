#include <SanUSB.h> //Servo_motor de parabólica - Apresenta 3 posições definidas 0, 90 e 180 graus

int16 FRENTE=200, TRAS=200; //no servo de teste 200 passos corresponderam a aprox. 1 volta

void main()
{
clock_int_4MHz();


while (1)
   {

   while (FRENTE>0)
             {
               FRENTE--;
               output_high(pin_b0);
               delay_ms(1);        // tempo de busca de 0 graus
               output_low(pin_b0);
               delay_ms(10);
             }
            FRENTE=200;

//output_toggle(pin_b7);


  while (TRAS>0)
             {
               TRAS--;
               output_high(pin_b0);
               delay_ms(2);       // tempo de busca de 180 graus
               output_low(pin_b0);
               delay_ms(10);
             }
            TRAS=200;

 output_toggle(pin_b7);

     }
}
