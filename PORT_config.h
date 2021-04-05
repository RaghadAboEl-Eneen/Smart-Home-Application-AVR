/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: PORT                    **********/
/**********      Date: 31-8-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/


#ifndef PORT_CONFIG_H_
#define PORT_CONFIG_H_

//choose 0 for input and 1 for output.

 #define PORTA_PIN0_DIR 	0	//ADC for Lm35
 #define PORTA_PIN1_DIR 	0	//ADC for LDR
 #define PORTA_PIN2_DIR 	0
 #define PORTA_PIN3_DIR 	0
 #define PORTA_PIN4_DIR 	0
 #define PORTA_PIN5_DIR 	0
 #define PORTA_PIN6_DIR 	1	//SSD control
 #define PORTA_PIN7_DIR 	1	//Buzzer Control

 
 #define PORTB_PIN0_DIR 	1
 #define PORTB_PIN1_DIR 	1
 #define PORTB_PIN2_DIR 	1
 #define PORTB_PIN3_DIR 	1	//Light intensity Control
 #define PORTB_PIN4_DIR 	1
 #define PORTB_PIN5_DIR 	1
 #define PORTB_PIN6_DIR 	1
 #define PORTB_PIN7_DIR 	1
 
 #define PORTC_PIN0_DIR 	1   //SSD Port
 #define PORTC_PIN1_DIR 	1
 #define PORTC_PIN2_DIR 	1
 #define PORTC_PIN3_DIR 	1
 #define PORTC_PIN4_DIR 	1
 #define PORTC_PIN5_DIR 	1
 #define PORTC_PIN6_DIR 	1
 #define PORTC_PIN7_DIR 	1
 
 #define PORTD_PIN0_DIR 	0 	//Rx as input
 #define PORTD_PIN1_DIR 	1	//Tx as output
 #define PORTD_PIN2_DIR 	1
 #define PORTD_PIN3_DIR 	1
 #define PORTD_PIN4_DIR 	1	//OC1B pin
 #define PORTD_PIN5_DIR 	1	//OC1A pin, Servo Control
 #define PORTD_PIN6_DIR 	1
 #define PORTD_PIN7_DIR 	1	//DC motor control
 
// 1 for pull-up or high , 0 for low.
 
 #define PORTA_PIN0_INITIAL_VALUE 0
 #define PORTA_PIN1_INITIAL_VALUE 0
 #define PORTA_PIN2_INITIAL_VALUE 0
 #define PORTA_PIN3_INITIAL_VALUE 0
 #define PORTA_PIN4_INITIAL_VALUE 0
 #define PORTA_PIN5_INITIAL_VALUE 0
 #define PORTA_PIN6_INITIAL_VALUE 0
 #define PORTA_PIN7_INITIAL_VALUE 0
 
 #define PORTB_PIN0_INITIAL_VALUE 0
 #define PORTB_PIN1_INITIAL_VALUE 0
 #define PORTB_PIN2_INITIAL_VALUE 0
 #define PORTB_PIN3_INITIAL_VALUE 0
 #define PORTB_PIN4_INITIAL_VALUE 0
 #define PORTB_PIN5_INITIAL_VALUE 0
 #define PORTB_PIN6_INITIAL_VALUE 0
 #define PORTB_PIN7_INITIAL_VALUE 0
 
 #define PORTC_PIN0_INITIAL_VALUE 0
 #define PORTC_PIN1_INITIAL_VALUE 0
 #define PORTC_PIN2_INITIAL_VALUE 0
 #define PORTC_PIN3_INITIAL_VALUE 0
 #define PORTC_PIN4_INITIAL_VALUE 0
 #define PORTC_PIN5_INITIAL_VALUE 0
 #define PORTC_PIN6_INITIAL_VALUE 0
 #define PORTC_PIN7_INITIAL_VALUE 0
 
 #define PORTD_PIN0_INITIAL_VALUE 0
 #define PORTD_PIN1_INITIAL_VALUE 0
 #define PORTD_PIN2_INITIAL_VALUE 0
 #define PORTD_PIN3_INITIAL_VALUE 0
 #define PORTD_PIN4_INITIAL_VALUE 0
 #define PORTD_PIN5_INITIAL_VALUE 0
 #define PORTD_PIN6_INITIAL_VALUE 0
 #define PORTD_PIN7_INITIAL_VALUE 0
 
 
#endif
