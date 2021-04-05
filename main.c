/*
 * main.c
 *
 *  Created on: 22 Oct 2020
 *      Author: es-RaghadAly2023
 */
#include <util/delay.h>

#include "STD_TYPES.h"
#include "Mapping_interface.h"

#include "DIO_interface.h"
#include "USART_interface.h"
#include "PORT_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"
#include "ADC_interface.h"

#include "SERVO_interface.h"
#include "SSD_interface.h"
#include "Buzzer_interface.h"

#define ACTIVE			1
#define INACTIVE		0

#define CORRECT			1
#define INCORRECT		0

#define TRACK_1			1
#define TRACK_2			2
#define NUM_OF_TRACKS	2

#define NUM_OF_USERS	10

MAP_T TemperatureToOnTime = { 15, 30, 0, 100 }; //Mapping from temperature to on time %
MAP_T LightToOnTime = {21, 231, 0, 100 };	    //Mapping from light intensity to on time %

static u8 Percentage;						    //Variable to hold the return of the map function
static volatile u8 MelodyCounter = 0;		    //Variable to go through array of music notes
static u8 TrackSelector = TRACK_1;
static u16 TEMPERATURE_u16ADC_Reading = 0;	    //Variable to hold the output of ADC conversion
static u16 TEMPERATURE_u16AnalogValue = 0;


static u8 WelcomePhaseFlag = ACTIVE;

/*Flags relating to the login phase*/
static u8 IdPhaseFlag = INACTIVE;
static u8 IdCheckPhaseFlag = INACTIVE;
static u8 PasswordPhaseFlag = INACTIVE;
static u8 PasswordCheckPhaseFlag = INACTIVE;

/*Flags relating to viewing and choosing from the main menu phase*/
static u8 MainMenuOptionsPhase = INACTIVE;
static u8 MainMenuPhaseFlag = INACTIVE;


static u8 FanControlPhaseFlag = INACTIVE;

static u8 DoorControlPhaseFlag = INACTIVE;

static u8 LightControlPhaseFlag = INACTIVE;
static u8 LightMapPhaseFlag = INACTIVE;

static u8 BuzzerControlPhaseFlag = INACTIVE;
static u8 MusicPhaseFlag = INACTIVE;

static u8 TemperatureMapPhaseFlag = INACTIVE;

static u8 SystemClosePhaseFlag = INACTIVE;

static u8 ErrorPhaseFlag = INACTIVE;

static u8 OptionSelect; //Variable that hold the option the user selects
static u8 Temperature;	//Variable to hold the calculated temperature
static u8 StringSize;	//Variable to hold the size of the entered username/password



void MainMenuOptionsISR(void); //ISR for when an option in the main menu is selected
void FanOptionsISR(void);	   //ISR for when an option in the fan's menu is selected
void DoorOptionsISR(void);	   //ISR for when an option in the door's menu is selected
void LightOptionsISR(void);	   //ISR for when an option in the light's menu is selected
void ADC_TemperatureISR(void); //ISR for when LM35 ADC conversion is complete
void ADC_LightISR(void);	   //ISR for when LDR ADC conversion is complete
void MusicOptionsISR(void);	   //ISR for when an option in the music's menu is selected

