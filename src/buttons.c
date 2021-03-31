#include "lcd1602.h"

void buttons_init(void){
	
	SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
	
	// PTA9 - PTA12: GPIO
	for(int i=9;i<13;i++){	
	PORTA->PCR[i] |= PORT_PCR_MUX(1);			// PTA5 - PTA12: GPIO
	PORTA->PCR[i] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;	
	}
	//PTA5 - PTA8: wyjscia
	
	for (int i=5;i<9;i++){
	PORTA->PCR[i] |= PORT_PCR_MUX(1);
	PTA->PDDR |= (1<<i); 
	PTA->PSOR|=(1<<i);
	}
	
	
}
uint8_t get_key(){
    int row = 0;
    int col = 0;
		PTA->PDDR|= 0x000001E0;
		PTA->PSOR|= 0x000001E0;
    for (int i = 0; i < 4; i++)
    {
        row++;
        PTA->PCOR |= (1 << (5 + i));
        if ((PTA->PDIR & (1 << 9)) == 0)
        {
           col = 1;
					break;
					
        }
				else if ((PTA->PDIR & (1 << 10)) == 0)
        {
            col = 2;
					break;
					
        }
        else if ((PTA->PDIR & (1 << 11)) == 0)
        { 
            col = 3;
					break;
						
				}
        else if ((PTA->PDIR & (1 << 12)) == 0)
        {
            col = 4;
					break;
        }
        PTA->PDDR|= (0<< (5 + i));        
    }
		if(col==0) return 0;
    return (row - 1) * 4 + col;
}
