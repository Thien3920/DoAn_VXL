
#include <msp430g2553.h>

volatile unsigned int  time_flow =1;


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
  default:
    if (time > 3)
    {
      __delay_cycles(3000000);
      time_flow --;
    }
    
    else if (time <= 0) 
    {
      __delay_cycles(1000000);
      time_flow ++;
    }
    
      
      
  }
}

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  
  // p1.0 out put 
  P1DIR = BIT0;     // P1.0 : output
  P1OUT &= ~BIT0;   // P1.0 : off
  
  //P1.6 OUT OUT 
  P1DIR |= BIT6;
  P1OUT &=~BIT6;  
  
  // P1.1 : dau vao cam bien tiem can  
  P1DIR &= ~BIT1;  // p1.1 : input
  P1REN |=BIT1;    // cho phep dung dien tro keo
  P1OUT &= ~BIT1;  // chon dien tro keo xuong
  P1IE  |=BIT1;    // cho phep ngat tai P1.1
  P1IES &=~BIT1;   //chon tin hieu ngat la suon len 
  
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
  
  _BIS_SR(LPM4_bits + GIE);         // cho phep ngat toan cuc		
  
}
#pragma vector=PORT1_VECTOR         // khai bao vector ngat
__interrupt void Port_1(void)       // chuong trinh ngat
{
  
  if (P1IFG & BIT1 )
  { 
    __delay_cycles(50000);
    if (P1IN & BIT1) {}
    else
    {
     P1OUT |= BIT0;
    delay_(time_flow);  
    P1OUT &= ~BIT0;
    P1IFG &= ~BIT1;   // xoa co ngat
    }
    
  }
  else if (P1IFG &BIT2 )
  {	
    
    P1IFG &= ~BIT2;  
    
    P1OUT |= BIT6;
    __delay_cycles(500000);
    P1OUT &= ~BIT6;
   
    time_flow --;
  }
  else if (P1IFG &BIT3 )
  {
    
    P1IFG &= ~BIT3;   // xoa co ngat
    P1OUT |= BIT6;
    __delay_cycles(500000);
    P1OUT &= ~BIT6;
    time_flow ++;
    
  }
  
}







/*
#include <msp430g2553.h>

volatile unsigned int  time_flow =1;


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
  default:
    if (time > 3)
    {
      __delay_cycles(3000000);
      time_flow --;
    }
    
    else if (time <= 0) 
    {
      __delay_cycles(1000000);
      time_flow ++;
    }
    
      
      
  }
}

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  
  // p1.0 out put 
  P1DIR = BIT0;     // P1.0 : output
  P1OUT &= ~BIT0;   // P1.0 : off
  
  //P1.6 OUT OUT 
  P1DIR |= BIT6;
  P1OUT &=~BIT6;  
  
  // P1.1 : dau vao cam bien tiem can  
  P1DIR &= ~BIT1;  // p1.1 : input
  P1REN |=BIT1;    // cho phep dung dien tro keo
  P1OUT &= ~BIT1;  // chon dien tro keo xuong
  P1IE  |=BIT1;    // cho phep ngat tai P1.1
  P1IES &=~BIT1;   //chon tin hieu ngat la suon len 
  
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
  
  _BIS_SR(LPM4_bits + GIE);         // cho phep ngat toan cuc		
  
}
#pragma vector=PORT1_VECTOR         // khai bao vector ngat
__interrupt void Port_1(void)       // chuong trinh ngat
{
  
  if (P1IFG & BIT1 )
  { 

    
    P1OUT |= BIT0;
    delay_(time_flow);  
    P1OUT &= ~BIT0;
    P1IFG &= ~BIT1;   // xoa co ngat
  }
  else if (P1IFG &BIT2 )
  {	
    
    P1IFG &= ~BIT2;  
    
    P1OUT |= BIT6;
    delay_(1);
    P1OUT &= ~BIT6;
   
    time_flow ++;
  }
  else if (P1IFG &BIT3 )
  {
    
    P1IFG &= ~BIT3;   // xoa co ngat
    P1OUT |= BIT6;
    delay_(1);
    P1OUT &= ~BIT6;
    time_flow --;
    
  }
  
}


*/