void main(void) {

	PORT_voidInit();		//Initalizing port directions
	ADC_voidInit();			//Initalizing the ADC
	USART_voidInit();		//Initalizing the USART
	Timer0_voidInit();		//Initalizing timer0
	Timer1_voidInit();		//Initalizing timer1
	Timer2_voidInit();		//INitalizing timer2
	GIE_voidEnableGlobal(); //Enabling the global interrupt enable

	SSD_T SSD_One = { CKATHODE, DIO_u8PORTC, DIO_u8PORTA, DIO_u8PIN6 }; // Initalizing the SSD

	/*Melodies to be played*/
	u16 Local_u16Melody[] = { F, A, B, PAUSE, F, A, B, PAUSE, F, A, B, PAUSE, PAUSE, B, PAUSE, B, G, E, PAUSE, PAUSE, D, E, G, E, PAUSE, F, A, B, PAUSE, F, A, B, F, A, B, PAUSE, B, PAUSE, B, G, PAUSE, B, G, D, E, PAUSE, D, E, F, PAUSE, G, A, B, PAUSE, B, E, PAUSE, F, G, A, PAUSE, B, A, B, PAUSE, D, E, F, PAUSE, G, END };
	u16 Local_u16Twinkle[] = { G, G, D, D, E, E, D, PAUSE, C, C, B, B, A, A, G, PAUSE, D, D, C, C, B, B, A, PAUSE, D, D, C, C, B, B, A, PAUSE, G, G, D, D, E, E, D, PAUSE, C, C, B, B, A, A, G, END };
	/***********************/

	u8 Local_u8NumberOfTries = 3; //Initalizing the number of tries a user has to enter a correct password
	u8 Local_u8UsernameState = CORRECT; //Variable to indicate if the entered username is correct or wrong
	u8 Local_u8PasswordState = CORRECT; //Variable to indicate if the entered password is correct or wrong

	u8 Local_u8ID[20];					//Variable to hold the entered username
	u8 Local_u8Password[20];			//Variable to hold the entered password
	u8 Local_u8NameCounter = 0;
	u8 Local_u8LetterCounter;
	u8 Local_u8Size;					//Variable to hold the size of the corresponding username/password

	const char * Local_pchUsernames[10] = { "nada"     , "layla"   , "aly"   , "manar"  , "reem"  , "farah", "ahmed" , "salim", "nour", "merna" }; //List of usernames
	const char * Local_pchPasswords[10] = { "1234", "gpl6q367u", "yq3x", "steu7e1q", "e3wum", "afra5q", "ltuwb", "vjf7h8buk", "nbw1hh", "fz2uj"}; //List of corresponding passwords

	SERVO_u8SetAngle(CHANNEL_A, 0);	//Initially , the door is closed

	while (1) {

		/*If the MusicPhaseFlag is active, it doesn't deactivate and plays one single note in every cycle in the super loop
		 *It can be deactivated by choosing to deactivate the system or choosing to stop playing music in the music menu phase
		 **/
		if (MusicPhaseFlag == ACTIVE) {

			if (TrackSelector == TRACK_1) {
				Buzzer_u16PlayTone(Local_u16Melody[MelodyCounter], 200);
				MelodyCounter++;

				if (Local_u16Melody[MelodyCounter] == 0) {
					MelodyCounter = 0;
				}
			} else if (TrackSelector == TRACK_2) {
				Buzzer_u16PlayTone(Local_u16Twinkle[MelodyCounter], 500);
				MelodyCounter++;

				if (Local_u16Twinkle[MelodyCounter] == 0) {
					MelodyCounter = 0;
				}
			}

		}

		/*The first flag to be active in the start of the program
		 *It deactivates itself and nothing can reactivate it
		 **/
		if (WelcomePhaseFlag == ACTIVE) {

			WelcomePhaseFlag = INACTIVE;
			USART_u8SendStringSynchronous("Welcome");
			USART_u8SendData('\n');
			Local_u8NumberOfTries = 3;
			IdPhaseFlag = ACTIVE;

		}

		/*The IdPhaseFlag deactivates itself and can be reactivated if the username is invalid*/

		if (IdPhaseFlag == ACTIVE) {
			IdPhaseFlag = INACTIVE;
			USART_u8SendStringSynchronous("Please enter your username");
			USART_u8SendData('\n');

			/*In case of timeout (user took too long to enter username) the string size would be equal to 0
			 *A do-while loop takes care of this*/

			do {
				/*This function returns the size of the received string*/
				StringSize = USART_u8ReceiveStringSynchronous((char*) Local_u8ID);
			}
			while (StringSize == 0);

			IdCheckPhaseFlag = ACTIVE;
			USART_u8SendStringSynchronous((char*)Local_u8ID);
			USART_u8SendData('\n');
		}

		/*This phase checks if the entered username is valid or invalid*/
		if (IdCheckPhaseFlag == ACTIVE) {

			IdCheckPhaseFlag = INACTIVE;


			/*This loop goes through every defined username to check if it matches the entered username*/
			for (Local_u8NameCounter = 0; Local_u8NameCounter < NUM_OF_USERS; Local_u8NameCounter++) {

				Local_u8Size = 0;
				Local_u8LetterCounter = 0;

				/*Loops through every defined username and gets its size*/
				while (Local_pchUsernames[Local_u8NameCounter][Local_u8LetterCounter] != '\0') {
					Local_u8Size++;
					Local_u8LetterCounter++;
				}

				/*If the size matches the size of the entered username, it might be correct
				 *Otherwise it is incorrect
				 **/
				if (Local_u8Size == StringSize) {

					/*Loops through every letter to check if they all match*/
					for (Local_u8LetterCounter = 0; Local_u8LetterCounter < Local_u8Size; Local_u8LetterCounter++) {

						if ((u8) (Local_u8ID[Local_u8LetterCounter]) == (u8) (Local_pchUsernames[Local_u8NameCounter][Local_u8LetterCounter])) {
							Local_u8UsernameState = CORRECT;
						} else {
							Local_u8UsernameState = INCORRECT;
						}

					}

					/*If the UsernameState stays CORRECT (every letter matches) then the username is valid*/
					if (Local_u8UsernameState == CORRECT) {
						USART_u8SendStringSynchronous("Hello ");
						USART_u8SendStringSynchronous((char*) Local_u8ID);
						USART_u8SendData('\n');
						PasswordPhaseFlag = ACTIVE;
						break;
					}

				} else {
					Local_u8UsernameState = INCORRECT;
				}

			}

			/*If the username is incorrect , the user is given the chance to enter their username again*/
			if (Local_u8UsernameState == INCORRECT) {
				USART_u8SendStringSynchronous("Invalid Username");
				USART_u8SendData('\n');
				IdPhaseFlag = ACTIVE;
			}

		}


		/*In this phase the user enters their password
		 *This phase activates only if the username is correct
		 *It can reactivate is the user enters an incorrect password for up to 3 times*/


		if (PasswordPhaseFlag == ACTIVE) {
			PasswordPhaseFlag = INACTIVE;
			SSD_u8On(&SSD_One); // turning on the SSD to display the number of tries left
			SSD_u8SetNumber(&SSD_One, Local_u8NumberOfTries);
			USART_u8SendStringSynchronous("Please enter your password");
			USART_u8SendData('\n');

			//Similar to the IdPhaseFlag procedure

			do {
				StringSize = USART_u8ReceiveStringSynchronous((char*) Local_u8Password);
			}
			while (StringSize == 0);

			PasswordCheckPhaseFlag = ACTIVE;
		}

		/*The password is checked if it is correct or incorrect in this phase*/
		if (PasswordCheckPhaseFlag == ACTIVE) {

			PasswordCheckPhaseFlag = INACTIVE;

			/*Procedure is similar to IdCheckPhase procedure*/

			Local_u8Size = 0;
			Local_u8LetterCounter = 0;

			while (Local_pchPasswords[Local_u8NameCounter][Local_u8LetterCounter] != '\0') {
				Local_u8Size++;
				Local_u8LetterCounter++;

			}


			if (Local_u8Size == StringSize) {

				for (Local_u8LetterCounter = 0; Local_u8LetterCounter < Local_u8Size; Local_u8LetterCounter++) {

					if ( (u8) (Local_pchPasswords[Local_u8NameCounter][Local_u8LetterCounter]) == (u8) (Local_u8Password[Local_u8LetterCounter]) ) {

						Local_u8PasswordState = CORRECT;
					} else {
						Local_u8PasswordState = INCORRECT;
						break;
					}

				}
			} else {
				Local_u8PasswordState = INCORRECT;
			}

			Local_u8NumberOfTries--;

			/*If the password is correct*/
			if (Local_u8PasswordState == CORRECT) {
				MainMenuOptionsPhase = ACTIVE; // This phase will tell the user the options avaiable to them
				SSD_u8Off(&SSD_One);
				USART_u8SendStringSynchronous("Welcome ");
				USART_u8SendStringSynchronous((char*) Local_u8ID);
				USART_u8SendData(' ');
				SERVO_u8SetAngle(CHANNEL_A, 90); // Door is opened


				/*If the password is correct but there are still tries left*/
			} else if (Local_u8PasswordState == INCORRECT && Local_u8NumberOfTries != 0) {

				SSD_u8SetNumber(&SSD_One, Local_u8NumberOfTries);
				USART_u8SendStringSynchronous("Password Incorrect, Please try again");
				USART_u8SendData('\n');
				PasswordPhaseFlag = ACTIVE;

				/*If the password is correct but there are no tries left*/
			} else if (Local_u8PasswordState == INCORRECT && Local_u8NumberOfTries == 0) {

				SSD_u8Off(&SSD_One);

				USART_u8SendStringSynchronous("Intruder Alert");

				while(1) {
				Buzzer_u16PlayTone(2000,200);
				_delay_ms(100);
				Buzzer_u16PlayTone(1000,200);
				_delay_ms(100);
				}


			}

		}

		/*This phase activates whenever an option is selected from the sub menus or an invalid option is entered*/

		if (MainMenuOptionsPhase == ACTIVE) {

			MainMenuOptionsPhase = INACTIVE;

			USART_u8SendStringSynchronous("Choose one of the following options:");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("1 for fan control");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("2 for door control");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("3 for light control");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("4 to play music");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("5 to close the system");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("6 to hear the options again");
			USART_u8SendData('\n');

			MainMenuPhaseFlag = ACTIVE;

		}

		/*In this phase, the system waits for a user input to activate an ISR*/
		if (MainMenuPhaseFlag == ACTIVE) {
			MainMenuPhaseFlag = INACTIVE;
			USART_u8SendStringSynchronous("Press the button and say an option");
			USART_u8SendData('\n');
			USART_u8ReceiveBufferAsynchronous(&OptionSelect, 1, &MainMenuOptionsISR);

		}

		/*In this phase , the user chooses an action on the fan*/
		if (FanControlPhaseFlag == ACTIVE) {
			FanControlPhaseFlag = INACTIVE;

			USART_u8SendStringSynchronous("Choose one of the following options:");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("1 to open the fan");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("2 to close the fan");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("3 to adjust fan speed to temperature");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("4 to return to the main menu");
			USART_u8SendData('\n');

			USART_u8ReceiveBufferAsynchronous(&OptionSelect, 1, &FanOptionsISR); //system waits for user input

		}

		/*In this phase, the user chooses an action on the door*/
		if (DoorControlPhaseFlag == ACTIVE) {
			DoorControlPhaseFlag = INACTIVE;

			USART_u8SendStringSynchronous("Choose one of the following options:");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("1 to open the door");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("2 to close the door");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("3 to return to the main menu");
			USART_u8SendData('\n');

			USART_u8ReceiveBufferAsynchronous(&OptionSelect, 1, &DoorOptionsISR); //system waits for user input

		}

		/*In this phase, the user chooses an action on the lights*/
		if (LightControlPhaseFlag == ACTIVE) {
			LightControlPhaseFlag = INACTIVE;

			USART_u8SendStringSynchronous("Choose one of the following options:");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("1 to open the lights");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("2 to close the lights");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("3 to adjust light intensity");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("4 to return to the main menu");
			USART_u8SendData('\n');

			USART_u8ReceiveBufferAsynchronous(&OptionSelect, 1, &LightOptionsISR); //system waits for user input

		}

		/*In this phase, the user chooses an action on the buzzer (playing music)*/
		if (BuzzerControlPhaseFlag == ACTIVE) {
			BuzzerControlPhaseFlag = INACTIVE;

			USART_u8SendStringSynchronous("Choose one of the following options:");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("1 to play music");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("2 to change track");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("3 to stop plaing music");
			USART_u8SendData('\n');
			USART_u8SendStringSynchronous("4 to return to main menu");
			USART_u8SendData('\n');

			USART_u8ReceiveBufferAsynchronous(&OptionSelect, 1, &MusicOptionsISR); //system waits for user input

		}

		/*This phase activates when the user chooses to close the entire system*/
		if (SystemClosePhaseFlag == ACTIVE) {
			SystemClosePhaseFlag = INACTIVE;
			MusicPhaseFlag = INACTIVE;
			Timer0_u8SetCompareMatchMode(DISABLE);
			Timer1_voidDisableFastPWM(CHANNEL_A);
			Timer2_u8SetCompareMatchMode(DISABLE);
			USART_u8SendStringSynchronous("Goodbye ");
			USART_u8SendStringSynchronous((char*) Local_u8ID);

		}

		/*This phase actiavates when the user enters an invalid option*/
		if (ErrorPhaseFlag == ACTIVE) {
			ErrorPhaseFlag = INACTIVE;
			USART_u8SendStringSynchronous("Please say a valid option");
			USART_u8SendData('\n');
			MainMenuPhaseFlag = ACTIVE;
		}

		/*This phase starts the conversion of the LM35 output to digital*/
		if (TemperatureMapPhaseFlag == ACTIVE) {
			TemperatureMapPhaseFlag = INACTIVE;
			ADC_u8StartSingleConversionAsynch(0, &TEMPERATURE_u16ADC_Reading, &ADC_TemperatureISR);
		}

		/*This phase starts the conversion of the LDR output to digital*/
		if (LightMapPhaseFlag == ACTIVE) {
			LightMapPhaseFlag = INACTIVE;
			ADC_u8StartSingleConversionAsynch(1, &TEMPERATURE_u16ADC_Reading, &ADC_LightISR);

		}

	}

}

