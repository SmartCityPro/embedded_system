/*
 * Drivers_final.c
 *
 * Created: 12/2/2019 7:40:28 PM
 * Author : fathy
 */ 



#include "adc.h"
#include "utils.h"
#include "lcd.h"
#include "i2c.h"
#include "interrupt.h"
#include "dht11.h"



#define degree_sysmbol 0xdf
void calcTemp(uint16_t *pe);
uint8_t calcRain(uint16_t *pe);
uint8_t calcWater(uint16_t *pe);
uint8_t cnt = 0;

ISR(INT0_vect)
{
	if (cnt>2)
	{
		cnt = 0;
	}else if (cnt<0){
		cnt = 2;
	}else{
		cnt++;
	}
}

int main(void)
{
	uint8_t I_RH,D_RH,I_Temp,D_Temp,CheckSum;
	char Temperature[5];
	uint16_t tempVal = 0.0;
	char Rain[5];
	uint16_t rainVal = 0.0;
	char Water[5];
	uint16_t waterVal = 0.0;
	//char totalString[15];
	
	PORTD |= (1<<2);                   // Pull Up  switch for interrupt
	
	interrupt_init(INT_NUM_0,RAISING_EDGE_TYPE);
	lcd_init();
	adc_init(AVREF,FREE_RUNNING_MODE,CLK_ADC_DIV_128);
   
	sei();			   // Enable Global Interrupt 
	while(1){
	
	  calcTemp(&tempVal);
	  sprintf(Temperature,"%d  ",(int)tempVal);
	  calcRain(&rainVal);  
	  sprintf(Rain,"%d  ",(int)rainVal);
	  calcWater(&waterVal);
	  sprintf(Water,"%d  ",(int)waterVal);
	  dht11_process(&I_RH,&D_RH,&I_Temp,&D_Temp,&CheckSum);
	  //sprintf(totalString,"%d  %d  %d ",(int)tempVal,(int)rainVal,(int)waterVal);
	  //LCD_String_xy(1,0,totalString); 
	  
	  
	  switch(cnt){
		  case 0:
		  LCD_String_xy(0,0,"Temp          ");
		  LCD_String_xy(1,0,Temperature);
		  break;
		  case 1:
		  LCD_String_xy(0,0,"Rain           ");
		  LCD_String_xy(1,0,Rain);
		  break;
		  case 2:
		  LCD_String_xy(0,0,"Water         ");
		  LCD_String_xy(1,0,Water);
		  break;
	  }
	}
	return 0;
}

void calcTemp(uint16_t *pe){ 
	*pe = adc_read(CHANNEL0);
	*pe = (*pe*4.88)/10.0;
	
}

uint8_t calcRain(uint16_t *pe){
		*pe = adc_read(CHANNEL1);
		if (*pe<300)
		{
			return 2;
		}else if(*pe<500){
			return 1;
		}else{
			return 0;
		}
}

uint8_t calcWater(uint16_t *pe){
	*pe = adc_read(CHANNEL2);
	 if (*pe<300)
	 {
		 return 2;
		 }else if(*pe<500){
		 return 1;
		 }else{
		 return 0;
	 }
}









/*
double count = 0;
uint16_t pulse = 0;
ISR(INT0_vect){
	if(count==0){
		count = 1 ;
	}
}

int main (){
	char string[15];
	DDRD |= (1<<7); 
	lcd_init();
	LCD_String_xy(0,0,"ultrasonic");
	interrupt_init(INT_NUM_0,ANY_CHANGE_TYPE);
	sei();
	TCCR1A = 0;
	while(1){
		_delay_ms(1500);
		PORTD |= (1 << 7);
		_delay_us(10);
		PORTD &= (~(1 << 7));
        
		
	 while(count==0);
	   TCCR1B |= 1<<CS10;
	   count = 0;
	 while(count==0);
	    TCCR1B = 0;
	    pulse = TCNT1;
	    TCNT1 = 0;
	    count = 0;
		
		
	sprintf(string,"%d  ",TCNT1);
	LCD_String_xy(1,0,string);  
		
	_delay_ms(1000);		
	}
	return 0;
}
*/


