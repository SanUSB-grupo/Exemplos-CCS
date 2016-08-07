////////////////////////////tinyurl.com/SanUSB/////////////////////////////
#include <SanUSB.h> //http://www.quinapalus.com/hd44780udg.html
                     //Visualiza sequencia http://www.darreltaylor.com/files/CustChar.htm

#include "SmartLCD16x2.c" // funcionou na placa PIC SanUSB de 28 pinos como também na placa de 40 pinos.

//Vale salientar que, com esse princípio, é possível desenvolver jogos e criar estórias animadas
// utilizando esse simples display 16x2

    int i = 0, k = 0;

    char b1[8] = {4,21,14,4,10,10,10};//Desenha boneco 1
    char b2[8] = {4,14,21,4,10,10,10};//Desenha boneco 2
    char b3[8] = {21,14,4,4,10,10,10};//Desenha boneco 3
    char b4[8] = {21,14,4,4,10,17,0};//Desenha boneco 4. O oitavo byte = 0 , pois o padrão é 5x7

    char b5[8] = {31,25,24,31,3,31,31};//Desenha S
  //  char b6[8] = {0,0,14,3,15,27,15};//Desenha a
  //  char b7[8] = {0,0,16,30,19,19,19};//Desenha n
  //  char b8[8] = {0,17,17,17,17,31,31};//Desenha U
  //  char b9[8] = {31,25,24,31,3,31,31};//Desenha S
  //  char b10[8] = {30,27,27,30,27,27,30};//Desenha B

void main(){

    lcd_ini();

    lcd_envia_byte(0, 0x40);//Envia o comando de escrita na CGRAM na primeira posição
    // Enviar código de caracteres personalizados
    // Padrão  5 x 7 ( último byte 0 para a simetria)
    for (i = 0; i < 7; i++) {
        lcd_envia_byte(1, (i % 2 == 0)? 0b10101 : 0b01010);
    }
   lcd_envia_byte(1, 0);

   //EnviaCaracter("\f");//avanço de página
   //EnviaCaracter("\b");///volta um espaço
   //EnviaCaracter("\n");///pula uma linha

    // Cria caracteres usando array de bytes de cima
    for (i = 0; i < 8; i++) {
        lcd_envia_byte(1, b1[i]);
    }
    for (i = 0; i < 8; i++) {
        lcd_envia_byte(1, b2[i]);
    }
    for (i = 0; i < 8; i++) {
        lcd_envia_byte(1, b3[i]);
    }
        for (i = 0; i < 8; i++) {
        lcd_envia_byte(1, b4[i]);
    }
   for (i = 0; i < 8; i++) {
        lcd_envia_byte(1, b5[i]);
    }

    // Envia os caracateres especiais para o display
    EnviaCaracter("\f");
    delay_ms(200);

  lcd_pos_xy(5,1);

  for (k = 0; k < 5; k++) {
    EnviaCaracter(1);
    delay_ms(300);
    EnviaCaracter("\b");//Volta um espaço
    EnviaCaracter(2);
    delay_ms(300);
    EnviaCaracter("\b");
    EnviaCaracter(3);
    delay_ms(300);
    EnviaCaracter("\b");
    EnviaCaracter(4);
    delay_ms(300);
    EnviaCaracter("\b");
          }
    EnviaCaracter(4);
    delay_ms(300);

    EnviaCaracter(5); //Desenha S
    delay_ms(400);
    EnviaCaracter("anUSB");
    delay_ms(500);

    for (k = 0; k < 3; k++) {
    EnviaCaracter(1);
    delay_ms(300);
    EnviaCaracter("\b");//Volta um espaço
    EnviaCaracter(2);
    delay_ms(300);
    EnviaCaracter("\b");
    EnviaCaracter(3);
    delay_ms(300);
    EnviaCaracter("\b");
    EnviaCaracter(4);
    delay_ms(300);
    EnviaCaracter("\b");
          }
    EnviaCaracter(4);
    delay_ms(300);

    lcd_pos_xy(1,2);
    EnviaCaracter(".blogspot.com.br");

    while(TRUE) {
     output_toggle(pin_b7); output_toggle(pin_d7);
     delay_ms(400);

      }
}
