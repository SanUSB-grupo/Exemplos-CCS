#include "SanUSB.h"
#include "usb_san_cdc.h"// Biblioteca para comunica��o serial virtual
BYTE Comando;


void main() {
clock_int_4MHz();//Fun��o necess�ria para habilitar o dual clock (48MHz para USB e 4MHz para CPU)
usb_cdc_init(); // Inicializa o protocolo CDC
usb_init(); // Inicializa o protocolo USB
usb_task(); // Une o perif�rico com USB do PC


while (TRUE)
{
   if (usb_cdc_kbhit()) //avisa se chegou dados do PC
      { //verifica se acabou de chegar um novo byte no buffer de recep��o, depois o kbhit � zerado para pr�ximo byte
      comando=usb_cdc_getc(); //se chegou, ret�m o caractere e compara com �L� ou �D�
      if (comando=='L') {output_high(pin_b7); printf(usb_cdc_putc, "\r\nLed Ligado!\r\n");}
      if (comando=='D') {output_low(pin_b7); printf(usb_cdc_putc, "\r\nLed Desligado!\r\n");}
      }

output_high(pin_B6); // Pisca Led na fun��o principal
delay_ms(500);
output_low(pin_B6);
delay_ms(500);}
}
