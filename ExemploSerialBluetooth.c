#include <SanUSB.h> //This library 18F4550.h is valid for the whole family USB PIC18Fx5xx
#use delay(clock=48000000)// USB standard frequency (cpu and timers 12 MIPS = 4/48MHz)

#use rs232(baud=19200, xmit=pin_c6, rcv=pin_c7)

char comando, n; //o ultimo caractere é invalido


#INT_RDA
void recepcao_serial()// Interrupicao serial
{
comando=getc(); //somente a primeira letra

if (comando=='A') {output_high(pin_b7); }
if (comando=='B') {output_low(pin_b7); }


}


void main()
{
   enable_interrupts(GLOBAL); // Possibilita todas interrupcoes
   enable_interrupts(INT_RDA); // Habilita interrupcao da serial


   while(1)
   {
   
      
  output_high(pin_B6); // Pisca Led na função principal
delay_ms(500);
output_low(pin_B6);
delay_ms(500);


   }}
