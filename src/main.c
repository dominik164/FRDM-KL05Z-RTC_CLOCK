#include "MKL05Z4.h"
#include "rtc.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include "buttons.h"
#include "led.h"
#include "tsi.h"


uint8_t seconds=0;
uint8_t minutes=0;
uint8_t hours=0;
uint8_t alarm_seconds=0;
uint8_t alarm_minutes=0;
uint8_t alarm_hours=0;
uint8_t alarm_set=0;

void digitalClock()
{
	seconds ++;
	if(seconds == 60)
	{
		seconds = 0;
		minutes++;	
	}
	
	if(minutes == 60)
	{
		minutes = 0;
		hours++;
		
	}
	
	if(hours == 24)
	{
		hours = 0;
	}
	
	
}

void print_clock(uint8_t value ,char* tab){
		tab[0] = (value / 10)%10 + '0';
    tab[1] = value %10 + '0';
		tab[2]=0;
		LCD1602_Print(tab);
   
}


void check_alarm(){
	if (seconds==alarm_seconds && minutes==alarm_minutes && hours==alarm_hours){
		Led_On();
	}
}

void set_alarm(uint8_t a){
	if(a==1){
		hours++;
		if(hours==24){
			hours=0;
		}
	}
	else if(a==2){
		if(hours==0){
			hours=24;
		}
		hours--;
	}
	else if(a==3){
		minutes++;
		if(minutes==60){
		minutes=0;
		}
	}
	else if(a==4){
		minutes--;
	}
	if(a==5){
		alarm_hours++;
		alarm_set=1;
		if(alarm_hours==24){
			alarm_hours=0;
		}
	}
	else if(a==6){
		if(alarm_hours==0){
			alarm_hours=24;
		}
		alarm_hours--;
	}
	else if(a==7){
		alarm_minutes++;
		alarm_set=1;
		if(alarm_minutes==60){
		alarm_minutes=0;
		}
	}
	else if(a==8){
		alarm_minutes--;
	}
	
}

void turn_alarm_off(void){
	
	if(TSI_ReadSlider()>0){
		alarm_set=0;
		Led_Off();
	}
}


void RTC_Seconds_IRQHandler()
{	
	digitalClock();
}

int main (void)
{
	TSI_Init();
	RTC_Init();
	buttons_init();
	Led_Init();
	char show_sec[3] ; 
	char show_min[3] ;  
	char show_hou[3] ;
	char alarm_sec[3] ; 
	char alarm_min[3] ;
	char alarm_hou[3] ;
	LCD1602_Init();		 // Inicjalizacja wyświetlacza LCD
	LCD1602_Backlight(TRUE);
	LCD1602_SetCursor(0,0);
	LCD1602_Print("ZEGAR:");
	LCD1602_SetCursor(0,1);
	LCD1602_Print("BUDZIK:");
	uint8_t key_value;
	
	
	while(1){
	key_value=get_key();
	set_alarm(key_value);
	LCD1602_SetCursor(8,0);
	print_clock(hours,show_hou);
	LCD1602_Print(":");
	print_clock(minutes,show_min);
	LCD1602_Print(":");
	print_clock(seconds,show_sec);
	if (alarm_set==0){
		LCD1602_SetCursor(8,1);
		LCD1602_Print("OFF     ");
	}
	else{
	check_alarm();
	turn_alarm_off();
	LCD1602_SetCursor(8,1);
	print_clock(alarm_hours,alarm_hou);
	LCD1602_Print(":");
	print_clock(alarm_minutes,alarm_min);
	LCD1602_Print(":");
	print_clock(alarm_seconds,alarm_sec);
	}
	
}
	
}


  