// utra sonic
/*
static volatile int pulse = 0;    
static volatile int i = 0;       
 int16_t count_a = 0;
 char show_a[16];

#define trigger_pin PD0

int x = 0;

int main(){
	sbi(DDRD,trigger_pin);
	lcd_init();
	interrupt_init(INT_NUM_0,ANY_CHANGE_TYPE);
	sei();
	LCD_String_xy(0,0,"AHMED");
	while(1){
	itoa(count_a,show_a,10);
	LCD_String_xy(1,0,show_a);	   
		                     
	}
	return 0;
}

ISR(INT0_vect)
{
	if(i == 1)
	{
		pulse = TCNT1;
		TCCR1B = 0;
		x = 100;
		TCNT1 = 0;
		i = 0;
	}

	if(i==0)
	{
		sbi(TCCR1B,CS10);
		i = 1;
	}
}*/

/*
int TimerOverflow = 0;
double distance;
#define Trigger_pin PD0
#define Echo_pin    PD6
ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	// Increment Timer Overflow count 
}
int main(){
	char string[10];
	long count;
	
	
	DDRD  |= (1<<Trigger_pin);                 // D0 AS OUTPUT TRIGGER
	PORTD |= (1<<Echo_pin);                   // D6 AS INPUT - PULLUP - ECHO
	
	sei();			            // Enable global interrupt 
	TIMSK = (1 << TOIE1);	    // Enable Timer1 overflow interrupts 
	TCCR1A = 0;		            // Set all bit to zero Normal operation
	 
	lcd_init();
	LCD_String_xy(0,0,"Ultra Sonic");
	
	while(1){
		// Give 10us trigger pulse on trig. pin to HC-SR04 
		PORTA |= (1 << Trigger_pin);
		_delay_us(10);
		PORTA &= (~(1 << Trigger_pin));
		
		TCNT1 = 0;	                              // Clear Timer counter 
		TCCR1B |= 0x41;	      // Capture on rising edge, No prescaler
		TIFR = 1<<ICF1;	                         // Clear ICP flag (Input Capture flag) 
		TIFR = 1<<TOV1;	                         // Clear Timer Overflow flag 
		
		//Calculate width of Echo by Input Capture (ICP) 
		
		while ((TIFR & (1 << ICF1)) == 0);          // Wait for rising edge 
		TCNT1 = 0;	                               // Clear Timer counter 
		TCCR1B |= 0x01;                       // Capture on falling edge, No prescaler 
		TIFR = 1<<ICF1;	                           // Clear ICP flag (Input Capture flag) 
		TIFR = 1<<TOV1;	                           // Clear Timer Overflow flag 
		TimerOverflow = 0;                         // Clear Timer overflow count 

		while ((TIFR & (1 << ICF1)) == 0);          // Wait for falling edge 
		
		count = ICR1 + (65535 * TimerOverflow);	    // Take count 
		
		
		// 8MHz Timer freq, sound speed =343 m/s 
		distance = (double)count / 466.47;
		
		dtostrf(distance, 2, 2, string); // distance to string 
		strcat(string, " cm   ");	    // Concat unit i.e.cm 
		LCD_String_xy(1, 0, "Dist = ");
		LCD_String_xy(1, 7, string);	// Print distance 
		_delay_ms(200);
		
		// d = v  * t
		//distance = ((TimerOverflow*(1/F_CPU))*SOUND_VELOCITY)/2;
		
	}
	return 0;
}
*/

/*
#define Slave_Write_Address		0x20    //w(0)
#define Slave_Read_Address		0x21    //w(1)
#define	count				    10
int main(){
	char buffer[10];
	lcd_init();
	i2c_init();
	LCD_String_xy(0,0,"Master Device..");
	while (1)
	{
		LCD_String_xy(1, 0, "Sending :       ");
		I2C_Start_Wait(Slave_Write_Address);       // Start I2C with SLA+W 
	}
	return 0;
}
*/


