#include "utils.h"
#include "peripherals/p_uart.h"
#include "peripherals/gpio.h"

void uart_send ( char c )
{
	//To enable transmission, the TXE bit and UARTEN bit must be set to 1
    while(1) {
		if(get32(PL011_UART_FR) & (1 << 5))  
			break;
	}
	put32(PL011_UART_DR, c);
}

char uart_recv ( void )
{
    //To enable reception, the RXE bit and UARTEN bit, must be set to 1
	while(1) {
		if(get32(PL011_UART_FR) & (1 << 4))  
			break;
	}
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

    //disable cr register
    selector = get32(PL011_UART_CR);
    selector |= 0;
    put32(PL011_UART_CR, selector);
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
    
    //when PL011_UART_LCRH reset, all bits are 0, no need clean
    selector = get32(PL011_UART_LCRH);  
    selector |= 0<<7;   //disable stick parity select
    selector |= 0b11<<5;    //word length = 8 bits
    selector |= 0<<4;       //FIFOS disable
    selector |= 0<<3;       //one stop bit
    selector |= 0<<1;       //disable parity
    selector |= 0;          //after transmission keep high-level
    put32(PL011_UART_LCRH, selector);

    //enable cr register
    selector = get32(PL011_UART_CR);
    selector |= 1<<9;
    selector |= 1<<8;
    selector |= 1;
    put32(PL011_UART_CR, selector);   

}