/*Depending on the option selected by the user , a specific action is executed*/
void LightOptionsISR(void) {

	switch (OptionSelect) {
	case '1':
		Timer0_voidSetOnTime(100); //Lights turned on at max intensity
		break;
	case '2':
		Timer0_u8SetCompareMatchMode(DISABLE);	//Lights turned off
		break;
	case '3':
		LightMapPhaseFlag = ACTIVE;	 //Mapping the LDR output to adjust the light intensity accordingly
		break;
	case '4':
		MainMenuPhaseFlag = ACTIVE;	//Option to return to the main menu
		break;
	default:
		ErrorPhaseFlag = ACTIVE;
		break;
	}
	MainMenuPhaseFlag = ACTIVE;

}

/*Depending on the option selected by the user , a specific action is executed*/
void MainMenuOptionsISR(void) {

	switch (OptionSelect) {
	case '1':
		FanControlPhaseFlag = ACTIVE;	//System waits for user to select option relating to the fan
		break;
	case '2':
		DoorControlPhaseFlag = ACTIVE;	//System waits for the user to select an option relating to the door
		break;
	case '3':
		LightControlPhaseFlag = ACTIVE;	//System waits for the user to select an option relating to the lights
		break;
	case '4':
		BuzzerControlPhaseFlag = ACTIVE;//System waits for the user to select an option relating to the buzzer
		break;
	case '5':
		SystemClosePhaseFlag = ACTIVE;  //System closes completly
		break;
	case '6':
		MainMenuOptionsPhase = ACTIVE;	//User can see the options avaialble again if he chooses this option
		break;
	default:
		ErrorPhaseFlag = ACTIVE;
		break;
	}

}

