//O firmware abaixo executa uma multi-tarefa (multi-tasking) onde 3 LEDs comutam
//independentes e simultaneamente

#include <SanUSB.h>

// Define qual o timer utilizado e o maior tempo de cada tarefa (minor_cycle) do RTOS
#use rtos(timer=0, minor_cycle=10ms)

// Declara TAREFA 1 - chamada a cada 250ms
#task(rate=250ms, max=10ms)
void task_B7()
{output_toggle(PIN_B7); }// comuta RB7

// Declara TAREFA 2 - chamada a cada 500ms
#task(rate=500ms, max=10ms)
void task_B6()
{output_toggle(PIN_B6);} // comuta  RB6


// Declara TAREFA 3 - chamada a cada segundo
#task(rate=1s, max=10ms)
void task_B0()
{
output_toggle(PIN_B0); // comuta  RB0
}


void main()
{
clock_int_4MHz();
set_tris_b(0); // Configura PORTB como saída

setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1); //ciclo de máquina de 1us
rtos_run(); // inicia o RTOS (sistema operacional em tempo real

}


