#include <SanUSB.h> //Programa com protocolo RC5 da Philllips de controle remoto
#include <usb_san_cdc.h>// Biblioteca para comunicação serial virtual

char chegoupc, comando, sistema, bit_rx;
int32 i;

void identifica_bit(void)
   {
      bit_rx=0;
      if (input(pin_b0)==1) {bit_rx=1;} //identifica 0 ou 1
      delay_us(860); // //pula para o próximo período para outra leitura
   }

#int_ext
void san_ext()
{
output_toggle(pin_b6);

sistema=0;
comando=0;
//*************************************************
delay_us(750); //Tempo do start bit 1 com a perda do tempo do primeiro semi-ciclo alto pela interrupção
delay_us(1720); //Tempo do start bit 2
delay_us(1720); //Tempo do toogle bit

delay_us(860); //pula o primeiro semi-ciclo
identifica_bit();
if (bit_rx) sistema|=16; //Bit 5 do byte sistema 0b00010000

delay_us(860); //pula o primeiro semi-ciclo
identifica_bit();
if (bit_rx) sistema|=8; //Bit 4 do byte sistema 0b00001000

delay_us(860); //pula o primeiro semi-ciclo
identifica_bit();
if (bit_rx) sistema|=4; //Bit 3 do byte sistema 0b00000100

delay_us(860); //pula o primeiro semi-ciclo
identifica_bit();
if (bit_rx) sistema|=2; //Bit 2 do byte sistema 0b00000010

delay_us(860); //pula o primeiro semi-ciclo
identifica_bit();
if (bit_rx) sistema|=1; //Bit 1 do byte sistema 0b00000001

//*************************************************

delay_us(860); //pula o primeiro semi-ciclo
identifica_bit();
if (bit_rx) comando|=32; //Bit 4 do byte comando

delay_us(860); //pula o primeiro semi-ciclo
identifica_bit();
if (bit_rx) comando|=16; //Bit 5 do byte comando

delay_us(860); //pula o primeiro semi-ciclo
identifica_bit();
if (bit_rx) comando|=8; //Bit 4 do byte comando

delay_us(860); //pula o primeiro semi-ciclo
identifica_bit();
if (bit_rx) comando|=4; //Bit 3 do byte comando

delay_us(860); //pula o primeiro semi-ciclo
identifica_bit();
if (bit_rx) comando|=2; //Bit 2 do byte comando

delay_us(860); //pula o primeiro semi-ciclo
identifica_bit();
if (bit_rx) comando|=1; //Bit 1 do byte comando
//*************************************************
write_eeprom(0x10,sistema); write_eeprom(0x11,comando);  ////guarda as variáveis decodificadas
while(read_eeprom(0xfd));
printf (usb_cdc_putc,"comando: %x\r\n",read_eeprom(0x11));
delay_ms(500); //Tempo para deixar o receptor cego por um segundo após a primeira atuação da interrupção
}

main() {
clock_int_4MHz();

usb_cdc_init(); // Inicializa o protocolo CDC
usb_init(); // Inicializa o protocolo USB
usb_task(); // Une o periférico com USB do PC //Para depurar o programa em aplicação real
while(!usb_enumerated()); //Aguarda reconhecimento da emulação serial via USB

enable_interrupts (global); // Possibilita todas interrupcoes
enable_interrupts (int_ext); // Habilita interrupcao externa 0 no pino B0 onde está ligado o receptor infravermelho

while(1)
{
if (usb_cdc_kbhit(1)) //avisa se chegou dados do PC
{
chegoupc=usb_cdc_getc(); //se chegou, retém o caractere e compara com 'L' ou 'D'
if (chegoupc=='L') {output_toggle(pin_b6); printf(usb_cdc_putc, "\r\nTesta led!\r\n");}
}
++i; if (i>=10000) {i=0; output_toggle(pin_b7);} //Led de visualização
}}
