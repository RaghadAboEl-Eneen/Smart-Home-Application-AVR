/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: TIMER    			     **********/
/**********      Date: 24-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Mapping_interface.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"
#include "TIMER_config.h"

// Global pointer to callback function to hold the function's address
static void (*Timer0_pvOverflowCallBackFunction)(void) = NULL;

// Global pointer to callback function to hold the function's address
static void (*Timer0_pvCompareMatchCallBackFunction)(void) = NULL;

//Global variable to hold value of Timer0 Counter
static u16 Timer0_u16GlobalCounter = 0;

static u8 Timer0_u8MsTimerActive = 0; // 1 for active , 0 for inactive

/****************************************Timer initialize**************************************************/

void Timer0_voidInit(void) {

	//Initialize waveform generation mode to work as Fast PWM mode
	SET_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);



	//Set the required prescaler
	TCCR0 &= TIMER_PRESCALER_MASK;
	TCCR0 |= TIMER0_u8PRESCALER;

}

void Timer1_voidInit(void) {

	//Compare match output mode: Set on top , Clear on compare (Non-inverted mode)

	//Disable
	CLR_BIT(TCCR1A, TCCR1A_COM1A1);
	SET_BIT(TCCR1A, TCCR1A_COM1A0);

	//Waveform generation form mode: Fast PWM with ICR1 as top value
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	SET_BIT(TCCR1A, TCCR1A_WGM11);
	SET_BIT(TCCR1B, TCCR1B_WGM12);
	SET_BIT(TCCR1B, TCCR1B_WGM13);

	//Set Timer1 top value
	ICR1 = 25000;

	//Set Compare Match value OCR1A
	OCR1A = 9375;

	//Set the required prescalar
	CLR_BIT(TCCR1B, TCCR1B_CS12);
	SET_BIT(TCCR1B, TCCR1B_CS11);
	CLR_BIT(TCCR1B, TCCR1B_CS10);

	/*
	 TCCR1B &= TIMER_PRESCALER_MASK;
	 TCCR1B |= TIMER1_u8PRESCALER;
	 */
}

void Timer2_voidInit(void) {


	//Set waveform generation mode to fast PWM
	SET_BIT(TCCR2, TCCR2_WGM20);
	SET_BIT(TCCR2, TCCR2_WGM21);

	//Set Compare match output mode to Disabled
	Timer2_u8SetCompareMatchMode(DISABLE);

	//Setting the required prescalar
	CLR_BIT(TCCR2, TCCR2_CS22);
	SET_BIT(TCCR2, TCCR2_CS21);
	CLR_BIT(TCCR2, TCCR2_CS20);


	//TCCR2 &= TIMER_PRESCALER_MASK;
	//TCCR2 |= TIMER2_u8PRESCALER;

}

/**********************************************************************************************************/

/****************************************Timer0 Post Configurations****************************************/
u8 Timer0_u8OverflowSetCallBack(void (*Copy_pvCallBackFunction)(void)) {

	u8 Local_u8ErrorState = OK;

	if (Copy_pvCallBackFunction != NULL) {
		Timer0_pvOverflowCallBackFunction = Copy_pvCallBackFunction;

	} else {
		Local_u8ErrorState = NULLPOINTER;
		return Local_u8ErrorState;
	}

	return Local_u8ErrorState;

}

u8 Timer0_u8CompareMatchSetCallBack(void (*Copy_pvCallBackFunction)(void)) {

	u8 Local_u8ErrorState = OK;

	if (Copy_pvCallBackFunction != NULL) {
		Timer0_pvCompareMatchCallBackFunction = Copy_pvCallBackFunction;

	} else {
		Local_u8ErrorState = NULLPOINTER;
		return Local_u8ErrorState;
	}

	return Local_u8ErrorState;

}

void Timer0_voidSetPreload(u8 Copy_u8Preload) {

	TCNT0 = Copy_u8Preload;

}
void Timer0_voidEnableCompareMatchInterrupt(void) {

	SET_BIT(TIMSK, TIMSK_OCIE0);

}

void Timer0_voidDisableCompareMatchInterrupt(void) {

	CLR_BIT(TIMSK, TIMSK_OCIE0);

}


u8 Timer0_u8SetCompareMatchMode(u8 Copy_u8Mode) {

	u8 Local_u8ErrorState = OK;

		switch(Copy_u8Mode) {
		case SET_AT_TOP_CLEAR_AT_COMPARE: CLR_BIT(TCCR0, TCCR0_COM00); SET_BIT(TCCR0, TCCR0_COM01); break;
		case CLEAR_AT_TOP_SET_AT_COMPARE: SET_BIT(TCCR0, TCCR0_COM00); SET_BIT(TCCR0, TCCR0_COM01); break;
		case DISABLE:					  CLR_BIT(TCCR0, TCCR0_COM00); CLR_BIT(TCCR0, TCCR0_COM01); break;
		default: Local_u8ErrorState = NOOK; break;
		}

		return Local_u8ErrorState;

}


