///////////////////http://br.groups.yahoo.com/group/GrupoSanUSB/////////////////
#include <18F4550.h> //This library 18F4550.h is valid for the whole family USB PIC18Fx5xx

#byte OSCCON=0XFD3
#byte SPBRGH=0xFB0
#byte SPBRG=0xFAF
#byte BAUDCON= 0xFB8
#byte TXSTA=0xFAC
#byte RCSTA=0xFAB
#BYTE RCREG=0xFAE
#BYTE TXREG=0xFAD
#BYTE PIE1=0xF9D
#BIT TRMT=TXSTA.1
#BIT RCIE=PIE1.5
#bit BRG16=BAUDCON.3
#BYTE INTCON=0xFF2


#device ADC=10
#fuses HSPLL,PLL5, USBDIV,CPUDIV1,VREGEN,NOWDT,NOPROTECT,NOLVP,NODEBUG
#use delay(clock=48000000)// USB standard frequency (cpu and timers 12 MIPS = 4/48MHz)
//#use delay(clock=4000000) // internal Oscillator Clock of 4MHz
//#use rs232(baud=19200, xmit=pin_c6, rcv=pin_c7)

//SanUSB program memory allocation
#define CODE_START 0x1000
#build(reset=CODE_START, interrupt=CODE_START+0x08)
#org 0, CODE_START-1 {}

void serial_putc(char c)
{
while (!TRMT);
TXREG=c;
}

/*************************************************************************************/
void taxa_serial(unsigned long taxa) { //Modo 16 bits(bits BRG16=1 e BRGH=1)
unsigned long baud_sanusb; //es klappt nut mit long
while(read_eeprom(0b11111101));
    set_tris_c(0b10111111); 
     TXSTA = 0x24;       
     RCSTA = 0x90;       
     BAUDCON = 0x08;     

  baud_sanusb = ((48000000/4)/ taxa) - 1;
  SPBRGH = (unsigned char)(baud_sanusb >> 8);
  SPBRG = (unsigned char)baud_sanusb;

				                       }

