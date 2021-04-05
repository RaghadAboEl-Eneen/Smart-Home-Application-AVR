/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: TIMER    			     **********/
/**********      Date: 24-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define TIMER_PRESCALER_MASK 0b11111000

#define TIMER01_STOP									0
#define TIMER01_DIVIDE_BY_1								1
#define TIMER01_DIVIDE_BY_8								2
#define TIMER01_DIVIDE_BY_64							3
#define TIMER01_DIVIDE_BY_256							4
#define TIMER01_DIVIDE_BY_1024							5
#define TIMER01_DIVIDE_BY_EXT_CLOCK_FALLING_EDGE		6
#define TIMER01_DIVIDE_BY_EXT_CLOCK_RISING_EDGE			7

#define TIMER2_STOP										0
#define TIMER2_DIVIDE_BY_1								1
#define TIMER2_DIVIDE_BY_8								2
#define TIMER2_DIVIDE_BY_32								3
#define TIMER2_DIVIDE_BY_64								4
#define TIMER2_DIVIDE_BY_128							5
#define TIMER2_DIVIDE_BY_256							6
#define TIMER2_DIVIDE_BY_1024							7

																								    /*Top value*/
#define TIMER1_WAVEFORM_MODE_0							0		//Normal							OxFFFF
#define TIMER1_WAVEFORM_MODE_1							1		//PWM, Phase correct, 8 bit			0x00FF
#define TIMER1_WAVEFORM_MODE_2							2		//PWM, Phase correct, 9 bit			0x01FF
#define TIMER1_WAVEFORM_MODE_3							3		//PWM, Phase correct, 10 bit		0x03FF
#define TIMER1_WAVEFORM_MODE_4							4		//CTC								OCR1A
#define TIMER1_WAVEFORM_MODE_5							5		//Fast PWM, 8 bit					0X00FF
#define TIMER1_WAVEFORM_MODE_6							6		//Fast PWM, 9 bit					0X01FF
#define TIMER1_WAVEFORM_MODE_7							7		//Fast PWM, 10 bit					0X03FF
#define TIMER1_WAVEFORM_MODE_8							8		//PWM, Phase and frequency correct	ICR1
#define TIMER1_WAVEFORM_MODE_9							9		//PWM, Phase and frequency correct	OCR1A
#define TIMER1_WAVEFORM_MODE_10							10		//PWM, Phase correct				ICR1
#define TIMER1_WAVEFORM_MODE_11							11		//PWM, Phase correct				OCR1A
#define TIMER1_WAVEFORM_MODE_12							12		//CTC								ICR1
#define TIMER1_WAVEFORM_MODE_14							14		//FAST PWM							ICR1
#define TIMER1_WAVEFORM_MODE_15							15		//FAST PWM							OCR1A


#endif
