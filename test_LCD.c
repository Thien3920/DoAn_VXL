#include <msp430g2553.h>
#include "lcd.c"

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    lcdInit();
    lcdPrint("Hello", 0, 0);
    delay_ms(1000);
    lcdClear();
    lcdPrint("Test LCD ", 0,0);
}
