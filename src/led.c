#include "led.h"
#define RED_LED 8

void Led_Init(void) {  
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 
	PORTB->PCR[RED_LED] |= PORT_PCR_MUX(1);
	PTB->PDDR |= (1<<RED_LED); 
	PTB->PSOR |= (1<<RED_LED);
}

void Led_On(void){
	PTB->PCOR|= (1<<RED_LED);
}

void Led_Off(void){
	PTB->PSOR |= (1<<RED_LED);	
}