/**********************************************************************************************************/

/****************************************Timer0 Extra Applications*****************************************/
void Timer0_StopWatchMsISR(void) {

	static u16 Local_u16Counter = 0;
	Local_u16Counter++;
	if (Local_u16Counter == 5) {
		Timer0_u16GlobalCounter++;
		Local_u16Counter = 0;
	}
}


void Timer0_voidSetOnTime(u8 Copy_u8Percentage) {

	u8 Local_u8CTV;

	/*First we initialize the required map
	 * 0% -> 100% as input
	 * 0 -> 255 compare match value as output*/
	MAP_T PercentageToCTV = {0,100,0,255};

	/*Then we map the input argument to the corresponding compare match value*/
	Local_u8CTV = (u8)Map_s32(&PercentageToCTV, Copy_u8Percentage);

	/*We assign this value to the CTV register of timer2*/
	OCR0 = Local_u8CTV;

	/*Finally we activate the PWM signal*/
	Timer0_u8SetCompareMatchMode(SET_AT_TOP_CLEAR_AT_COMPARE);

}




/**********************************************************************************************************/

/****************************************Timer1 Post Configurations****************************************/

void Timer1_voidSetCompValue(u16 Copy_u16Value, u8 Copy_u8Channel) {

	if (Copy_u8Channel == CHANNEL_A) {
		OCR1A = Copy_u16Value;
	} else if (Copy_u8Channel == CHANNEL_B) {
		OCR1B = Copy_u16Value;
	}

}

void Timer1_voidDisableFastPWM(u8 Copy_u8Channel) {

	if (Copy_u8Channel == CHANNEL_A) {
		CLR_BIT(TCCR1A, TCCR1A_COM1A0);
		CLR_BIT(TCCR1A, TCCR1A_COM1A1);
	} else if (Copy_u8Channel == CHANNEL_B) {
		CLR_BIT(TCCR1A, TCCR1A_COM1B0);
		CLR_BIT(TCCR1A, TCCR1A_COM1B1);
	}

}

u8 Timer1_u8SetFastPWM_Mode(u8 Copy_u8Mode, u8 Copy_u8Channel) {

	u8 Local_u8ErrorState = OK;

	if (Copy_u8Channel == CHANNEL_A) {

		switch (Copy_u8Mode) {
		case CLEAR_AT_TOP_SET_AT_COMPARE:
			SET_BIT(TCCR1A, TCCR1A_COM1A0);
			SET_BIT(TCCR1A, TCCR1A_COM1A1);
			break;
		case SET_AT_TOP_CLEAR_AT_COMPARE:
			CLR_BIT(TCCR1A, TCCR1A_COM1A0);
			SET_BIT(TCCR1A, TCCR1A_COM1A1);
			break;
		default:
			Local_u8ErrorState = NOOK;
			break;

		}
	} else if (Copy_u8Channel == CHANNEL_B) {
		switch (Copy_u8Mode) {
		case CLEAR_AT_TOP_SET_AT_COMPARE:
			SET_BIT(TCCR1A, TCCR1A_COM1B0);
			SET_BIT(TCCR1A, TCCR1A_COM1B1);
			break;
		case SET_AT_TOP_CLEAR_AT_COMPARE:
			CLR_BIT(TCCR1A, TCCR1A_COM1B0);
			SET_BIT(TCCR1A, TCCR1A_COM1B1);
			break;
		default:
			Local_u8ErrorState = NOOK;
			break;

		}
	}
	return Local_u8ErrorState;
}

void Timer1_voidSetOverflowTicks(u16 Copy_u16OverflowTicks) {
	ICR1 = Copy_u16OverflowTicks;
}

/**********************************************************************************************************/

/****************************************Timer1 Extra Applications*****************************************/

void Timer1_voidSetTone(u32 Copy_u16Frequency, u16 Copy_u16Duration, u8 Copy_u8Channel) {

	u16 local_16OverflowTicks;
	Copy_u16Frequency = Copy_u16Frequency * 10;
	//Copy_u16Frequency = (u32)(Copy_u16Frequency / 2);
/*
	if (Copy_u16Frequency >= 140 && Copy_u16Frequency < 170) {
		Copy_u16Frequency += 1000;
	}

	if (Copy_u16Frequency < 1200) {
		Copy_u16Frequency *= 2;
	}
	if (Copy_u16Frequency > 2800) {
		Copy_u16Frequency = (u32) (Copy_u16Frequency / 2);
	}
*/
	//to achieve a certain frequency we need to calculate a specific overflow ticks count
	local_16OverflowTicks = (u16) (10000000UL / (Copy_u16Frequency * 8)) - 1;

	//Set Timer1 Top Value with calculated overflow ticks
	Timer1_voidSetOverflowTicks(local_16OverflowTicks);

	//50% duty cycle is needed , 0.5* chosen overflow ticks compare match value will achieve it
	//OCR1A = (u16) (local_16OverflowTicks / 2UL);
	Timer1_voidSetCompValue((u16) (local_16OverflowTicks / 2UL), Copy_u8Channel);

	//Activate the Fast PWM Set on top Clear on compare
	Timer1_u8SetFastPWM_Mode(SET_AT_TOP_CLEAR_AT_COMPARE, Copy_u8Channel);

	//Set the stop watch active flag
	Timer0_u8MsTimerActive = 1;

	//Activate Timer0 Compare Match Interrupt Enable to start a stop watch for duration specified
	Timer0_voidEnableCompareMatchInterrupt();

	//Polling until Ms stop watch reaches duration specified
	while (Timer0_u16GlobalCounter < Copy_u16Duration);
	/********************************************************************************************/

	//Polling ended , reset and disable everything
	//Disable fastPWM
	Timer1_voidDisableFastPWM(Copy_u8Channel);

	//Disable Timer interrupt
	Timer0_voidDisableCompareMatchInterrupt();

	//Clear the stop watch active flag
	Timer0_u8MsTimerActive = 0;

	//Reset the global counter
	Timer0_u16GlobalCounter = 0;

}

