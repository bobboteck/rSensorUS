/* 
 * File:   interrupts.h
 * Author: roberto
 *
 * Created on 12 settembre 2013, 11.47
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

void interrupt low_priority InterruptHandlerLow(void);
void interrupt InterruptHandlerHigh(void);

#endif	/* INTERRUPTS_H */

