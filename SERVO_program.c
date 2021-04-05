/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: SERVO                  **********/
/**********      Date: 14-10-2020            **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include "Mapping_interface.h"

#include "TIMER_interface.h"

#include "SERVO_interface.h"
#include "SERVO_private.h"
#include "SERVO_config.h"

u8 SERVO_u8SetAngle(u8 Copy_u8ChannelID, u8 Copy_u8Angle) {

	u8 Local_u8ErrorState = OK;
	u16 Local_u16CompareMatchValue;
	u16 Local_u16OnTime;

	//0 angle is at 550Ms on time , 180 angle is at 2500Ms on time
	MAP_T Local_AngleToOnTime = { 0, 180, 550, 2500 };

	if ( (Copy_u8Angle >= 0) && (Copy_u8Angle <= 180) ) {

		//First we need to map the angle to the corresponding on time
		Local_u16OnTime = (u16) (Map_s32(&Local_AngleToOnTime, Copy_u8Angle));

		/*Servo motor needs period time of 20ms -> 50Hz.
		 * Using the following equation , overflow ticks of 24999 was calculated to generate 50hz
		 * Overflow_ticks = (u16)(10000000UL/ (Frequency * 8)) -1 ;*/
		Timer1_voidSetOverflowTicks(24999);

		Local_u16CompareMatchValue = (u16) ((10UL * Local_u16OnTime) / 8UL);
		Timer1_voidSetCompValue(Local_u16CompareMatchValue, Copy_u8ChannelID);

		//Set Timer1 Mode to be set on top clear on compare (non-inverted mode)
		Timer1_u8SetFastPWM_Mode(SET_AT_TOP_CLEAR_AT_COMPARE, Copy_u8ChannelID);

	} else {
		Local_u8ErrorState = OUT_OF_RANGE;
	}

	return Local_u8ErrorState;

}
