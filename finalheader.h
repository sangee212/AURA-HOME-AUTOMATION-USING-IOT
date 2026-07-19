
#include<lpc21xx.h>
#define LED0 1<<14
#define LED1 1<<15
#define LED2 1<<16
#define LED3 1<<17

#define LCD 0xf<<4
#define RS 1<<8
#define E 1<<9
       
void UART_CONFIG(void)
{
 PINSEL0=0X5;
 U0LCR=0X83;
 U0DLL=97;
 U0DLM=0;
 U0LCR=0X03;
}

void UART_TX(unsigned char tx)
{
 U0THR=tx;
 while(((U0LSR>>5)&1==0));
}

unsigned char UART_RX(void)
{
 while((U0LSR&1)==0);
 return U0RBR;
}

void UART_STRING(unsigned char*s)
{
 while(*s)
 {
  UART_TX(*s++);
 }
}

void delay_milliseconds(unsigned int ms)
{
 T0PR=15000-1;
 T0TCR=0X01;
 while(T0TC<ms);
 T0TCR=0X03;
 T0TCR=0X00;  
}

void LCD_COMMAND(unsigned char cmd)
{
 IOCLR0=LCD;
 IOSET0=(cmd&0xf0)<<0;
 IOCLR0=RS;
 IOSET0=E;
 delay_milliseconds(2);
 IOCLR0=E;

 IOCLR0=LCD;
 IOSET0=(cmd&0x0f)<<4;
 IOCLR0=RS;
 IOSET0=E;
 delay_milliseconds(2);
 IOCLR0=E;
}

void LCD_DATA(unsigned char d)
{
 IOCLR0=LCD;
 IOSET0=(d&0xf0)<<0;
 IOSET0=RS;
 IOSET0=E;
 delay_milliseconds(2);
 IOCLR0=E;

 IOCLR0=LCD;
 IOSET0=(d&0x0f)<<4;
 IOSET0=RS;
 IOSET0=E;
 delay_milliseconds(2);
 IOCLR0=E;
}

void LCD_INIT()
{
 IODIR0|=LCD|RS|E;
 LCD_COMMAND(0x01);
 LCD_COMMAND(0x02);
 LCD_COMMAND(0x28);
 LCD_COMMAND(0x80);
}

void LCD_STR(unsigned char *s)
{
 while(*s)
  LCD_DATA(*s++);
}
