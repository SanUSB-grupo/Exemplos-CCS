#include <SanUSB.h> // Emula��o de circuitos l�gicos booleanos (OU-Exclusivo)
short int A, B, saida, ledpisca;

main(){
clock_int_4MHz();

while (TRUE)
{
A=input(pin_b1); //entrada com pull-down externo (resistor conectado ao Terra)
B=input(pin_b2); //entrada com pull-down externo (resistor conectado ao Terra)

saida = A^B; //saida � igual ao resultado do OU-Exclusivo obtida pelas entradas dos pinos A e B 
output_bit(pin_b7,saida); //O pino_b7 mostra o resultado do circuito l�gico booleano alocado em saida

ledpisca=!ledpisca; // ledpisca � igual ao inverso de ledpisca
output_bit(pin_b0,ledpisca); // b0 recebe o valor de ledpisca
delay_ms(500);
}
}
