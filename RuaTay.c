//Dev: le Van Thien
#include <msp430g2553.h>
#include "lcd.c"

volatile unsigned int  time_flow =1;
volatile unsigned int  wash_time = 0;
volatile unsigned int  cur_person = 0;

int max_person =5;
int max_time_flow =3;
int max_water=10;

char str[16]; //temp 

void display(int wash_time,int time_flow,int  cur_person)
{
  lcdClear();
  sprintf(str, "Water:%d%% /%d" ,100-wash_time*100/max_water,time_flow);
  lcdPrint(str, 0,1);
  sprintf(str, "Person: %d", cur_person);
  lcdPrint(str, 0,0);
}

void delay_(int time)
{
  switch(time){
  case 1:
    __delay_cycles(1000000);
    break;
  case 2:
    __delay_cycles(2000000);
    break;
  case 3:
    __delay_cycles(3000000);
    break; 
  }
}

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer
  
  /* p1.0 output bump */ 
  P1DIR = BIT0;     // P1.0 : output
  P1OUT &= ~BIT0;   // P1.0 : off
  
  /* P1.6 Output for button p1.2 p1.3: Blink */
  P1DIR |= BIT6;
  P1OUT &=~BIT6;  
  
  /*P1.7 INPUT  FOR RESET WASH_TIME=0 (OUT OF WATER) */
  P1DIR &= ~BIT7; 	 // p1.1 : input
  P1REN |=BIT7;   	 // Pullup/pulldown resistor enabled
  P1OUT &= ~BIT7; 	 // enable internal pull down
  P1IE  |=BIT7;  	  // enable interrupt p1.1
  P1IES &=~BIT7;  	 //(low-to-high)  
  
  /* P1.1 : proximity sensor */
  P1DIR &= ~BIT1; 	 // p1.1 : input
  P1REN |=BIT1;   	 // Pullup/pulldown resistor enabled
  P1OUT &= ~BIT1; 	 // enable internal pull down
  P1IE  |=BIT1;  	  // enable interrupt p1.1
  P1IES &=~BIT1;  	 //(low-to-high)
  
  /* P1.2 button up */
  P1DIR &= ~BIT2;        //P1.2 : input  
  P1REN |= BIT2;         //Pullup/pulldown resistor enabled
  P1OUT |= BIT2;         //enable internal pull up
  P1IE  |= BIT2;         //enable interrupt P1.3   
  P1IES |= BIT2;  	 //(high-to-low)
  
  /* P1.3 button down */
  P1DIR &= ~BIT3;         
  P1REN |= BIT3;         
  P1OUT |= BIT3;         
  P1IE  |= BIT3;             
  P1IES |= BIT3;         
  
  /* P1.4 : Sensor door 1 */
  P1DIR &= ~BIT4; 	
  P1REN |=BIT4;   	 
  P1OUT |= BIT4; 	 
  P1IE  |=BIT4;  	  
  P1IES |=BIT4;  	 
  
  /* P1.5 Sensor door 2 */
  P1DIR &= ~BIT5;         
  P1REN |= BIT5;         
  P1OUT |= BIT5;         
  P1IE  |= BIT5;             
  P1IES |= BIT5; 
  
  /* LCD INIT */
  lcdInit();
  lcdPrint("Hello ", 0, 0);
  delay_ms(1000);
  
  display(wash_time,time_flow,cur_person);
  
  _BIS_SR(LPM4_bits + GIE);         // Enter LPM4 & enable global interrupt	
  
}
#pragma vector=PORT1_VECTOR         // interrupt vector declaration
__interrupt void Port_1(void)       // interrupt program
{
  
  if (P1IFG & BIT1 )
  {// hand wash sensor
    __delay_cycles(50000);
    if (P1IN & BIT1) {}
    else
    {
      P1OUT |= BIT0;
      delay_(time_flow);  
      P1OUT &= ~BIT0;
      P1IFG &= ~BIT1;   // clear interrupt flag
      
      wash_time = wash_time + time_flow;
      if(wash_time>= max_water)   // water out warning 
      {
        wash_time=max_water;
        for ( int i =0;i<=5;i++) 
        {
          P1OUT |= BIT6;
          __delay_cycles(200000);
          P1OUT &= ~BIT6;
          __delay_cycles(200000);
          
        }
        
      }
      display(wash_time,time_flow,cur_person); 
      
    }
  }
  else if (P1IFG &BIT2 ) //reduce spray time
  {	
    
    P1IFG &= ~BIT2;  
    
    P1OUT |= BIT6;
    __delay_cycles(100000);
    P1OUT &= ~BIT6;
    
    time_flow --;
    if (time_flow < 1) time_flow =1;
    display(wash_time,time_flow,cur_person);
    
  }
  else if (P1IFG &BIT3 )// increase spray time
  {
    
    P1IFG &= ~BIT3;   
    P1OUT |= BIT6;
    __delay_cycles(100000);
    P1OUT &= ~BIT6;
    
    time_flow ++;
    if (time_flow > max_time_flow) time_flow =max_time_flow;
    display(wash_time,time_flow,cur_person);
    
  }
  else if (P1IFG & BIT4 ) // detect people entering
  { 
    __delay_cycles(50000);
    if (P1IN & BIT4) {
      
      
      while(1)
      {
	if(P1IN &BIT5)
	{
	  
	  P1OUT |= BIT6;
	  __delay_cycles(1000000);
	  P1OUT &= ~BIT6;
	  cur_person ++;
          if (cur_person>=max_person)
          {
              for ( int i =0;i<=5;i++) 
              {
                P1OUT |= BIT6;
                __delay_cycles(200000);
                P1OUT &= ~BIT6;
                __delay_cycles(200000);
               }
          }
	  break;
	}
	
	if (P1IN & BIT4){}
	else{
	  break;
	}
      }
      P1IFG &= ~BIT5;   
      P1IFG &= ~BIT4;   
      
      display(wash_time,time_flow,cur_person);
      
    }
  }
  
  else if (P1IFG & BIT5 ) // detect people coming out
  { 
    __delay_cycles(50000);
    if (P1IN & BIT5) {
      
      
      while(1)
      {
	if(P1IN &BIT4)
	{
	  
	  P1OUT |= BIT6;
	  __delay_cycles(1000000);
	  P1OUT &= ~BIT6;
	  cur_person --;
	  break;
	}
	
	if (P1IN & BIT5){}
	else{
	  break;
	}
      }
      P1IFG &= ~BIT5;   
      P1IFG &= ~BIT4;   
      
      display(wash_time,time_flow,cur_person);
    }
  }
  
   else if (P1IFG &BIT7 ) //reduce spray time
  {	
    
    P1IFG &= ~BIT7;  
    
    P1OUT |= BIT6;
    __delay_cycles(100000);
    P1OUT &= ~BIT6;
    
    wash_time = 0;
  
    display(wash_time,time_flow,cur_person);
    
  }
}






