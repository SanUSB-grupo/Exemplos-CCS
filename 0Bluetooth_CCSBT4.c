/***************************************************************************
 Grupo: www.tinyurl.com/SanUSB - Versao Modem Slave - CCS Compiler
 video-aulas: www.youtube.com/SanUSB2

 Funciona para todos os APKs disponiveis em :https://play.google.com/store pesquisar por SanUSB.

 Video-aulas: http://www.youtube.com/watch?v=vtS2rq_sO5M ,  http://www.youtube.com/watch?v=5bOcVZqi0GM ,

 http://www.youtube.com/watch?v=k2quWQlc-ro e https://www.youtube.com/watch?v=V65-Vt91rug

 Mercado Livre: http://lista.mercadolivre.com.br/sanusb

 Baixar MPLABX e C18: https://dl.dropbox.com/u/101922388/BaixarMPLABX_C18.pdf
 **********************************************************************************/
#include <SanUSBT.h>

#define pinoblue pin_b0       //pinos para serem conectados ao led RGB
#define pinogreen pin_b1
#define pinored pin_b2


short int pisca=0, chegou=0, flag=0, c=0, flagRGB=0, rgb_interrupt = 0, flagstart=0, flagBD=0, vorbei=0, zeit=1;
unsigned char comando[30], comand[30], n=0, m=0, k=0, c1=0, c2=0;
unsigned char G=32, ru=32, po=32, e=32, Fe=32, rr=32;
unsigned char am=32, en=32, ta=32, ti=32, ny=32, url=32, pon=32, to=32, com=32, ba=32, rra=32;
unsigned char S=130>>1, a=168>>1, an=86>>1, u=132>>1,us=130>>1, b=170>>1,x=136>>1,z=106>>1;
unsigned int i=0,j=0;

#INT_RDA
void recepcao_serial()
{
comando[n]=RCREG; m=n;comand[n]= comando[n];

   if (comando[0]!='L' && flagstart==0) {flagstart=1; flagBD=1; zeit=1; n=0;}

   if (comando[0]==65) {flag=1;pisca=0;zeit=1; }
++n;

switch (comando[0])
   {
      case  79 : { chegou=1; flag=0; m=0; flagBD=0;}
            break;

     /* case 'R' : { if (n>=4)  {comand[1]=255-comando[1]; //Led RGB anodo comum//
         comand[2]=255-comando[2];comand[3]= 255-comando[3]; n=0; comando[0]=32;
         output_toggle(pin_b7); chegou=0; zeit=0;}} //Anodo comum
          break; */

        case 'R' : { if (n>=4)  {comand[1]=comando[1]; //Led RGB catodo comum//
        comand[2]=comando[2];comand[3]= comando[3]; n=0; comando[0]=32;
        output_toggle(pin_b7); chegou=0; zeit=0;}} //Catodo comum
         break;

      case 'L' : {flag=0; n=0; c=1; chegou=0; zeit=1;output_high(pin_B7);pisca=0;}
            break;
      case 'D' : {flag=0; n=0; chegou=0; zeit=1;output_low(pin_B7);pisca=0;}
            break;
      case 'P': { pisca=1; flag=0; n=0; chegou=0; zeit=1; }
            break;
   }
}

void main()
{
  taxa_serial(9600);
  enable_interrupts(GLOBAL);
  enable_interrupts(INT_RDA);
  #priority rda //serial

   for(k=0;k<=25;k++){comando[k]=32;}
   for(k=0;k<=25;k++){comand[k]=32;}

 //Es vesucht mindestens einmal shreiben, wenn es lehr ist.
   SPBRGH = 0x02; SPBRG = 0x70;

   while(1)
   {
while (pisca==1){output_toggle(pin_B7);delay_ms (300);n=0;m=0;}

while (chegou==1){ output_toggle(pin_B7);delay_ms(200); if(flagBD==0 && c1==3){ c1=2; write_eeprom(251,2);}
                   serial_putc(79);serial_putc(75);serial_putc(32);n=0; }

if (flagBD==1 && chegou==0 && c==0){
  SPBRGH = 0x04; SPBRG = 0xE1;
  serial_putc(S);serial_putc(a);serial_putc(an);serial_putc(u);serial_putc(us);
  serial_putc(b);serial_putc(x);serial_putc(z);
  delay_ms(1000); output_toggle(pin_b7);
  SPBRGH = 0x02; SPBRG = 0x70;
                                    }

        if (flag==1) { flag=0; output_toggle(pin_b7);

                  if (m==12) {comand[1]=a;comand[3]=78;comand[5]=77;comand[8]=S;comand[10]=b;comand[12]=u;
                  for(k=0;k<=m;k++){serial_putc(comand[k]);}
                  for(k=m+1;k<25;k++){serial_putc(32);}
                   ++j;if(j>=5){j=0;flagBD=1;}
                             }
      write_eeprom(250,m); //PLatz von m-Byte-Zaeler

      if (c==1){ 
      for(k=0;k<=25;k++){serial_putc(comand[k]);}
      for(k=0;k<=25;k++){comando[k]=32;comand[k]=32;}
      n=0;m=0; }

       delay_ms(1000); }

if(chegou==0 && zeit==1){
      c1=read_eeprom(251);if(c1==255){++c2;if(c2>3){write_eeprom(251,3);}}//Das erste Lesen ist 255
      if (c==0 && c1==3 && flagBD==0){output_toggle(pin_b7);//write_eeprom(251,3);
      if(m<=12 || m==255){flag=1; m=12;
      comand[0]=S;comand[2]=an;comand[4]=S;comand[6]=69;comand[7]=83;comand[9]=78;comand[11]=83;
                         }
                                              }

      delay_ms(1000);n=0;}


delay_us(30);
++i; //if(i>255) {i=0;}
if(i>=comand[1]){output_low(pinored);} else {output_high(pinored);}
if(i>=comand[2]){output_low(pinoblue);} else {output_high(pinoblue);}
if(i>=comand[3]){output_low(pinogreen);} else {output_high(pinogreen);}

   }}
