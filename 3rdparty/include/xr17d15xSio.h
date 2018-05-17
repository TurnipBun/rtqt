/* xr17d15xSio.h - Multiport Serial Driver for EXAR's PCI Family of UARTs (XR17D158) */

/* Copyright 1984-2002 Wind River Systems, Inc. */
#include "copyright_wrs.h"
/*

modification history
--------------------
01a,13nov03,tsi  written (copied from i8250SioPep.h)
*/

#ifndef	__INCxr17d15xSioh
#define	__INCxr17d15xSioh

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _ASMLANGUAGE

#include "vxWorks.h"
#include "sioLib.h"

/* defines */

/* channel data structure  */
typedef struct xr17d15xChan	/* XR17D15X_CHAN */
{
	SIO_DRV_FUNCS * pDrvFuncs;	/* driver functions */

	STATUS	(*getTxChar) ();	/* pointer to xmitr function */
	STATUS	(*putRcvChar) ();	/* pointer tp rcvr function */
	void *	getTxArg;
	void *	putRcvArg;

	UINT16	int_vec;			/* interrupt vector number */
	UINT16	channelMode;		/* SIO_MODE_[INT | POLL] */

	UCHAR	(*inByte) (int);		/* routine to read a byte from register */
	void		(*outByte)(int,char);	/* routine to write a byte to register */

	ULONG data;		/* UART data register */
	ULONG brdl;		/* UART baud rate register */
	ULONG brdh;	/* UART baud rate register */
	ULONG ier;		/* UART interrupt enable register */
	ULONG isr;		/* UART interrupt ID register */
	ULONG fcr;		/* UART Fifo Control register */
	ULONG lcr;		/* UART line control register */
	ULONG mcr;		/* UART modem control register */
	ULONG lsr;		/* UART line status register */
	ULONG msr;		/* UART modem status register */
	ULONG spr;		/* UART indexed control register */                        

	ULONG fctr;		/* Feature Control Register */
	ULONG efr;		/* EFR - Enhanced Function Reg */
	ULONG txcnt;	/* Transmit FIFO Level Counter ,Read-Only*/
	ULONG txtrg;	/* Transmit FIFO Trigger Level ,Write-Only */
	ULONG rxcnt;	/* Receive FIFO Level Counter, ,Read-Only */
	ULONG rxtrg;	/* Receive FIFO Trigger Level ,Write-Only */

	ULONG   options;	/* UART hardware options */

} XR17D15X_CHAN;

typedef struct			/* BAUD */
{
	int rate;		/* a baud rate */
	UINT dlm;	/* the value of dlm */
	UINT dll;		/* the value of dll */
}XR17D15X_BAUD;


/* PEP modification: additional IOCTL calls */
#define SIO_RS485		0x80000000  /* enable/disable RS485 mode */
#define SIO_LOOPBACK	0x80000001  /* enable/disable the loopback mode */
#define SIO_SPR_SET		0x80000003  /* write spr register */
#define SIO_SPR_GET		0x80000004  /* Read spr register value */
#define SIO_HW_SET		0x80000005
#define SIO_HW_GET		0x80000006
/* end of PEP modification */

/* register definitions */

#define XR17D15X_UTHR		0x00	/* Transmitter holding reg. */
#define XR17D15X_URDR		0x00	/* Receiver data reg.       */
#define XR17D15X_UBRDL		0x00	/* Baud rate divisor (LSB)  */
#define XR17D15X_UBRDH	0x01	/* Baud rate divisor (MSB)  */
#define XR17D15X_UIER		0x01	/* Interrupt enable reg.    */
#define XR17D15X_UIID		0x02	/* Interrupt ID reg.        */
#define XR17D15X_UFCR		0x02	/* Fifo Control reg.        */
#define XR17D15X_ULCR		0x03	/* Line control reg.        */
#define XR17D15X_UMDC		0x04	/* Modem control reg.       */
#define XR17D15X_ULST		0x05	/* Line status reg.         */
#define XR17D15X_UMSR		0x06	/* Modem status reg.        */
#define XR17D15X_USPR		0x07	/* SCRATCH PAD REGISTER (SPR) - Read/Write.     */

/*
 * The special register set for XR17x15y UARTs.  Enhanced Register.
 */

