#ifndef	_BOOT_H
#define	_BOOT_H

extern void put32 ( unsigned long, unsigned int );
extern unsigned int get32 ( unsigned long );
extern unsigned int proc_id  ( void );

#define delay(i){                   \
	{for (int j = 0; j < i; j++);}  \
}

#endif  /*_BOOT_H */
