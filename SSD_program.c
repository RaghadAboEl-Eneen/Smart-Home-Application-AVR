/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: SSD    			     **********/
/**********      Date: 26-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "SSD_interface.h"
#include "SSD_config.h"
#include "SSD_private.h"

static u8 sev_seg[10] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111 };

u8 SSD_u8SetNumber(SSD_T * Copy_SSD_Config_Struct, u8 Copy_u8Number) {

	u8 Local_u8ErrorState = OK;
	u8 Local_u8Counter;
	u8 Local_u8PortArray[] = SSD_PORT_ARR;
	u8 Local_u8PinArray[] = SSD_PIN_ARR;

	if (Copy_SSD_Config_Struct != NULL) {
		if ((Copy_u8Number >= 0) && (Copy_u8Number <= 9)) {

			if (Copy_SSD_Config_Struct->Type == CANODE) {

				if (PIN_MODE == SEQUENTIAL) {
					DIO_u8SetPortValue(Copy_SSD_Config_Struct->Data_Port, ~(sev_seg[Copy_u8Number]));
				}

				else if (PIN_MODE == SCATTERED) {

					for (Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++) {

						DIO_u8SetPinValue(Local_u8PortArray[Local_u8Counter], Local_u8PinArray[Local_u8Counter], GET_BIT(~(sev_seg[Copy_u8Number]), Local_u8Counter));

					}

				}

			} else if (Copy_SSD_Config_Struct->Type == CKATHODE) {
				if (PIN_MODE == SEQUENTIAL) {

					DIO_u8SetPortValue(Copy_SSD_Config_Struct->Data_Port, sev_seg[Copy_u8Number]);

				} else if (PIN_MODE == SCATTERED) {

					for (Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++) {

						DIO_u8SetPinValue(Local_u8PortArray[Local_u8Counter], Local_u8PinArray[Local_u8Counter], GET_BIT(sev_seg[Copy_u8Number], Local_u8Counter));

					}

				}

			} else {
				Local_u8ErrorState = NOOK;
			}

		} else {
			Local_u8ErrorState = NOOK;
		}
	} else {
		Local_u8ErrorState = NULLPOINTER;
	}
	return Local_u8ErrorState;

}

u8 SSD_u8On(SSD_T * Copy_SSD_Config_Struct) {

	u8 Local_u8ErrorState = OK;

	if (Copy_SSD_Config_Struct != NULL) {
		if (Copy_SSD_Config_Struct->Type == CANODE) {
			DIO_u8SetPinValue(Copy_SSD_Config_Struct->Enable_Port, Copy_SSD_Config_Struct->Enable_Pin, DIO_u8PIN_HIGH);
		} else if (Copy_SSD_Config_Struct->Type == CKATHODE) {
			DIO_u8SetPinValue(Copy_SSD_Config_Struct->Enable_Port, Copy_SSD_Config_Struct->Enable_Pin, DIO_u8PIN_LOW);
		}
	} else {
		Local_u8ErrorState = NULLPOINTER;
	}

	return Local_u8ErrorState;

}

u8 SSD_u8Off(SSD_T * Copy_SSD_Config_Struct) {

	u8 Local_u8ErrorState = OK;

	if (Copy_SSD_Config_Struct != NULL) {
		if (Copy_SSD_Config_Struct->Type == CANODE) {
			DIO_u8SetPinValue(Copy_SSD_Config_Struct->Enable_Port, Copy_SSD_Config_Struct->Enable_Pin, DIO_u8PIN_LOW);
		} else if (Copy_SSD_Config_Struct->Type == CKATHODE) {
			DIO_u8SetPinValue(Copy_SSD_Config_Struct->Enable_Port, Copy_SSD_Config_Struct->Enable_Pin, DIO_u8PIN_HIGH);
		}
	} else {
		Local_u8ErrorState = NULLPOINTER;
	}
	return Local_u8ErrorState;
}

