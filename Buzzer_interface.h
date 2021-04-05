/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: Buzzer                 **********/
/**********      Date: 25-10-2020            **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

#define PAUSE	1
#define END		0



#define A		1500//880
#define B		1700//988
#define C		1900//1047
#define D		2100//1175
#define E		2300//1319
#define F		2500//1397
#define G		2700//1568


u8 Buzzer_u16PlayTone(u16 Copy_u16Frequency, u16 Copy_u16Duration);



#endif
