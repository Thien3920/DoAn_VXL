
#include <msp430g2553.h>
#include "lcd.c"

volatile unsigned int  time_flow =1;
volatile unsigned int  wash_time = 0;

int max_time_flow =3;
int max_water=10;
char str[16];
void display(int wash_time,int time_flow)
{
  lcdClear();
  sprintf(str, "Water:%d%%" ,100-wash_time*100/max_water);
  lcdPrint(str, 0,0);
  sprintf(str, "Flow:%d", time_flow);
  lcdPrint(str, 0,1);
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
  WDTCTL = WDTPW + WDTHOLD;
  
  // p1.0 out put 
  P1DIR = BIT0;     // P1.0 : output
  P1OUT &= ~BIT0;   // P1.0 : off
  
  //P1.6 Output for button p1.2 p1.3
  P1DIR |= BIT6;
  P1OUT &=~BIT6;  
  
  //P1.6 Output for button p1.2 p1.3
  P1DIR |= BIT6;
  P1OUT &=~BIT6;  
  
  //P1.7 INPUT  FOR RESET WASH_TIME=0 (OUT OF WATER)S
  P1DIR |= BIT7;
  P1OUT &=~BIT7;  
  
  // P1.1 : dau vao cam bien tiem can  
  P1DIR &= ~BIT1; 	 // p1.1 : input
  P1REN |=BIT1;   	 // cho phep dung dien tro keo
  P1OUT &= ~BIT1; 	 // chon dien tro keo xuong
  P1IE  |=BIT1;  	  // cho phep ngat tai P1.1
  P1IES &=~BIT1;  	 //chon tin hieu ngat la suon len 
  
  // P1.2 button up 
  P1DIR &= ~BIT2;        //P1.2 : input  
  P1REN |= BIT2;         //Cho phep tro keo len
  P1OUT |= BIT2;         //Chon dien tro keo len nguon
  P1IE  |= BIT2;         //Cho phep ngat tai P1.3   
  P1IES |= BIT2;  	 //Chon tin hieu ngat la suon xuong(high-to-low)
  
  // P1.2 button down 
  P1DIR &= ~BIT3;         
  P1REN |= BIT3;         
  P1OUT |= BIT3;         
  P1IE  |= BIT3;             
  P1IES |= BIT3;         
  
 // LCD INIT
  lcdInit();
  lcdPrint("Hello Ziet", 0, 0);
  delay_ms(1000);
  
#include <msp430g2553.h>
#include "lcd.c"

volatile unsigned int  time_flow =1;
volatile unsigned int  wash_time = 0;
volatile unsigned int  cur_person = 0;

int max_person =5;
int max_time_flow =3;
int max_water=10;
char str[16];
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
  WDTCTL = WDTPW + WDTHOLD;
  
  // p1.0 out put 
  P1DIR = BIT0;     // P1.0 : output
  P1OUT &= ~BIT0;   // P1.0 : off
  
  //P1.6 Output for button p1.2 p1.3
  P1DIR |= BIT6;
  P1OUT &=~BIT6;  
  
  //P1.6 Output for button p1.2 p1.3
  P1DIR |= BIT6;
  P1OUT &=~BIT6;  
  
  //P1.7 INPUT  FOR RESET WASH_TIME=0 (OUT OF WATER)S
  P1DIR |= BIT7;
  P1OUT &=~BIT7;  
  
  // P1.1 : dau vao cam bien tiem can  
  P1DIR &= ~BIT1; 	 // p1.1 : input
  P1REN |=BIT1;   	 // cho phep dung dien tro keo
  P1OUT &= ~BIT1; 	 // chon dien tro keo xuong
  P1IE  |=BIT1;  	  // cho phep ngat tai P1.1
  P1IES &=~BIT1;  	 //chon tin hieu ngat la suon len 
  
  // P1.2 button up 
  P1DIR &= ~BIT2;        //P1.2 : input  
  P1REN |= BIT2;         //Cho phep tro keo len
  P1OUT |= BIT2;         //Chon dien tro keo len nguon
  P1IE  |= BIT2;         //Cho phep ngat tai P1.3   
  P1IES |= BIT2;  	 //Chon tin hieu ngat la suon xuong(high-to-low)
  
  // P1.3 button down 
  P1DIR &= ~BIT3;         
  P1REN |= BIT3;         
  P1OUT |= BIT3;         
  P1IE  |= BIT3;             
  P1IES |= BIT3;         
  
    // P1.4 : cam bien phat hien nguoi vao
  P1DIR &= ~BIT4; 	 // p1.1 : input
  P1REN |=BIT4;   	 // cho phep dung dien tro keo
  P1OUT |= BIT4; 	 // chon dien tro keo len
  P1IE  |=BIT4;  	  // cho phep ngat tai P1.4
  P1IES |=BIT4;  	 //chon tin hieu ngat la suon xuong
  
  // P1.5 cam bien phat hien nguoi ra
  P1DIR &= ~BIT5;         
  P1REN |= BIT5;         
  P1OUT |= BIT5;         
  P1IE  |= BIT5;             
  P1IES |= BIT5; 
  
  // LCD INIT
  lcdInit();
  lcdPrint("Hello ", 0, 0);
  delay_ms(1000);
  
  display(wash_time,time_flow,cur_person);
  
  _BIS_SR(LPM4_bits + GIE);         // cho phep ngat toan cuc		
  
}
#pragma vector=PORT1_VECTOR         // khai bao vector ngat
__interrupt void Port_1(void)       // chuong trinh ngat
{
  
  if (P1IFG & BIT1 ) // cam bien tiem can rua tay
  { 
    __delay_cycles(50000);
    if (P1IN & BIT1) {}
    else
    {
      P1OUT |= BIT0;
      delay_(time_flow);  
      P1OUT &= ~BIT0;
      P1IFG &= ~BIT1;   // xoa co ngat
      
      wash_time = wash_time + time_flow;
      if(wash_time>= max_water)
      {
	wash_time=max_water;
	for ( int i =0;i<=5;i++) // canh bao het nuoc p1.6
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
    
  
  else if (P1IFG &BIT2 ) // nhan giam time_flow
  {	
    
    P1IFG &= ~BIT2;  
    
    P1OUT |= BIT6;
    __delay_cycles(10000);
    P1OUT &= ~BIT6;
    
    time_flow --;
    if (time_flow < 1) time_flow =1;
    display(wash_time,time_flow,cur_person);
    
  }
  else if (P1IFG &BIT3 )// nhan tang time_flow
  {
    
    P1IFG &= ~BIT3;   // xoa co ngat
    P1OUT |= BIT6;
    __delay_cycles(10000);
    P1OUT &= ~BIT6;
    
    time_flow ++;
    if (time_flow > max_time_flow) time_flow =max_time_flow;
    display(wash_time,time_flow,cur_person);
    
  }
  else if (P1IFG & BIT4 ) // cam bien phat hien nguoi vao
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
	 break;
      }
      
      if (P1IN & BIT4){}
      else{
	break;
      }
      }
      P1IFG &= ~BIT5;   // xoa co ngat
      P1IFG &= ~BIT4;   // xoa co ngat
    
    display(wash_time,time_flow,cur_person);
    
    }
  }
  
  else if (P1IFG & BIT5 ) // cam bien phat hien nguoi vao
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
      P1IFG &= ~BIT5;   // xoa co ngat
      P1IFG &= ~BIT4;   // xoa co ngat
    
    display(wash_time,time_flow,cur_person);
    
    }
  }
  

  

 else if (P1IFG &BIT7 )//reset wash_time
 {
   
   P1IFG &= ~BIT7;   // xoa co ngat
   
   P1OUT |= BIT6;
   __delay_cycles(10000);
   P1OUT &= ~BIT6;
   
   wash_time =0;
   display(wash_time,time_flow,cur_person);
   
 }

}















