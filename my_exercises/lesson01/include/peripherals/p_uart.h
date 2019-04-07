#ifndef _P_UART_H
#define _P_UART_H

#include "peripherals/base.h"

#define PL011_UART_BASE     (PBASE+0x00201000)

#define PL011_UART_DR       (PL011_UART_BASE)
#define PL011_UART_RSRECR   (PL011_UART_BASE + 0X4)
#define PL011_UART_FR       (PL011_UART_BASE + 0x18)
#define PL011_UART_ILPR     (PL011_UART_BASE + 0x20)
#define PL011_UART_IBRD     (PL011_UART_BASE + 0x24)
#define PL011_UART_FBRD     (PL011_UART_BASE + 0x28)
#define PL011_UART_LCRH     (PL011_UART_BASE + 0x2c)
#define PL011_UART_CR       (PL011_UART_BASE + 0x30)
#define PL011_UART_IFLS     (PL011_UART_BASE + 0x34)
#define PL011_UART_IMSC     (PL011_UART_BASE + 0x38)
#define PL011_UART_RIS      (PL011_UART_BASE + 0x3c)
#define PL011_UART_MIS      (PL011_UART_BASE + 0x40)
#define PL011_UART_ICR      (PL011_UART_BASE + 0x44)
#define PL011_UART_DMACR    (PL011_UART_BASE + 0x48)
#define PL011_UART_ITCR     (PL011_UART_BASE + 0x80)
#define PL011_UART_ITIP     (PL011_UART_BASE + 0x84)
#define PL011_UART_ITOP     (PL011_UART_BASE + 0x88)
#define PL011_UART_TDR      (PL011_UART_BASE + 0x8c)

#endif
