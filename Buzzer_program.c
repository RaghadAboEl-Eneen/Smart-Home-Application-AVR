/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: Buzzer                 **********/
/**********      Date: 25-10-2020            **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include <util/delay.h>

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "USART_interface.h"
#include "Buzzer_interface.h"
#include "Buzzer_config.h"

u8 Buzzer_u16PlayTone(u16 Copy_u16Frequency, u16 Copy_u16Duration) {

	u32 Local_u16Counter;

	u32 Local_u32RequiredTime = (u32) ((u32) Copy_u16Duration * 1000);

	u32 Local_u16PeriodTime = (u32) ((1000000 / (u32) Copy_u16Frequency));

	f32 Local_u16DelayTime = (Local_u16PeriodTime / 2UL);

	u32 Local_u16NumOfLoops = (u32) (Local_u32RequiredTime / Local_u16PeriodTime);

	if (Copy_u16Frequency == PAUSE) {
		_delay_us(Local_u32RequiredTime);
	} else {

		for (Local_u16Counter = 0; Local_u16Counter < Local_u16NumOfLoops; Local_u16Counter += 4) {

			DIO_u8SetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_u8PIN_HIGH);
			_delay_us(Local_u16DelayTime);
			DIO_u8SetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_u8PIN_LOW);
			_delay_us(Local_u16DelayTime);

		}

	}

	return Local_u16Counter;

}
