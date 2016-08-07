#include "SanUSB.h"
#include "usb_san_cdc.h"// Biblioteca para comunicação serial virtual
unsigned char Comando,c;


void main() {
usb_cdc_init(); // Inicializa o protocolo CDC
usb_init(); // Inicializa o protocolo USB
usb_task(); // Une o periférico com USB do PC
while(!usb_enumerated());
while(!usb_cdc_connected());
//output_high(pin_d7);

while (TRUE)
{

      if (kbhit()) {
      
         c=getc();
         if (c=='\n') {usb_cdc_putc('\n');}
         if (c=='\r') {usb_cdc_putc('\r');}
         else {usb_cdc_putc(c);}
                  }
     if (usb_cdc_kbhit()) {
         c=usb_cdc_getc();
         if (c=='\n') { putc('\n');}
         if (c=='\r') {putc('\r'); }
         else {putc(c);}
                          }

}
}
