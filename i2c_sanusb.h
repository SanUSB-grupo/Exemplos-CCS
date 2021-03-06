/**********http://br.groups.yahoo.com/group/GrupoSanUSB/*************************/
// Defini��es dos pinos de comunica��o I2C SanUSB
   #ifndef scl
   #define scl  pin_b1             // pino de clock
   #define sda  pin_b0              // pino de dados

   #define EEPROM_SIZE 32768       // tamanho em bytes da mem�ria EEPROM
   #endif

   #define seta_scl   output_float(scl)      // seta o pino scl
   #define apaga_scl  output_low(scl)      // apaga o pino scl
   #define seta_sda   output_float(sda)      // seta o pino sda
   #define apaga_sda  output_low(sda)      // apaga o pino sda

// RAM do RTC DS1307
#define seg  0x00
#define min  0x01
#define hora 0x02
#define dia  0x04
#define mes  0x05
#define ano  0x06
/******************************************************************************/
//SUB-ROTINAS DA COMUNICA��O I2C

   void I2C_start(void)
   // coloca o barramento na condi��o de start
   {
      apaga_scl;     // coloca a linha de clock em n�vel 0
      delay_us(5);
      seta_sda;   // coloca a linha de dados em alta imped�ncia (1)
      delay_us(5);
      seta_scl;   // coloca a linha de clock em alta imped�ncia (1)
      delay_us(5);
      apaga_sda;   // coloca a linha de dados em n�vel 0
      delay_us(5);
      apaga_scl;   // coloca a linha de clock em n�vel 0
      delay_us(5);
   }

   void I2C_stop(void)
   // coloca o barramento na condi��o de stop
   {
      apaga_scl;   // coloca a linha de clock em n�vel 0
      delay_us(5);
      apaga_sda;   // coloca a linha de dados em n�vel 0
      delay_us(5);
      seta_scl;   // coloca a linha de clock em alta imped�ncia (1)
      delay_us(5);
      seta_sda;   // coloca a linha de dados em alta imped�ncia (1)
      delay_us(5);
   }

   void i2c_ack()
   // coloca sinal de reconhecimento (ack) no barramento
   {
      apaga_sda;   // coloca a linha de dados em n�vel 0
      delay_us(5);
      seta_scl;   // coloca a linha de clock em alta imped�ncia (1)
      delay_us(5);
      apaga_scl;   // coloca a linha de clock em n�vel 0
      delay_us(5);
      seta_sda;   // coloca a linha de dados em alta imped�ncia (1)
      delay_us(5);
   }

   void i2c_nack()
   // coloca sinal de n�o reconhecimento (nack) no barramento
   {
      seta_sda;   // coloca a linha de dados em alta imped�ncia (1)
      delay_us(5);
      seta_scl;   // coloca a linha de clock em alta imped�ncia (1)
      delay_us(5);
      apaga_scl;   // coloca a linha de clock em n�vel 0
      delay_us(5);
   }

   boolean i2c_le_ack()
   // efetua a leitura do sinal de ack/nack
   {
      boolean estado;
      seta_sda;    // coloca a linha de dados em alta imped�ncia (1)
      delay_us(5);
      seta_scl;   // coloca a linha de clock em alta imped�ncia (1)
      delay_us(5);
      estado = input(sda);   // l� o bit (ack/nack)
      apaga_scl;   // coloca a linha de clock em n�vel 0
      delay_us(5);
      return estado;
   }

   void I2C_escreve_byte(unsigned char dado)
   {
   // envia um byte pelo barramento I2C
      int conta=8;
      apaga_scl;      // coloca SCL em 0
      while (conta)
      {
         // envia primeiro o MSB
         if (shift_left(&dado,1,0)) seta_sda; else apaga_sda;
         // d� um pulso em scl
         seta_scl;
         delay_us(5);
         conta--;
         apaga_scl;
         delay_us(5);
      }
      // ativa sda
      seta_sda;
   }

   unsigned char I2C_le_byte()
   // recebe um byte pelo barramento I2C
   {
      unsigned char bytelido, conta = 8;
      bytelido = 0;
      apaga_scl;
      delay_us(5);
      seta_sda;
      delay_us(5);
      while (conta)
      {
         // ativa scl
         seta_scl;
         // l� o bit em sda, deslocando em bytelido
         shift_left(&bytelido,1,input(sda));
         conta--;
         // desativa scl
         apaga_scl;
      }
      return bytelido;
   }

   void escreve_eeprom(byte dispositivo, long endereco, byte dado)
   // Escreve um dado em um endere�o do dispositivo
   // dispositivo - � o endere�o do dispositivo escravo (0 - 7)
   // endereco - � o endere�o da mem�ria a ser escrito
   // dado - � a informa��o a ser armazenada
   {
      if (dispositivo>7) dispositivo = 7;
      i2c_start();
      i2c_escreve_byte(0xa0 | (dispositivo << 1)); // endere�a o dispositivo
      i2c_le_ack();
      i2c_escreve_byte(endereco >> 8);   // parte alta do endere�o
      i2c_le_ack();
      i2c_escreve_byte(endereco);   // parte baixa do endere�o
      i2c_le_ack();
      i2c_escreve_byte(dado);         // dado a ser escrito
      i2c_le_ack();
      i2c_stop();
      while(read_eeprom(0xfd));
      delay_ms(10); // aguarda a programa��o da mem�ria
   }

   byte le_eeprom(byte dispositivo, long int endereco)
   // L� um dado de um endere�o especificado no dispositivo
   // dispositivo - � o endere�o do dispositivo escravo (0 - 7)
   // endereco - � o endere�o da mem�ria a ser escrito
   {
      byte dado;
      if (dispositivo>7) dispositivo = 7;
      i2c_start();
      i2c_escreve_byte(0xa0 | (dispositivo << 1)); // endere�a o dispositivo
      i2c_le_ack();
      i2c_escreve_byte((endereco >> 8));   // envia a parte alta do endere�o
      i2c_le_ack();
      i2c_escreve_byte(endereco);   // envia a parte baixa do endere�o
      i2c_le_ack();
      i2c_start();
      // envia comando de leitura
      i2c_escreve_byte(0xa1 | (dispositivo << 1));
      i2c_le_ack();
      dado = i2c_le_byte();   // l� o dado
      i2c_nack();
      i2c_stop();
      return dado;
   }
