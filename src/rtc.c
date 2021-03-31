#include "MKL05Z4.h"
#include	"rtc.h"



void RTC_Init(void)
{
	// enable the clock to SRTC module register space
    SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
    SIM->SOPT1 = (SIM->SOPT1 & ~SIM_SOPT1_OSC32KSEL_MASK) | SIM_SOPT1_OSC32KSEL(0);

    // Reset
    RTC->CR = RTC_CR_SWR_MASK;
    RTC->CR &= ~RTC_CR_SWR_MASK;

    // Allow write
    RTC->CR = RTC_CR_UM_MASK | RTC_CR_SUP_MASK;

    NVIC_EnableIRQ(RTC_Seconds_IRQn);
  
    if (RTC->SR & RTC_SR_TIF_MASK){
        RTC->TSR = 0;
    }
    RTC->TCR = 0;
		
		
		//clock stablziation
    RTC->CR |= RTC_CR_OSCE_MASK;
    for (volatile int i=0; i<0x600000; i++);

    //enable seconds interrupts
    RTC->IER |= RTC_IER_TSIE_MASK;

    // enable time counter
    RTC->SR |= RTC_SR_TCE_MASK;

}
