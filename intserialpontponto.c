#include <SanUSB.h> //Programa para ligar os pinos Tx(17) e Rx(18) cruzados de dois microcontroladores para comandar o chaveamento
		             // de leds nos pinos B6 por interrupção serial
#INT_RDA
void recepcao_serial()// Interrupicao serial
{
char escravo,estado;
escravo=getc(); //comando é o Byte recebido pela serial
if (escravo=='A')
{

estado=getc();
switch (estado)
{
case '0': {output_high(pin_B6);}
break;
case '1': {output_low(pin_B6);}
break;
}
}
}

main()
{
Clock_int_4MHz();
enable_interrupts(GLOBAL); // Possibilita todas interrupcoes
enable_interrupts(INT_RDA); // Habilita interrupcao da serial
output_low(PIN_b6);

//##############################################################################
output_low(PIN_A4); //  se utilizar Max485, inicia em modo de recepção
//##############################################################################
while(1)
{
//##############################################################################
output_high(PIN_A4); //Habilita Max485 em modo de Transmissão
printf ("A0\r\n"); //Transmite dado
output_low(PIN_A4); //Habilita Max485 em Modo de Recepção
//##############################################################################
output_high(pin_B7);
delay_ms (1000);
//##############################################################################
output_high(PIN_A4); //Habilita Max485 em modo de Transmissão
printf ("A1\r\n"); //Transmite dado
output_low(PIN_A4); //Habilita Max485 em Modo de Recepção
//##############################################################################
output_low(pin_B7);// Apaga
delay_ms (1000);
}
}
