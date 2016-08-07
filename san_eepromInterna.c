/////////////////////////////////////////////////////////////////////////
//// exemplo_san_eeprom2550                                          ////
/////////////////////////////////////////////////////////////////////////
#include <SanUSB.h> //Programa que grava valores de 16 bits de um potenciômetro em uma EEPROM externa via i2c e lê a memória via emulação serial
#include <usb_san_cdc.h>// Biblioteca para emulação da comunicação serial

#rom int 0xf00000={'S','A','N'}  // Escreve no endereço inicial da EEPROMint (no 18F é 0xf00000)

BYTE i, j, endereco, valor;
boolean led;

main() {
clock_int_4MHz();
   usb_cdc_init(); // Inicializa o protocolo CDC
   usb_init();    // Inicializa o protocolo USB
   while(!usb_cdc_connected()) {}  // espere enquanto o protocolo CDC não se conecta com o driver CDC
   usb_task();  // Une o periférico com a usb do PC
   usb_wait_for_enumeration();      //espera até que a USB do Pic seja reconhecida pelo PC

   output_high(pin_b7);  // Sinaliza comunicação USB Ok

while (1) {
         printf(usb_cdc_putc, "\r\n\nEEPROM:\r\n"); // Display contém os primeiros 64 bytes em hex
         for(i=0; i<=3; ++i) {
            for(j=0; j<=15; ++j) {
               printf(usb_cdc_putc, "%2x ", read_eeprom( i*16+j ) );
            }
            printf(usb_cdc_putc, "\n\r");
         }

         printf(usb_cdc_putc, "\r\nEndereco para escrever: ");
         endereco = gethex_usb();
         printf(usb_cdc_putc, "\r\nNovo valor: ");
         valor = gethex_usb();

         write_eeprom( endereco, valor );
led = !led; // inverte o led de teste
output_bit (pin_b7,led);
      }
}