#define XR_17X15Y_EXTENDED_FCTR	8
#define XR_17X15Y_EXTENDED_EFR	9	/* EFR - Enhanced Function Reg */
#define XR_17X15Y_TXFIFO_CNT		10	/* Transmit FIFO Level Counter ,Read-Only*/
#define XR_17X15Y_TXFIFO_TXTRG	10 	/* Transmit FIFO Trigger Level ,Write-Only */
#define XR_17X15Y_RXFIFO_CNT		11	/* Receive FIFO Level Counter, ,Read-Only */
#define XR_17X15Y_EXTENDED_RXTRG	11	/* Receive FIFO Trigger Level ,Write-Only */

#define XR17D15X_UXOFF1	12	/* Xoff Character 1.       */
#define XR17D15X_UXOFF2	13	/* Xoff Character 2.         */
#define XR17D15X_UXON1		14	/* Modem status reg.        */
#define XR17D15X_UXON2		35	/* indexed control reg.     */

#define XR_17X15Y_FCTR_RTS_8DELAY	0x03
#define XR_17X15Y_FCTR_TRGD			192

/* 17D15X TX/RX memory mapped buffer offsets */

#define UART_17X15Y_RX_OFFSET		0x100
#define UART_17X15Y_TX_OFFSET 		0x100

/*
 * These are the EXTENDED definitions for the 17D15X's Interrupt
 * Enable Register
 */
#define	XR_17X15Y_IER_RTSDTR	0x40
#define XR_17X15Y_IER_CTSDSR	0x80
/* Enhanced Register */
#define XR17D15X_UTRG	0x00	/* Transmitter holding reg. */
#define XR17D15X_UFC	0x00	/* Receiver data reg.       */
#define XR17D15X_UFCTR	0x01	/* Baud rate divisor (LSB)  */
#define XR17D15X_UEFR	0x02	/* Baud rate divisor (MSB)  */


/* equates for interrupt enable register */

#define XR17D15X_IER_RXRDY	0x01	/* receiver data ready */
#define XR17D15X_IER_TBE		0x02	/* transmit bit enable */
#define XR17D15X_IER_LST		0x04	/* line status interrupts */
#define XR17D15X_IER_MSI		0x08	/* modem status interrupts */

/* equates for interrupt identification register */

#define XR17D15X_IIR_IP			0x01	/* interrupt pending bit */
#define XR17D15X_IIR_MASK		0x07	/* interrupt id bits mask */
#define XR17D15X_IIR_MSTAT 	0x00	/* modem status interrupt */
#define XR17D15X_IIR_THRE		0x02	/* transmit holding register empty */
#define XR17D15X_IIR_RBRF		0x04	/* receiver buffer register full */
#define XR17D15X_IIR_SEOB		0x06	/* serialization error or break */

/* equates for line control register */

#define XR17D15X_LCR_CS5		0x00	/* 5 bits data size */
#define XR17D15X_LCR_CS6		0x01	/* 6 bits data size */
#define XR17D15X_LCR_CS7		0x02	/* 7 bits data size */
#define XR17D15X_LCR_CS8		0x03	/* 8 bits data size */
#define XR17D15X_LCR_2_STB  	0x04	/* 2 stop bits */
#define XR17D15X_LCR_1_STB		0x00	/* 1 stop bit */
#define XR17D15X_LCR_PEN		0x08	/* parity enable */
#define XR17D15X_LCR_PDIS   	0x00	/* parity disable */
#define XR17D15X_LCR_EPS		0x10	/* even parity slect */
#define XR17D15X_LCR_SP		0x20	/* stick parity select */
#define XR17D15X_LCR_SBRK		0x40	/* break control bit */
#define XR17D15X_LCR_DLAB		0x80	/* divisor latch access enable */

/* equates for the modem control register */

#define XR17D15X_MCR_DTR	0x01	/* dtr output */
#define XR17D15X_MCR_RTS	0x02	/* rts output */
#define XR17D15X_MCR_OUT1	0x04	/* output #1 */
#define XR17D15X_MCR_OUT2	0x08	/* output #2 */
#define XR17D15X_MCR_LOOP	0x10	/* loop back */
#define XR17D15X_MCR_BRG	0x80	/* BRG Prescaler */

/* equates for line status register */

