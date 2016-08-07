/***************************************************************************
Firmware and Front-end: https://dl.dropboxusercontent.com/u/101922388/WiflySanUSB.zip
APK: https://play.google.com/store/apps/details?id=appinventor.ai_sandro_juca.Wifi_SanUSB
Video http://www.youtube.com/watch?v=gUe24X1gNVw 

After uploading or reset, wait until only the green led on the Wifly modem is blinking and click connect on the front-end.
Ap�s o upload ou reset, aguarde ate que somente o led verde do modem Wifly esteja piscando e clique em conectar no front-end

Se for a primeira grava��o do PIC com modem conectado, talvez seja necess�rio resetar o microcontrolador ap�s a grava��o, retirando e colocando o cabo USB novamente.
//Ao digitar 192.168.1.195/YT na barra de endere�o de qualquer navegador (browser), o sinal do LED ser� comutado (toggle) e aparecer� uma p�gina HTML.
 
 The microcontroller can be, with this firmware, server (switching the led signal through 192.168.1.195/YT in adress bar) or also client (the AD converter value is inserted in google databank).

 **********************************************************************************/
#include "SanUSBfly.h"

  const unsigned char pg[] = {144,168,168,160,94,98,92,98,64,100,96,96,64,158,150,26,20,134,222,220,232,202,220,232,90,168,242,224,202,116,64,232,202,240,
  232,94,208,232,218,216,26,20,26,20,120,198,202,220,232,202,228,124,120,210,204,228,194,218,202,64,230,228,198,122,68,208,232,232,224,230,116,94,94,
  200,222,198,230,92,206,222,222,206,216,202,92,198,222,218,94,230,224,228,202,194,200,230,208,202,202,232,94,204,222,228,218,164,202,230,224,222,220,230,
  202,126,204,222,228,218,214,202,242,122,200,136,180,238,172,216,164,104,164,142,106,230,168,174,106,156,202,216,222,100,164,216,156,160,172,138,162,100,
  178,218,198,108,154,162,76,210,204,226,74,100,96,76,202,220,232,228,242,92,96,92,230,210,220,206,216,202,122,0};

  const unsigned char pg1[] = {76,202,220,232,228,242,92,98,92,230,210,220,206,216,202,122,0};

  const unsigned char pg2[] = {76,230,234,196,218,210,232,122,166,234,196,218,210,232,68,124,120,94,210,204,228,194,218,202,124,120,144,98,124,148,222,
  210,220,64,232,210,220,242,234,228,216,92,198,222,218,94,166,194,220,170,166,132,120,94,144,98,124,120,160,124,120,94,144,98,124,130,198,198,202,230,
  230,64,120,194,64,208,228,202,204,122,68,208,232,232,224,230,116,94,94,200,222,198,230,92,206,222,222,206,216,202,92,198,222,218,94,230,224,228,202,
  194,200,230,208,202,202,232,94,198,198,198,126,214,202,242,122,96,130,224,102,102,100,158,130,208,220,154,202,100,200,136,180,238,172,216,164,104,164,
  142,106,230,168,174,106,156,202,216,222,100,164,216,156,160,172,138,162,100,178,218,198,68,124,152,222,206,230,120,94,194,124,120,94,160,124,120,94,
  198,202,220,232,202,228,124,26,20,0};
  
//Basta compilar o arquivo SaUSBwifly.c inserindo o nome da rede (SSID) e a senha abaixo e gravar no PIC o SaUSBwifly.hex com o modem conectado ao PIC.

char rede[] = "SanUSB";      // Your WiFi SSID name 
char senha[] = "Laese";   // Your WiFi password
char ip[] = "192.168.1.195"; // Set intranet static IP (DHCP OFF). In this the case the static IP .195 is based on the gateway IP 192.168.1.1.
                             // To check the IP of your gateway, type ipconfig or ifconfig at the prompt or terminal on the computer 
                             // Default Wifly RN-XV SanUSB IP: 192.168.1.195 Port: 80. The Wifly IP must be xxx.xxx.x.1xx , with "1" in last byte for the gateway IP.

short int AT1=0,  AT2=0, flagsw=0;
char  comando[64], n=0, m=0;
unsigned int16 ADvalue = 0, i=0; 
unsigned char smid;


#INT_RDA
void recepcao_serial()
{
comando[n]=RCREG; m=n;

      switch (comando[n]){

             case 'C':
             AT1=1;
             break;

             case 'I':
             AT2=1;
             break;

             case 'A':
             AT1=1;
             break;

             case 'S':
             AT1=1;
             break;

             case '*':
             AT1=1;
             break;
           case 'Y':
             {n=0;comando[0] = 'Y';}
              break;
         }
 //***************possibility 1->character***********************
                            if (comando[0]== 'Y' && n==1){comando[0]== 32;
                                      switch(RCREG)
                                                  {
                                                case 'L':  output_high(pin_b7); //type in browser address bar: 192.168.1.195/YL
                                                           flagsw=1;
                                                break;

                                                case 'D': output_low(pin_b7); //type in browser address bar: 192.168.1.195/YD
                                                break;

                                                case 'P':  output_high(pin_b7); //type in browser address bar: 192.168.1.195/YP
                                                break;

                                                case 'T': output_toggle(pin_b7); //type in browser address bar: 192.168.1.195/YT to toggle Led and open a HTML page
                                                          flagsw=1;
                                                break;
                                                
                                                case 'Y': {n=0;comando[0] = 'Y';}
                                                break;

                                                 }
                                                         }
//***************possibility 2-> word**************************
                            if ( comando[1]== 'O' && comando[2]== 'N')
                                                {
                                                 output_high(pin_b7);  // ON
                                                }

                            if ( comando[1]== 'O' && comando[2]== 'F' && comando[3]== 'F')
                                                {

                                                 output_low(pin_b7); // OFF
                                                }

         ++n; if(n>=64){n=0;}
   }
   
#include "confws.h"


void main()
{
  taxa_serial(9600);
  enable_interrupts(GLOBAL);
  enable_interrupts(INT_RDA);
  #priority rda 
  setup_adc_ports(AN0_to_AN1);  //Habilita entradas anal�gicas - A0
  setup_adc(ADC_CLOCK_INTERNAL);
  set_adc_channel(0);
  iniws();
 // setup_wdt(wdt_on);

   while(true)
   {
           if (flagsw==1) {flagsw=0;
                           ADvalue=read_adc();
                           delay_ms(500);
                           sends(pg);
                           for(i=0;rede[i]!='\0';i++)
                           {smid=(rede[i]*(('@'+REG)>>5));sputc(smid);}
                           sends(pg1);
                           sendnum(ADvalue);
                           sends(pg2);
                           delay_ms(500);
                          }
                           // restart_wdt(); 
   }}
   
