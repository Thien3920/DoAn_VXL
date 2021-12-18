// 12/12/2021
// Interface LCD1602 with MSP430G2553

#include <msp430g2553.h>
#include <string.h>
#include <stdio.h>

#define	LOWNIB(x)	P2OUT = (P2OUT & 0xF0) + (x & 0x0F)
#define delay_ms(x)	__delay_cycles((long)x*1000)
#define delay_us(x)	__delay_cycles((long) x)

#define EN		BIT4
#define RS		BIT5
#define DATA	0x0F
#define CLEAR	0x01

void lcdInit();		
void lcdTriggerEN();							
void lcdWriteData(unsigned char data);			
void lcdWriteCmd(unsigned char cmd);			
void lcdClear();						
void lcdPrint(char * text, int x, int y);

void lcdInit() {
	delay_ms(100);
	P2DIR = EN + RS + DATA;  // Make pins outputs
	P2OUT = 0x03;  // Start LCD (send 0x03)

	lcdTriggerEN(); // Send 0x03 3 times at 5ms then 100 us
	delay_ms(5);
	lcdTriggerEN();
	delay_ms(5);
	lcdTriggerEN();
	delay_ms(5);

	P2OUT = 0x02; // Switch 4-bit mode
	lcdTriggerEN();
	delay_ms(5);

	lcdWriteCmd(0x28); // 4-bit, 2 line, 5x8
	lcdWriteCmd(0x08); // Instruction Flow
	lcdWriteCmd(0x01); // Clear LCD
	lcdWriteCmd(0x06); // Auto-Increment
	lcdWriteCmd(0x0C); // Display On, No blink
}

void lcdTriggerEN() {
	P2OUT |= EN;
	P2OUT &= ~EN;
}

void lcdWriteData(unsigned char data) {
	P2OUT |= RS; // Set RS to Data
	LOWNIB(data >> 4);
	lcdTriggerEN();
	LOWNIB(data); 
	lcdTriggerEN();
	delay_us(50);
}

void lcdWriteCmd(unsigned char cmd) {
	P2OUT &= ~RS; // Set RS to Data
	LOWNIB(cmd >> 4); // Upper nibble
	lcdTriggerEN();
	LOWNIB(cmd); // Lower nibble
	lcdTriggerEN();
	delay_ms(5);
}

void lcdPrint(char* text, int x, int y) {
	int i;
	if (x < 16) {
		x |= 0x80; // Set LCD for first line write
		switch (y){
		case 1:
			x |= 0x40; // Set LCD for second line write
			break;
		case 2:
			x |= 0x60; // Set LCD for first line write reverse
			break;
		case 3:
			x |= 0x20; // Set LCD for second line write reverse
			break;
		}
		lcdWriteCmd(x);
	}
	i = 0;

	while (text[i] != '\0') {
		lcdWriteData(text[i]);
		i++;
	}
}

void lcdClear() {
	lcdWriteCmd(CLEAR);
}
