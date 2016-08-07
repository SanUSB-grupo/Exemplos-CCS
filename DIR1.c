#include "SanUSB4.h" //Mais detalhes em http://www.youtube.com/watch?v=7O9a0E_WXPA

#define botao PIN_E3
#define botao1 PIN_A0

int16 i;
signed int j=0, disparo=0;
char chegoupc, comando, sistema, bit_rx, flag=0;

#INT_EXT
void CruzaPor0()
{
delay_us(800); //devido a detec��o de interrup. j� com 2,5V como zero,
//o inicio para o disparo se encontra ainda no semi-ciclo anterior, por isso,
//o delay de inicial para entrar no pr�ximo semi-ciclo
delay_ms(disparo); //Para 60 Hz cada semi-ciclo aprox. 8,33ms

                               output_high(PIN_B6); //dispara triac
                               delay_us(100);
                               output_low(PIN_B6);
}

void main()
{
clock_int_4MHz(); //Fun��o necess�ria para habilitar o dual clock (48MHz para USB e 4MHz para CPU)

   disparo=read_eeprom(10);  //carrega o �ltimo valo ajustado
   if (disparo==0xff) {disparo=0; write_eeprom(10,0);} //inicio de opera��o ap�s grava��o

   enable_interrupts(GLOBAL);
   enable_interrupts(INT_EXT);
   //enable_interrupts(INT_EXT1);
   ext_int_edge(L_TO_H);

 while(true)
   {
   ++i; if (i>=50000) {i=0; output_toggle(pin_b7);} //Led de visualiza��o

      if(!input(botao))//bot�o de incremento de fase
      {  delay_ms(100);   while(!input(botao))  delay_ms(100); //filtro bot�o
         disparo++; // na pr�tica est� identificando o zero s� uma vez por ciclo
         if(disparo>=7) {disparo=7;} //o bot�o no pino E3 regula o �ngulo de disparo
         write_eeprom(10, disparo);
         
      }

    if(!input(botao1))
      {  delay_ms(100);   while(!input(botao1))  delay_ms(100);
         disparo--;
         if(disparo<=1) {disparo=1;}
         write_eeprom(10, disparo);
        }

   }
}
