#include <SanUSB.h> //Mais detalhes em http://www.youtube.com/watch?v=7O9a0E_WXPA

#define botao PIN_E3
#define botao1 PIN_A0

int16 i;
signed int j=0, disparo=0;
char chegoupc, comando, sistema, bit_rx, flag;

void identifica_bit(void)
   {
      bit_rx=0;
      if (input(pin_b0)==1) {bit_rx=1;} //identifica 0 ou 1
      delay_us(860); // //pula para o próximo período para outra leitura
   }

#int_ext
void san_ext()
{
disable_interrupts(INT_EXT1);

sistema=0;
comando=0;
//*************************************************
delay_us(700); //Diminuir de 750 pelo break etc. Tempo do start bit 1 com a perda do tempo do primeiro semi-ciclo alto pela interrupção
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
while(read_eeprom(0xfd));
if (comando==1) {output_toggle(pin_b7); disparo++; if(disparo>=8) {disparo=8;}}
if (comando==2) {output_toggle(pin_b7); disparo--; if(disparo<=0) {disparo=0;}}

enable_interrupts(INT_EXT1);
}


#INT_EXT1
void CruzaPor0()
{
output_low(PIN_B6);
if (!input(pin_b0)) break;
delay_us(500); //devido a detecção de interrup. já com 2,5V como zero,
//o inicio para o disparo se encontra ainda no semi-ciclo anterior, por isso,
//o delay de inicial para entrar no próximo semi-ciclo
delay_ms(disparo); //Para 60 Hz cada semi-ciclo aprox. 4,33ms

                 if(flag==0){  output_high(PIN_B6); //dispara triac
                               delay_us(300);
                               //output_low(PIN_B6);
                               }

   if (j==0){
   j=1;
   ext_int_edge(H_TO_L); // Muda a interrupção da borda de subida para descida da senóide
   }

   else {
   j=0;
   ext_int_edge(L_TO_H); // Muda a interrupção da borda de descida para subida da senóide
   }
}

void main()
{
clock_int_4MHz(); //Função necessária para habilitar o dual clock (48MHz para USB e 4MHz para CPU)

   disparo=read_eeprom(10);  //carrega o último valo ajustado
   if (disparo==0xff) {disparo=0; write_eeprom(10,0);} //inicio de operação após gravação

   enable_interrupts(GLOBAL);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
   ext_int_edge(L_TO_H);

 while(true)
   {
   ++i; if (i>=50000) {i=0; output_toggle(pin_b7);} //Led de visualização

      if(!input(botao))//botão de incremento de fase
      {  delay_ms(100);   while(!input(botao))  delay_ms(100); //filtro botão
         disparo++; // na prática está identificando o zero só uma vez por ciclo
         if(disparo>=8) {disparo=8;} //o botão no pino E3 regula o ângulo de disparo
         write_eeprom(10, disparo);
         enable_interrupts(INT_EXT1);
      }

    if(!input(botao1))
      {  delay_ms(100);   while(!input(botao1))  delay_ms(100);
         disparo--;
         if(disparo<=0) {disparo=0;}
         write_eeprom(10, disparo);
         enable_interrupts(INT_EXT1);
      }

   }
}