/*Depending on the option selected by the user , a specific action is executed*/
void FanOptionsISR(void) {

	switch (OptionSelect) {

	case '1':
		Timer2_voidSetOnTime(100); //Fan is turned on
		MainMenuPhaseFlag = ACTIVE;

		break;
	case '2':
		Timer2_u8SetCompareMatchMode(DISABLE); //Fan is turned off
		MainMenuPhaseFlag = ACTIVE;

		break;
	case '3':
		TemperatureMapPhaseFlag = ACTIVE;	//Fan speed is adjusted according to temperature
		MainMenuPhaseFlag = ACTIVE;

		break;
	case '4':
		MainMenuPhaseFlag = ACTIVE;
		break;
	default:
		ErrorPhaseFlag = ACTIVE;
		break;
	}

}

/*Conversion of the Temperature that is calculated from the LM#% output to a percentage to use in the PWm signal*/
void ADC_TemperatureISR(void) {

	/*Calculating the temperature*/
	TEMPERATURE_u16AnalogValue = ((u32) TEMPERATURE_u16ADC_Reading * 5000UL) / 256UL;
	Temperature = TEMPERATURE_u16AnalogValue / 10;

	/*Mapping temperature->percentage*/
	Percentage = Map_s32(&TemperatureToOnTime, Temperature);
	if (Percentage == 0) {
		Timer2_u8SetCompareMatchMode(DISABLE); //At lowest temperature , fan should be turned off
	} else {
		Timer2_voidSetOnTime(Percentage);
	}

}

