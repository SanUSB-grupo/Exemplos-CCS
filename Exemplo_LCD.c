////////////////////////////Cabeçalho Padrão////////////////////////////////
#include <SanUSB.h>
#include "MOD_LCD_SANUSB.c" // RB0-RS(4), RB1-EN(6), RB2-D4(11), RB3-D5(12), RB4-D6(13), RB5-D7(14)

int16 temperatura;
int8 x;
int1 led;

main() {
//clock_int_4MHz();
lcd_ini(); // Configuração inicial do LCD

setup_adc_ports(AN0);  //Habilita entradas analógicas - A0
setup_adc(ADC_CLOCK_INTERNAL);
delay_ms(100);
printf(lcd_escreve,"AUTOMACAO FERRAMENTA SanUSB ");

while (1) {
set_adc_channel(0);
delay_ms(10);
temperatura=500*read_adc()/1023; // Sensor de temperatura LM35

lcd_pos_xy(1,2); // Posiciona segunda linha
printf(lcd_escreve,"TEMPERATURA ATUAL=%lu C",temperatura);

for (x = 0; x < 15; x ++) // repete o bloco abaixo por 15 vezes
{
lcd_envia_byte(0,0x18); // rola display um caractere para esquerda
lcd_envia_byte(0,0x0C); //Apaga o cursor

led=!led; output_bit(pin_d7,led);
delay_ms(500);
}
                                           }}