/*Input range : 0->100*/
u8 Timer1_u8SetOnTime(u16 Copy_u16Frequency, u8 Local_u8Percentage, u8 Copy_u8Channel) {

	u16 Local_16CompareMatchValue;
	u16 Local_u16OverflowTicks;
	u8 Local_u8ErrorState = OK;

	if (Local_u8Percentage >= 0 && Local_u8Percentage <= 100) {

		//Calculate frequency
		Local_u16OverflowTicks = (u16) (10000000UL / (Copy_u16Frequency * 8)) - 1;

		//Set top value of timer1
		ICR1 = Local_u16OverflowTicks;

		//mapping between percentage from 0 to 100 and compare match value from 0 to Local_u16OverflowTicks(ICR1)
		MAP_T Local_PercentageToCompareMatchValue = { 0, 100, 0, Local_u16OverflowTicks };

		//Calculating the needed compare match value
		Local_16CompareMatchValue = Map_s32(&Local_PercentageToCompareMatchValue, Local_u8Percentage);

		//Set the compare match value to timer1 channel A
		//OCR1A = Local_16CompareMatchValue;
		Timer1_voidSetCompValue(Local_16CompareMatchValue, Copy_u8Channel);

		//Activate the PWM mode : Set on top clear on compare (non-inverted)
		Timer1_u8SetFastPWM_Mode(SET_AT_TOP_CLEAR_AT_COMPARE, Copy_u8Channel);

	} else {
		Local_u8ErrorState = OUT_OF_RANGE;
	}

	return Local_u8ErrorState;
}

/**********************************************************************************************************/

/****************************************Timer2 Post Configurations****************************************/

u8 Timer2_u8SetCompareMatchMode(u8 Copy_u8Mode) {

	u8 Local_u8ErrorState = OK;

	switch(Copy_u8Mode) {

	case SET_AT_TOP_CLEAR_AT_COMPARE: CLR_BIT(TCCR2, TCCR2_COM20); SET_BIT(TCCR2, TCCR2_COM21); break;
	case CLEAR_AT_TOP_SET_AT_COMPARE: SET_BIT(TCCR2, TCCR2_COM20); SET_BIT(TCCR2, TCCR2_COM21); break;
	case DISABLE:					  CLR_BIT(TCCR2, TCCR2_COM20); CLR_BIT(TCCR2, TCCR2_COM21); break;
	default: Local_u8ErrorState = NOOK; break;

	}


	return Local_u8ErrorState;



}

/**********************************************************************************************************/



/****************************************Timer2 Extra Applications*****************************************/

void Timer2_voidSetOnTime(u8 Copy_u8Percentage) {

	u8 Local_u8CTV;

	/*First we initialize the required map
	 * 0% -> 100% as input
	 * 0 -> 255 compare match value as output*/
	MAP_T PercentageToCTV = {0,100,0,255};

	/*Then we map the input argument to the corresponding compare match value*/
	Local_u8CTV = (u8)Map_s32(&PercentageToCTV, Copy_u8Percentage);

	/*We assign this value to the CTV register of timer2*/
	OCR2 = Local_u8CTV;

	/*Finally we activate the PWM signal*/
	Timer2_u8SetCompareMatchMode(SET_AT_TOP_CLEAR_AT_COMPARE);

}




/**********************************************************************************************************/


void __vector_11(void) __attribute__((signal));
void __vector_11(void) {

	if (Timer0_pvOverflowCallBackFunction != NULL) {
		Timer0_pvOverflowCallBackFunction();
	} else {
		//Do Nothing
	}

}

void __vector_10(void) __attribute__((signal));
void __vector_10(void) {

	if (Timer0_u8MsTimerActive == 1) {

		Timer0_StopWatchMsISR();

	} else {

		if (Timer0_pvCompareMatchCallBackFunction != NULL) {
			Timer0_pvCompareMatchCallBackFunction();
		} else {
			//Do Nothing
		}
	}
}