/*Depending on the option selected by the user , a specific action is executed*/
void DoorOptionsISR(void) {

	switch (OptionSelect) {
	case '1':
		SERVO_u8SetAngle(CHANNEL_A, 90); //Door is open
		MainMenuPhaseFlag = ACTIVE;
		break;
	case '2':
		SERVO_u8SetAngle(CHANNEL_A, 0);	//Door is closed
		MainMenuPhaseFlag = ACTIVE;
		break;
	case '3':
		MainMenuPhaseFlag = ACTIVE;
		break;
	default:
		ErrorPhaseFlag = ACTIVE;
		break;
	}

}

/*Conversion of the LDR output to a percentage to use in the PWM signal*/
void ADC_LightISR(void) {

	/*Light intensity -> percentage*/
	Percentage = Map_s32(&LightToOnTime, TEMPERATURE_u16ADC_Reading);

	/*Maximum light intensity -> leds should turn off*/
	if (Percentage == 100) {
		Timer0_u8SetCompareMatchMode(DISABLE); //Turning off the lights
	} else {
		Timer0_voidSetOnTime(100 - Percentage); //at minimum light intensity -> leds should be at maximum light intensity (100-0)
	}
}

/*Depending on the option selected by the user , a specific action is executed*/
void MusicOptionsISR(void) {

	switch (OptionSelect) {

	case '1': /*Music starts playing , first track is selected*/
		MusicPhaseFlag = ACTIVE;
		MelodyCounter = 0;
		MainMenuPhaseFlag = ACTIVE;
		break;
	case '2':/*Track is switched*/
		MusicPhaseFlag = ACTIVE;
		MelodyCounter = 0;
		TrackSelector++;
		if (TrackSelector > NUM_OF_TRACKS) {
			TrackSelector = TRACK_1;
		}
		MainMenuPhaseFlag = ACTIVE;
		break;
	case '3':/*Music is turned off*/
		MusicPhaseFlag = INACTIVE;
		MainMenuPhaseFlag = ACTIVE;
		break;
	case '4':
		MainMenuPhaseFlag = ACTIVE;
		break;
	default:
		ErrorPhaseFlag = ACTIVE;
		break;

	}

}

