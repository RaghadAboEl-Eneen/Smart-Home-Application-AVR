/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: TIMER    			     **********/
/**********      Date: 24-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef SSD_CONFIG_H_
#define SSD_CONFIG_H_



#define PIN_MODE	SCATTERED

/*Configuration only used in scattered mode
 * specifiy dio port and pin of every pin of the seven segment from A to dot*/

#define A_PORT		DIO_u8PORTD
#define A_PIN		DIO_u8PIN2

#define B_PORT		DIO_u8PORTD
#define B_PIN		DIO_u8PIN3

#define C_PORT		DIO_u8PORTC
#define C_PIN		DIO_u8PIN2

#define D_PORT		DIO_u8PORTC
#define D_PIN		DIO_u8PIN3

#define E_PORT		DIO_u8PORTC
#define E_PIN		DIO_u8PIN4

#define F_PORT		DIO_u8PORTC
#define F_PIN		DIO_u8PIN5

#define G_PORT		DIO_u8PORTC
#define G_PIN		DIO_u8PIN6

#define DOT_PORT	DIO_u8PORTC
#define DOT_PIN		DIO_u8PIN7



#endif
