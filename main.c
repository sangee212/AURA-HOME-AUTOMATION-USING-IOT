#include "finalheader.h"
void LCD_LIGHT()
{
    LCD_COMMAND(0x01);

    LCD_COMMAND(0x80);
    LCD_STR("LIGHT 1 :");

    LCD_COMMAND(0xC0);
    LCD_STR("LIGHT 2 :");

    LCD_COMMAND(0x94);
    LCD_STR("LIGHT 3 :");

    LCD_COMMAND(0xD4);
    LCD_STR("LIGHT 4 :");
}

int main()
{
    unsigned char rxbyte;

    IODIR0 |= LED0 | LED1 | LED2 | LED3;
    IOSET0 = LED0 | LED1 | LED2 | LED3;

    LCD_INIT();

    LCD_STR(" SANGEETHA");
    LCD_COMMAND(0xC0);
    LCD_STR(" V25CE6S2");
    delay_milliseconds(1000);

    LCD_COMMAND(0x01);
    delay_milliseconds(5);

    LCD_STR(" AURA HOME");
    LCD_COMMAND(0xC0);
    LCD_STR(" AUTOMATION");
    delay_milliseconds(1000);

    LCD_LIGHT();

    UART_CONFIG();

    while(1)
    {
        rxbyte = UART_RX();

        // LIGHT 1
        if(rxbyte == 'A')
        {
            IOCLR0 = LED0;
            LCD_COMMAND(0x8A);
            LCD_STR("ON ");
        }
        else if(rxbyte == 'a')
        {
            IOSET0 = LED0;
            LCD_COMMAND(0x8A);
            LCD_STR("OFF ");
        }

        // LIGHT 2
        else if(rxbyte == 'B')
        {
            IOCLR0 = LED1;
            LCD_COMMAND(0xCA);
            LCD_STR("ON ");
        }
        else if(rxbyte == 'b')
        {
            IOSET0 = LED1;
            LCD_COMMAND(0xCA);
            LCD_STR("OFF ");
        }

        // LIGHT 3
        else if(rxbyte == 'C')
        {
            IOCLR0 = LED2;
            LCD_COMMAND(0x9E);
            LCD_STR("ON ");
        }
        else if(rxbyte == 'c')
        {
            IOSET0 = LED2;
            LCD_COMMAND(0x9E);
            LCD_STR("OFF ");
        }

        // LIGHT 4
        else if(rxbyte == 'D')
        {
            IOCLR0 = LED3;
            LCD_COMMAND(0xDE);
            LCD_STR("ON ");
        }
        else if(rxbyte == 'd')
        {
            IOSET0 = LED3;
            LCD_COMMAND(0xDE);
            LCD_STR("OFF ");
        }

        else
        {
            IOSET0 = LED0 | LED1 | LED2 | LED3;
        }
    }
}


