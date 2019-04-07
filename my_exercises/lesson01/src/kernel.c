#include "uart.h"
#include "utils.h"

short init_complete_flag = 0;



void function(unsigned long cpu)	//processor_id -> x0 -> cpu
{
	delay(2000000*cpu);

	uart_send_string("Hello, from processor <");
	uart_send('0' + cpu);
	uart_send_string(">\r\n");

	while (1) { }
}

void kernel_main(void)
{
	uart_init();

	uart_send_string("UART inited. \r\n");

	function(0);
}