#define XR17D15X_LSR_RXRDY	0x01	/* receiver data available */
#define XR17D15X_LSR_OE		0x02	/* overrun error */
#define XR17D15X_LSR_PE		0x04	/* parity error */
#define XR17D15X_LSR_FE		0x08	/* framing error */
#define XR17D15X_LSR_BI		0x10	/* break interrupt */
#define XR17D15X_LSR_THRE	0x20	/* transmit holding register empty */
#define XR17D15X_LSR_TEMT	0x40	/* transmitter empty */

/* equates for modem status register */

#define XR17D15X_MSR_DCTS	0x01	/* cts change */
#define XR17D15X_MSR_DDSR	0x02	/* dsr change */
#define XR17D15X_MSR_DRI	0x04	/* ring change */
#define XR17D15X_MSR_DDCD	0x08	/* data carrier change */
#define XR17D15X_MSR_CTS	0x10	/* complement of cts */
#define XR17D15X_MSR_DSR	0x20	/* complement of dsr */
#define XR17D15X_MSR_RI		0x40	/* complement of ring signal */
#define XR17D15X_MSR_DCD	0x80	/* complement of dcd */

/*
 * LCR=0xBF (or DLAB=1 for 16C2850)
 */
#define UART_EFR			2	/* I/O: Extended Features Register */
#define UART_EFR_CTS		0x80 /* CTS flow control */
#define UART_EFR_RTS		0x40 /* RTS flow control */
#define UART_EFR_SCD		0x20 /* Special character detect */
#define UART_EFR_ECB		0x10 /* Enhanced control bit */
/*
 * the low four bits control software flow control
 */

/*
 * LCR=0xBF, TI16C752, ST16650, ST16650A, ST16654
 */
#define UART_XON1			4	/* I/O: Xon character 1 */
#define UART_XON2			5	/* I/O: Xon character 2 */
#define UART_XOFF1			6	/* I/O: Xoff character 1 */
#define UART_XOFF2			7	/* I/O: Xoff character 2 */

/*
 * EFR[4]=1 MCR[6]=1, TI16C752
 */
#define UART_TI752_TCR		6	/* I/O: transmission control register */
#define UART_TI752_TLR		7	/* I/O: trigger level register */

/*
 * LCR=0xBF, XR16C85x
 */
#define UART_TRG			0	/* FCTR bit 7 selects Rx or Tx
								 * In: Fifo count
				 				 * Out: Fifo custom trigger levels */
				 				 
/*
 * These are the definitions for the Programmable Trigger Register
 */
#define UART_TRG_1			0x01
#define UART_TRG_4			0x04
#define UART_TRG_8			0x08
#define UART_TRG_16			0x10
#define UART_TRG_32			0x20
#define UART_TRG_64			0x40
#define UART_TRG_96			0x60
#define UART_TRG_120		0x78
#define UART_TRG_128		0x80

#define UART_FCTR				1	/* Feature Control Register */
#define UART_FCTR_RTS_NODELAY	0x00  /* RTS flow control delay */
#define UART_FCTR_RTS_4DELAY	0x01
#define UART_FCTR_RTS_6DELAY	0x02
#define UART_FCTR_RTS_8DELAY	0x03
#define UART_FCTR_IRDA			0x04  /* IrDa data encode select */
#define UART_FCTR_TX_INT		0x08  /* Tx interrupt type select */
#define UART_FCTR_TRGA			0x00  /* Tx/Rx 550 trigger table select */
#define UART_FCTR_TRGB			0x10  /* Tx/Rx 650 trigger table select */
#define UART_FCTR_485_ENABLE	0x20  /* Auto 485 Enable */
#define UART_FCTR_TRGD			0x30  /* Tx/Rx 850 programmable trigger select */
#define UART_FCTR_SCR_SWAP		0x40  /* Scratch pad register swap */
#define UART_FCTR_RX			0x00  /* Programmable trigger mode select */
#define UART_FCTR_TX			0x80  /* Programmable trigger mode select */


#if defined(__STDC__) || defined(__cplusplus)

extern void xr17d15xHrdInit(XR17D15X_CHAN *pDev);
extern void xr17d15xInt(XR17D15X_CHAN  *pDev);
extern STATUS sysXr17d15xPciInit(void);

#else

extern void xr17d15xHrdInit();
extern void xr17d15xInt();
	     
#endif  /* __STDC__ */


#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCxr17d15xh */
