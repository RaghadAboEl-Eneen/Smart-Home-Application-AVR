/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: EEPROM       **************/
/**********			Date:13-10-2020         **************/            
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8Data);

u8 EEPPROM_u8ReadDataByte(u16 Copy_u16LocationAddress);

void EEPROM_voidSendString(u16 Copy_u16LocationAddress, u8 Copy_u8BufferSize,const char * Copy_pchString);

void EEPROM_voidReceieveDataBuffer(u16 Copy_u16LocationAddress,u8 *Copy_pu8Data);


#endif
