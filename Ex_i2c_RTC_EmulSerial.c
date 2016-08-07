//PROGRAMA PARA CONFIGURAR E LER UM RELÓGIO RTC I2C VIA MONITOR SERIAL/////////////////////
#include "SanUSB.h"
#include "usb_san_cdc.h"// Biblioteca para emulação da comunicação serial
#include "i2c_sanusb.c"

Char entrada,funcao,endrtc,valorrtc1,valorrtc2;
unsigned int endereco, valor,valorbcd, numquant;
boolean led;
/************************************************************************************************
* Conversão BCD P/ DECIMAL
************************************************************************************************/
int bcd_to_dec(int valorb)
{
int temp;
temp = (valorb & 0b00001111);
temp = (temp) + ((valorb >> 4) * 10);
return(temp);
}
/*************************************************************************************************
* Conversão DECIMAL p/ BCD
************************************************************************************************/
int dec_para_bcd(unsigned int valord)
{
return((0x10*(valord/10))+(valord%10));//Coloca a parte alta da divisão por 10 no nibble mais significativo
}
//////////////////////////////////////////////////////////////////////////////////
main() {
clock_int_4MHz();
usb_cdc_init(); // Inicializa o protocolo CDC
usb_init(); // Inicializa o protocolo USB
usb_task(); // Une o periférico com a usb do PC

while (1) {

//******************************************************************************
if (usb_cdc_kbhit(1)) { //verifica se acabou de chegar um novo dado no buffer de recepção, depois o kbhit é zerado

entrada=usb_cdc_getc(); //comando é o Byte recebido pela serial usb_cdc_putc,
if (entrada=='A')
{ funcao=usb_cdc_getc();
switch (funcao) //UTILIZAR VALORES DECIMAIS EM DOIS DIGITOS. ex:06 ou 23 ou 15
{
////////////////////////FUNCAO 4: CONFIGURA RELÓGIO//////////////////////////////Ex: A4H09
case '4':
{
endrtc=usb_cdc_getc();
valorrtc1=usb_cdc_getc();
valorrtc2=usb_cdc_getc(); //Ex: A4M43 - Altera os minutos para 43
if (endrtc=='H') { endereco=2;} //Escreve o endereco das horas
if (endrtc=='M') { endereco=1;} //Escreve o endereco dos minutos
if (endrtc=='S') { endereco=0;} //Escreve o endereco dos segundos
if (endrtc=='D') { endereco=4;} //Escreve o endereco do dia
if (endrtc=='N') { endereco=5;} //Escreve o endereco do mes
if (endrtc=='Y') { endereco=6;} //Escreve o endereco do ano
if (valorrtc1>='0'&&valorrtc1<='9') {numquant=(valorrtc1-0x30);}
if (valorrtc2>='0'&&valorrtc2<='9') {numquant=numquant*10+(valorrtc2-0x30);
valor=numquant;
if (endereco==0) { if(valor>59) {valor=0;}}
if (endereco==1) { if(valor>59) {valor=0;}}
if (endereco==2) { if(valor>23) {valor=0;}}
if (endereco==4) { if(valor>31) {valor=1;}}
if (endereco==5) { if(valor>12) {valor=1;}}
if (endereco==6) { if(valor>99) {valor=0;}}
//---------Converte byte hexadecimal para byte BCD decimal --------------
valorbcd=dec_para_bcd(valor);
//-----------------------------------------------------------------------
escreve_rtc(endereco,valorbcd); //Valor1 é byte BCD (decimal).
printf(usb_cdc_putc,"\r\nA5 %2x:%2x:%2x",le_rtc(2), le_rtc(1),le_rtc(0)); //BCD em hexadecimal representa o decimal
printf(usb_cdc_putc," %2x%2x%2x\r\n",le_rtc(4), le_rtc(5), le_rtc(6));
}
}
break;
//////////////////////FUNCAO 5: LÊ RELÓGIO////////////////////////////Ex: A5- Lê o relógio e o calendário
case '5':
printf(usb_cdc_putc,"\r\nA5 %2x:%2x:%2x",le_rtc(2), le_rtc(1),le_rtc(0));//BCD em hexadecimal representa o decimal
printf(usb_cdc_putc," %2x%2x%2x\r\n",le_rtc(4), le_rtc(5), le_rtc(6));
break;
}}}
//******************************************************************************
led = !led; // inverte o led de teste
output_bit (pin_b7,led);
delay_ms(500);
}
}
