# PING PONG GAME 🏓🏓

## Overview
This project implements a Ping-Pong game using an LCD and external interrupt. 
Players control their respective paddles using buttons, aiming to keep the ball in play. 
The game consists of 5 rounds, and scores are displayed on dedicated Seven Segment displays.

## Algorithm
- Ball Movement: Display a ball moving horizontally on the LCD screen from one end to the other.
- Player Controls: Two players interact with the game, each represented by a button acting as their ping pong racket.
- External Interrupt: Use external interrupts to detect button presses, indicating player actions.
- Gameplay Logic:
    - If a player presses their button, the ball bounces to the other side.
    - If the ball reaches one side without being bounced, the opposing player wins the round.
- Round System: The game consists of 5 rounds, providing multiple opportunities for players to score.
- Score Display: Each player's score is tracked and displayed on their respective Seven Segment display, allowing players to easily keep track of their progress.

## Simulation On Proteus:
![gitHub](https://github.com/MostafaEdrees11/PING_PONG_GAME/blob/master/Proteus/PING%20PONG.gif)

