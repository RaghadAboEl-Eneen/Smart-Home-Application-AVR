/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: TIMER    			     **********/
/**********      Date: 24-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_


/****************************************Timer 0***************************************************/
#define TCCR0			*((volatile u8*)0x53)   		//Timer0 Counter Control Register
#define TCCR0_FOC0		7								//Force Output Compare
#define TCCR0_WGM00		6								//Waveform Generation Mode Bit 0
#define TCCR0_COM01		5								//Compare match output mode Bit 1
#define TCCR0_COM00		4								//Compare match output mode Bit 0
#define TCCR0_WGM01		3								//Waveform Generation Mode Bit 1
#define TCCR0_CS02		2								//Clock select Bit 2
#define TCCR0_CS01		1								//Clock select Bit 1
#define TCCR0_CS00		0								//Clock select Bit 0

#define TCNT0			*((volatile u8*)0x52)			//Timer0 Counter  register
#define OCR0			*((volatile u8*)0x5C)			//Timer0 Output compare match register

#define TIMSK			*((volatile u8*)0x59)			//Timer  Mask Register
#define TIMSK_OCIE0		1								//Timer0 compare match interrupt enable
#define TIMSK_TOIE0		0								//Timer0 Overflow Interrupt Enable

#define TIFR			*((volatile u8*)0x59)			//Timer  interrupt flag register
#define TIFR_OCF0		1								//Timer0 Compare match flag
#define TIFR_TOV0		0								//Timer0 overflow flag
/**************************************************************************************************/


/****************************************Timer 1***************************************************/
#define TCCR1A			*((volatile u16*)0x4F)			//Timer1 Control Register A
#define TCCR1A_COM1A1	7								//Compare output mode for channel A bit1
#define TCCR1A_COM1A0	6								//Compare output mode for channel A bit0
#define TCCR1A_COM1B1	5								//Compare output mode for channel B bit1
#define TCCR1A_COM1B0	4								//Compare output mode for channel B bit0
#define TCCR1A_FOC1A	3								//Force compare match for channel A
#define TCCR1A_FOC1B	2								//Force compare match for channel B
#define TCCR1A_WGM11	1								//Waveform generation mode bit1
#define TCCR1A_WGM10	0								//Waveform generation mode bit0

#define TCCR1B			*((volatile u16*)0x4E)			//Timer1 Control Register B
#define TCCR1B_ICNC1	7								//Input capture noise canceler
#define TCCR1B_ICES1	6								//Input capture edge select
#define TCCR1B_WGM13	4								//Waveform generation mode bit3
#define TCCR1B_WGM12	3								//Waveform generation mode bit2
#define TCCR1B_CS12		2								//Clock select bit2
#define TCCR1B_CS11		1								//Clock select bit1
#define TCCR1B_CS10		0								//Clock select bit0

#define TIMSK_TICIE1	5								//Input capture interrupt enable
#define TIMSK_OCIE1A	4								//Output compare match A interrupt enable
#define TIMSK_OCIE1B	3								//Output compare match B interrupt enable
#define TIMSK_TOIE1		2								//Overflow interrupt enable

#define TIFR_ICF1		5								//Input capture flag
#define TIFR_OCF1A		4								//Output compare match flag A
#define TIFR_OCF1B		3								//OUtput compare match flag B
#define TIFR_TOV1		2								//Overflow flag

#define TCNT1			*((volatile u16*)0x4C)			//Timer1 16 bit counter

#define OCR1A			*((volatile u16*)0x4A)			//Output compare match counter for channel A

#define OCR1B			*((volatile u16*)0x48)			//Output compare match counter for channel B

#define ICR1			*((volatile u16*)0x46)			//Input Capture Register

/**************************************************************************************************/

/****************************************Timer 2***************************************************/
#define TCCR2			*((volatile u8*)0x45)				//Timer2 control register
#define TCCR2_FOC2		7									//Force output compare
#define TCCR2_WGM20		6									//Waveform generation mode bit 0
#define TCCR2_COM21		5									//Compare match output mode bit 1
#define TCCR2_COM20		4									//Compare match output mdoe bit 0
#define TCCR2_WGM21		3									//Waveform generation mode bit 1
#define TCCR2_CS22		2									//Clock select bit 2
#define TCCR2_CS21		1									//Clock select bit 1
#define TCCR2_CS20		0									//Clock select bit 0

#define ASSR			*((volatile u8*)0x42)
#define ASSR_AS2		3									//Timer2 Asynchronous mode enable
#define ASSR_TCN2UB		2									//Timer2 update busy
#define ASSR_OCR2UB		1									//Timer2 Compare match register busy
#define ASSR_TCR2UB		0									//Timer 2 Control register update busy

#define TIMSK_OCIE2		7									//Timer2 compare match interrupt enable
#define TIMSK_TOIE2		6									//Timer2 overflow interrupt enable

#define TIFR_OCF2		7									//Timer2 compare match flag
#define TIFR_TOV2		6									//Timer2 overflow flag

#define TCNT2			*((volatile u8*)0x44)				//Timer2 8 bit counter

#define OCR2			*((volatile u8*)0x43)				//Timer2 8 bit compare match counter
/**************************************************************************************************/




#endif
