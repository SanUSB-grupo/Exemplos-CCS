#include <SanUSB.h>

short int led;
int x;

#int_timer1
void trata_t1 ()
{
   led = !led; // inverte o led - pisca a cada 0,5 seg.
   output_bit (pin_b7,led);
   set_timer1(3036 + get_timer1());
}


#int_ext
void bot_ext()
{
   for(x=0;x<5;x++) // pisca 5 vezes após o pino ser aterrado (botão pressionado)
   {
   output_high(pin_B6); // Pisca Led em B5
   delay_ms(1000);
   output_low(pin_B6);
   delay_ms(1000);
   }
}

main(){
clock_int_4MHz();

enable_interrupts (global); // Possibilita todas interrupcoes
enable_interrupts (int_timer1); // Habilita interrupcao do timer 1
//enable_interrupts (int_ext); // Habilita interrupcao externa 0 no pino B0
setup_timer_1 ( T1_INTERNAL | T1_DIV_BY_8);// configura o timer 1 em 8 x 62500 = 0,5s
set_timer1(3036);		// Conta 62.500us x 8 para estourar= 0,5s

while (TRUE)
{

output_high(pin_B0); // Pisca Led na função principal
delay_ms(500);
output_low(pin_B0);
delay_ms(500);
	                                         }}



