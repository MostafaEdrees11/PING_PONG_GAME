/*
 * Ping_Pong_Game.c
 *
 * Created: 2/4/2024 1:57:24 PM
 *  Author: Mostafa Edrees
 */ 

#include "Ping_Pong_Game_priv.h"
#include "Ping_Pong_Game_config.h"

extern EXTI_Configuration_t EXTI_AStrEXTI_Config[MAX_NUM_EXTI];
extern SEG_t SEV_SEG_AstrSEGConfig[SEG_NUM];

s8 PING_PONG_Ball_Position = 0;
u8 PING_PONG_Ball_Line_Position = 0;
u8 PLAYER_1_RES, PLAYER_2_RES; 
state MOVING_STATE = start;

void Player1_Interrupt(void *ptr)
{
	MOVING_STATE = right;
}

void Player2_Interrupt(void *ptr)
{
	MOVING_STATE = left;
}

ES_t PING_PONG_GAME_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	
	DIO_enuSetPinDirection(DIO_u8PORTD, DIO_u8PIN2, DIO_u8INPUT);
	DIO_enuSetPinVal(DIO_u8PORTD, DIO_u8PIN2, DIO_u8PULL_UP);
	DIO_enuSetPinDirection(DIO_u8PORTD, DIO_u8PIN3, DIO_u8INPUT);
	DIO_enuSetPinVal(DIO_u8PORTD, DIO_u8PIN3, DIO_u8PULL_UP);
	
	LCD_enuInit();
	Seven_Segment_enuInit(SEV_SEG_AstrSEGConfig);
	LCD_enuSendCommand(LCD_DisplayOn_CursorOff_NoBlinking);
	EXTI_enuInit(EXTI_AStrEXTI_Config);
	EXTI_enuEnable(EXTI0);
	EXTI_enuEnable(EXTI1);
	EXTI_enuCallBackFunc(&Player1_Interrupt, NULL, EXTI0);
	EXTI_enuCallBackFunc(&Player2_Interrupt, NULL, EXTI1);
	
	LCD_enuWriteString("$PING PONG GAME$");
	Seven_Segment_enuDisplayNumber(0,0);
	Seven_Segment_enuDisplayNumber(1,0);
	_delay_ms(2000);
	LCD_vidClearScreen();
	
	GIE_enuGloable_Interrupt_Enable();
	
	return Local_enuErrorState;
}

ES_t PING_PONG_GAME_enuStartPlaying(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	
	while(PLAYER_1_RES < 3 && PLAYER_2_RES < 3)
	{
		MOVING_STATE = start;
		PING_PONG_Ball_Position = 0;
		PING_PONG_vidRoundNum();
		PING_PONG_GAME_vidPlayRound();
	}
	
	if(PLAYER_1_RES > PLAYER_2_RES)
	{
		LCD_vidClearScreen();
		LCD_enuWriteString("     Winner     ");
		LCD_enuWriteString("   Player One   ");
	}
	else
	{
		LCD_vidClearScreen();
		LCD_enuWriteString("     Winner     ");
		LCD_enuWriteString("   Player Two   ");
	}
	
	return Local_enuErrorState;
}

static void PING_PONG_GAME_vidPlayRound(void)
{
	while(1)
	{
		if(MOVING_STATE == right)
		{
			PING_PONG_Ball_Position = 0;
			while (1)
			{
				if(MOVING_STATE != right || PING_PONG_Ball_Position >= 16)
				break;
				
				LCD_vidClearScreen();
				LCD_enuGoToPosition(PING_PONG_Ball_Line_Position,PING_PONG_Ball_Position);
				LCD_enuDisplayChar('0');
				PING_PONG_Ball_Line_Position = !PING_PONG_Ball_Line_Position;
				_delay_ms(250);
				PING_PONG_Ball_Position++;
			}
		}
		
		if(MOVING_STATE == left)
		{
			PING_PONG_Ball_Position = 15;
			while(1)
			{
				if(MOVING_STATE != left || PING_PONG_Ball_Position < 0)
				break;
				LCD_vidClearScreen();
				LCD_enuGoToPosition(PING_PONG_Ball_Line_Position,PING_PONG_Ball_Position);
				LCD_enuDisplayChar('0');
				PING_PONG_Ball_Line_Position = !PING_PONG_Ball_Line_Position;
				_delay_ms(250);
				PING_PONG_Ball_Position--;
			}
		}
		
		if(PING_PONG_Ball_Position >= 16 && MOVING_STATE != left)
		{
			PLAYER_1_RES++;
			Seven_Segment_enuDisplayNumber(0,PLAYER_1_RES);
			break;
		}
		else if(PING_PONG_Ball_Position < 0 && MOVING_STATE != right)
		{
			PLAYER_2_RES++;
			Seven_Segment_enuDisplayNumber(1,PLAYER_2_RES);
			break;
		}
	}
}

static void PING_PONG_vidRoundNum(void)
{
	LCD_vidClearScreen();
	switch(PLAYER_1_RES+PLAYER_2_RES)
	{
		case 0:
		LCD_enuWriteString("   1st Round   ");
		_delay_ms(1000);
		break;
		
		case 1:
		LCD_enuWriteString("   2nd Round   ");
		_delay_ms(1000);
		break;
		
		case 2:
		LCD_enuWriteString("   3rd Round   ");
		_delay_ms(1000);
		break;
		
		case 3:
		LCD_enuWriteString("   4th Round   ");
		_delay_ms(1000);
		break;
		
		case 4:
		LCD_enuWriteString("   5th Round    ");
		LCD_enuWriteString("   Last Round   ");
		_delay_ms(1000);
		break;
	}
	
	LCD_vidClearScreen();
}