/*
 * Ping_Pong_Game_priv.h
 *
 * Created: 2/14/2024 9:41:31 PM
 *  Author: Mostafa Edrees
 */ 


#ifndef PING_PONG_GAME_PRIV_H_
#define PING_PONG_GAME_PRIV_H_

static void PING_PONG_GAME_vidPlayRound(void);
static void PING_PONG_vidRoundNum(void);

#define LCD_DisplayOn_CursorOff_NoBlinking			0x0C

typedef enum
{
	start,
	right,
	left
}state;



#endif /* PING_PONG_GAME_PRIV_H_ */