// Biblioteca para desenhar caracteres no LCD 16x2
//tinyurl.com/SanUSB
//*
#ifndef LCD_DB4 //Ligação nos pinos do LCD (4 pinos de dados e dois e controle (E e RS) - 4-bit mode)
#define LCD_DB4   PIN_B2
#define LCD_DB5   PIN_B3
#define LCD_DB6   PIN_B4
#define LCD_DB7   PIN_B5
#define LCD_E     PIN_B1
#define LCD_RS    PIN_B0
//*/
/*
#ifndef LCD_DB4
#define LCD_DB4   PIN_B0
#define LCD_DB5   PIN_B1
#define LCD_DB6   PIN_B2
#define LCD_DB7   PIN_B3
#define LCD_E     PIN_B4
#define LCD_RS    PIN_B5
//*/

#include "lcd.h.encrypted"
// Posição do cursor no display (1, 1) na linha de cima à esquerda
void lcd_pos_xy(int8 x, int8 y) {
    int8 address;
    address = (y != 1)? lcd_line_two : 0;
    address += x-1;
    lcd_envia_byte(0, 0x80 | address);
}


// Escreve caracteres para o display
void EnviaCaracter(char c) {
    switch(c) {
        case '\f':
            lcd_envia_byte(0,1);
            delay_ms(2);
            break;

        case '\n':
            lcd_pos_xy(1,2);
            break;

        case '\b':
            lcd_envia_byte(0,0x10);
            break;

        default:
            lcd_envia_byte(1,c);
            break;
    }
}


