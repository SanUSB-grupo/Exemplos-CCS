#include "SanUSBi2c.h" // Firmware para configuração e leitura por SOFTWARE de EEPROM i2c e do relógio DS1307 (BCD)
#include "i2c_sanusb.h"//Biblioteca de funcoes I2C com a placa SanUSB. RB0(SDA) e RB1(SCL)
//Apostila disponível em https://dl.dropboxusercontent.com/u/101922388/ApostilaSanUSB/Apostila_SanUSB_CCS.pdf

unsigned int32 resultado, tensao_lida16;
unsigned int16 i,j,endereco16=0, posicao=0, valorgravado;
unsigned char byte1,byte2; // 2 Partes do valor da tensao_lida16

unsigned int16 conv_dec_2bytes(unsigned int16 valor16) 
{//Função auxiliar para alocar um valor de 16 bits (até 65535) em 2 bytes
    //unsigned int resultado=0;
    byte1= valor16%256; byte2 = valor16/256; //o que for resto (%) é menos significativo
    return(byte2,byte1);
}

#INT_RDA
void recepcao_serial(){}

void main(){
    clock_int_4MHz();
    taxa_serial(19200);
    enable_interrupts(GLOBAL);
    enable_interrupts(INT_RDA);
    setup_adc_ports(AN0);  //Habilita entradas analógicas - A0
    setup_adc(ADC_CLOCK_INTERNAL);
    set_adc_channel(0);

    while(true){
              resultado = read_adc();
        tensao_lida16 = (resultado * 5000)/1023; //Valor até 16 bits (2 bytes)
        sendnum(tensao_lida16); swputc(' ');

        //***************************************************************************
        conv_dec_2bytes(tensao_lida16);
        posicao=2*endereco16; //endereço é o ponteiro de 16 bits (byte 1 e byte 2)
        escreve_eeprom(0, posicao, byte2); //Byte mais significativo do int16
        escreve_eeprom(0, posicao+1, byte1 ); //byte menos significativo do int16
        ++endereco16; if (endereco16>=150){endereco16=0;} //Buffer de 300 bytes posicao<300
        //***************************************************************************
        
        if(input(pin_e3)==0){ //Clique no botão para ler o buffer gravado
            send_hex(le_eeprom(0,1000)); sendsw("\n\r");//teste leitura eeprom i2c

         //***************LEITURA DO BUFFER DA EEPROM EXTERNA I2C********************
                for(i=0; i<10; ++i) { //150 Valores de 16 bits ou 300 de 8 bits.
                    for(j=0; j<15; ++j) {
                        valorgravado= 256*le_eeprom(0,(i*30)+2*j) + le_eeprom(0,(i*30)+2*j+1);
                        sendnum(valorgravado); swputc(' ');
                                        }
                        sendsw("\n\r");
                                    }
                        sendsw("\n\r");
                             }
        //***************************************************************************
    
        escreve_eeprom(0,1000, le_rtc(seg)); //Escreve na posicao 1000 para depurar a leitura da eeprom
        
        output_toggle(pin_b7);
        delay_ms(1000);
             }
}