/******************************************************************************/
//******************************************************************************/
void escreve_rtc(byte enderecoram, byte dado)
// Escreve um dado em um endere�o do dispositivo
// endereco - � o endere�o da mem�ria a ser escrito
// dado - � a informa��o a ser armazenada
{
   i2c_start();
   i2c_escreve_byte(0xd0);
   i2c_le_ack();
   i2c_escreve_byte(enderecoram);   // parte baixa do endere�o de 16 bits
   i2c_le_ack();
   i2c_escreve_byte(dado);         // dado a ser escrito
   i2c_le_ack();
   i2c_stop();
   while(read_eeprom(0xfd));
   delay_ms(10); // aguarda a programa��o da mem�ria
}
byte le_rtc(int enderecoram)
// L� um dado de um endere�o especificado no dispositivo
// dispositivo - � o endere�o do dispositivo escravo (0 - 7)
// endereco - � o endere�o da mem�ria a ser escrito
{
   byte dado;
   i2c_start();
   i2c_escreve_byte(0xd0); // endere�a o dispositivo e colocando leitura 0xd1
   i2c_le_ack();
   i2c_escreve_byte(enderecoram);   // envia a parte baixa do endere�o
   i2c_le_ack();
   i2c_start();
   // envia comando de leitura
   i2c_escreve_byte(0xd1); // Coloca o LSB (R\W) em estado de leitura
   i2c_le_ack();
   dado = i2c_le_byte();   // l� o dado
   i2c_nack();
   i2c_stop();
   return dado;
}

void send_hex(unsigned char number)
{
    unsigned char hexChar;
    char i;
    for(i = 0; i < 2; i++)
    {
        if(i == 0)
            hexChar = number >> 4;
        else
            hexChar = number & 0x0F;
        if(hexChar < 10)
            hexChar = hexChar + '0';
        else
            hexChar = hexChar + ('A' - 10);
        swputc(hexChar);
    }
}

/************************************************************************************************
* Convers�o BCD P/ DECIMAL
************************************************************************************************/
unsigned char bcd_para_dec(unsigned char valorb)
{
unsigned char temp;
temp = (valorb & 0b00001111);
temp = (REG+temp) + ((valorb >> 4) * 10);
return(temp);
}
/*************************************************************************************************
* Convers�o DECIMAL p/ BCD
************************************************************************************************/
unsigned char dec_para_bcd(unsigned char valord)
{
return((0x10*(valord/10))+(valord%10)+REG);
}

