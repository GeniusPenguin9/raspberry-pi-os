#include "utils.h"
#include "peripherals/p_uart.h"
#include "peripherals/gpio.h"

void uart_send ( char c )
{
    while(get32(PL011_UART_FR) & (1<<5)) { }
	put32(PL011_UART_DR, c);
}

char uart_recv ( void )
{
    while(get32(PL011_UART_FR) & (1<<4)) { }
	return(get32(PL011_UART_DR)&0xFF);
}

void uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void uart_init ( void )
{
    //Page 92 & 102, use gpio14&15 for UART0
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 0b100<<12;                  // set alt0 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 0b100<<15;                  // set alt0 for gpio15
	put32(GPFSEL1,selector);

    //Page 101: GPIO Pull-up/down Clock Registers
	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

    
    put32(PL011_UART_CR, 0);                      //disable cr register
    put32(PL011_UART_IMSC, 0);                    // Disable all interrupts 

    //set baud rate to 115200
    //default option in config.txt : init_uart_clock = 48MHz
    //https://www.raspberrypi.org/documentation/configuration/config-txt/boot.md
    //BAUDDIV = (FUARTCLK/(16 Baud rate)) = 48*10^6 / (16*115200)=26.0417
    //http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0183g/I54603.html
    //IBRD = 26
    //BRDF = 0.0417, FBRD = integer ( (BRDF × 64) + 0.5 ) = 3
    put32(PL011_UART_IBRD, 26);
    put32(PL011_UART_FBRD, 3);
    
    put32(PL011_UART_LCRH, (1<<4)|(3<<5));//word length = 8 bits, FIFOS ensable

    put32(PL011_UART_IMSC, 0);                  // mask interupts 
    put32(PL011_UART_CR, (1<<0)|(1<<8)|(1<<9)); //enable cr register
}
