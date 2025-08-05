/*
 * test.c
 *
 *  Created on: Nov 5, 2024
 *      Author: Peter
 */
#include <stdint.h>
#include<stdbool.h>
#include "test.h"
#include"gpio.h"
#include "usart.h"
#include "pingpong_functions.h"
void Test_program(void)
{
  // Test_Led();
  //Test_pingpong_program();
  // Test_pingpong_program_T();
  //Test_pingpong_program_T01 ();
	Test_pingpong_program_T02 ();//Player will serve every each round
  //Show_points(3, 2);
  //Test_buttons();
}

void Test_Led(void)
{
  int8_t Lednr;
  /* Loop checking that all leds can be turned on*/
    for (Lednr=1; Lednr<= 8; Lednr++) {
      Led_on(Lednr);
      HAL_Delay(500);
    }
    Led_on(9);  // Turn off led 8
    HAL_Delay(1000); // 1000 ms
    return;
  }

/*******************************************/
/**
@brief Led_on, turn one of the pingpong leds on

@param uint8_t Lednr , number to the Led that is turned on
       Lednr can be 1-8, all other values turns all leds off

@return void
*/
void Led_on(uint8_t Lednr)
 {
  uint8_t i;
  for (i=1; i<= 8; i++)
  {
   switch(i){
    case 1  :  // Led 1
      if (Lednr==i) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
      else HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
      break;
    case 2  :  // Led 2
      if (Lednr==i) HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
      else HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
      break;
    case 3  :  // Led 3
      if (Lednr==i) HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
      else HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
      break;
    case 4  :  // Led 4
      if (Lednr==i) HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
      else HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
      break;
    case 5  :  // Led 5
      if (Lednr==i) HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
      else HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
      break;
    case 6  :  // Led 6
      if (Lednr==i) HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
      else HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);
      break;
    case 7  :  // Led 7
      if (Lednr==i) HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
      else HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);
      break;
    case 8  :  // Led 8
      if (Lednr==i) HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
      else HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
      break;
     default :
      ;
    }  // end switch
  } // end for-loop
  return;
} // end function Led_on

/********************************************/

/**
@brief Test_buttons, check if Right button or left button is pressed
@return void
*/
void Test_buttons(void)
{
    int8_t j;

    /* Checking buttons */

    j=4;
    Led_on(j); // Light on

    while (j<9 && j>0)
    {
      if ( L_hit() == true ) // Wait for left button hit
      {
        j++;     // next led to the right
        Led_on(j); // Light on
        HAL_Delay(100); // 100 ms
        while ( L_hit() == true ); // Wait for button release
        HAL_Delay(100); // 100 ms

      }

      if ( R_hit() == true ) // Wait for right button hit
      {
        j--;     // next led to the left
        Led_on(j); // Light on
        HAL_Delay(100); // 100 ms
        while ( R_hit() == true ); // Wait for button release
        HAL_Delay(100); // 100 ms
        if (j<1) j=0; // Start again from left
      }

    }
}



/*************************************************/
/**********Test_pingpong_program*****************/
typedef enum
{
    Start,
    MoveRight,
    MoveLeft
} states;

static states State, NextState;

void Test_pingpong_program(void)
{
    bool ButtonPressed; // To remember that button is pressed
    uint32_t Varv, Speed; // Ball speed
    uint8_t Led; // LED nr
    uint8_t R_points, L_points;
    R_points=0;
    L_points=0;
    State = Start; // Initiate State to Start
    NextState = Start;
    Speed = 500000; // Initial number of loops for speed

    /* Infinite loop */
    while (1)
    {

      while(L_points<=4 || R_points <=4){
    	  if(L_points==4 || R_points ==4){
    		  Show_points(L_points,R_points);
    		  HAL_Delay(5000);
    		  Led_off();
    		  L_points=0;
    		  R_points=0;
    		  NextState = Start;
    	  }
    		  //break;
    	  State = NextState;
        switch (State) // State machine
        {
            case Start:
                Led_on(0); // Turn off all LEDs

                if (L_hit() == true) // L serve
                {
                    Led = 1;
                    NextState = MoveRight;
                    while (L_hit() == true); // wait until button is released
                }
                else if (R_hit() == true) // R serve
                {
                    Led = 8;
                    NextState = MoveLeft;
                    while (R_hit() == true); // wait until button is released
                }
                else
                {
                    NextState = Start; // Stay in Start state
                }
                break;

            case MoveRight:
            {
                Led_on(Led);
                Varv = Speed;

                while (Varv != 0)
                {
                    if (R_hit()) ButtonPressed = true; // R hit
                    Varv--;
                }

                if (ButtonPressed) // R pressed
                {
                    if (Led == 8) // and LED8 active
                    {

                        NextState = MoveLeft; // return ball
                        Led = 7;
                    }
                    else
                    {
                    	NextState = Start; // hit too early
                    }

                    // Decrease speed to increase game pace
                    if (Speed > 100000) {  // Ensure Speed doesn’t go below a safe threshold
                        Speed -= 50000;
                    }
                }
                else
                {
                    if (Led == 9) // no hit or too late
                    {
                    	Led_on_if_missed();
                    	HAL_Delay(1000);
                    	Led_off();
                    	L_points++;
                    	Show_points(L_points,R_points);
                    	HAL_Delay(1000);
                    	Led_off();
                    	NextState = Start;
                    }
                    else
                    {
                        NextState = MoveRight; // ball continues to move right
                    }
                }
                if (!ButtonPressed) Led++; // prepare to turn next LED on
                ButtonPressed = false;
            }
            break;

            case MoveLeft:
            {
                Led_on(Led);
                Varv = Speed;

                while (Varv != 0)
                {
                    if (L_hit()) ButtonPressed = true; // L hit
                    Varv--;
                }

                if (ButtonPressed) // L pressed
                {
                    if (Led == 1) // and LED1 active
                    {
                        NextState = MoveRight; // return ball
                        Led = 2;
                    }
                    else
                    {
                        NextState = Start; // hit too early
                    }

                    // Decrease speed to increase game pace
                    if (Speed > 100000) {  // Ensure Speed doesn’t go below a safe threshold
                        Speed -= 50000;
                    }
                }
                else
                {
                    if (Led == 0) // no hit or too late
                    {
                    	Led_on_if_missed();
                    	HAL_Delay(1000);
                    	Led_off();
                    	R_points++;
                        Show_points(L_points,R_points);
                        HAL_Delay(1000);
                    	Led_off();
                        NextState = Start;
                    }
                    else
                    {
                        NextState = MoveLeft; // ball continues to move left
                    }
                }
                if (!ButtonPressed) Led--; // prepare to turn next LED on
                ButtonPressed = false;
            }
            break;

            default:
                break;
        }
    }
   }
} // End of function Pingpong
/************************************************/

void Test_pingpong_program_T (void)
{
    bool ButtonPressed; // To remember that button is pressed
    uint32_t Varv, Speed; // Ball speed
    uint8_t Led; // LED nr
    uint8_t R_points, L_points;
    R_points=0;
    L_points=0;
    State = Start; // Initiate State to Start
    NextState = Start;
    Speed = 500000; // Initial number of loops for speed

    /* Infinite loop */
    while (1)
    {

      while(L_points<=4 || R_points <=4){
    	  if(L_points==4 || R_points ==4){
    		  Show_points(L_points,R_points);
    		  HAL_Delay(5000);
    		  Led_off();
    		  L_points=0;
    		  R_points=0;
    		  Speed = 500000; // Initial number of loops for speed
    		  NextState = Start;
    	  }
    		  //break;
    	  State = NextState;
        switch (State) // State machine
        {
            case Start:
                Led_on(0); // Turn off all LEDs

                if (L_hit() == true) // L serve
                {
                    Led = 1;
                    NextState = MoveRight;
                    while (L_hit() == true); // wait until button is released
                }
                else if (R_hit() == true) // R serve
                {
                    Led = 8;
                    NextState = MoveLeft;
                    while (R_hit() == true); // wait until button is released
                }
                else
                {
                    NextState = Start; // Stay in Start state
                }
                break;

            case MoveRight:
            {
                Led_on(Led);
                Varv = Speed;

                while (Varv != 0)
                {
                    if (R_hit()) ButtonPressed = true; // R hit
                    Varv--;
                }

                if (ButtonPressed) // R pressed
                {
                    if (Led == 8) // and LED8 active
                    {

                        NextState = MoveLeft; // return ball
                        Led = 7;
                    }
                    else
                    {

                    	NextState = MoveRight; // hit too early
                    }

                    // Decrease speed to increase game pace
                    if (Speed > 100000) {  // Ensure Speed doesn’t go below a safe threshold
                        Speed -= 20000;
                    }
                }
                else
                {
                    if (Led == 9) // no hit or too late
                    {
                    	Led_on_if_missed();
                    	HAL_Delay(1000);
                    	Led_off();
                    	L_points++;
                    	Show_points(L_points,R_points);
                    	HAL_Delay(1000);
                    	Led_off();
                    	NextState = Start;
                    }
                    else
                    {
                    	if(Led<8)
                        NextState = MoveRight; // ball continues to move right
                    }
                }
                if (!ButtonPressed) Led++; // prepare to turn next LED on
                ButtonPressed = false;
            }
            break;

            case MoveLeft:
            {
                Led_on(Led);
                Varv = Speed;

                while (Varv != 0)
                {
                    if (L_hit()) ButtonPressed = true; // L hit
                    Varv--;
                }

                if (ButtonPressed) // L pressed
                {
                    if (Led == 1) // and LED1 active
                    {
                        NextState = MoveRight; // return ball
                        Led = 2;
                    }
                    else
                    {
                        NextState = MoveLeft; // hit too early
                    }

                    // Decrease speed to increase game pace
                    if (Speed > 100000) {  // Ensure Speed doesn’t go below a safe threshold
                        Speed -= 20000;
                    }
                }
                else
                {
                    if (Led == 0) // no hit or too late
                    {
                    	Led_on_if_missed();
                    	HAL_Delay(1000);
                    	Led_off();
                    	R_points++;
                        Show_points(L_points,R_points);
                        HAL_Delay(1000);
                    	Led_off();
                        NextState = Start;
                    }
                    else
                    {
                    	if(Led>0)
                        NextState = MoveLeft; // ball continues to move left
                    }
                }
                if (!ButtonPressed) Led--; // prepare to turn next LED on
                ButtonPressed = false;
            }
            break;

            default:
                break;
        }
    }
   }
} // End of function Pingpong

/*************************Test_pingpong_program_T01*****************************************/
/**
******************************************************************************
@brief   Pingpong, functions for Pingpong-program
@file    tesy.c
@author  Bengt Molin
@version 1.0
@date    7-November-2024
@brief   Functions and structures for program Pingpong
******************************************************************************
*/
void Test_pingpong_program_T01 (void)
{
    bool ButtonPressed=false; // To remember that button is pressed
    uint32_t Varv, Speed; // Ball speed
    uint8_t Led; // LED nr
    uint8_t R_points, L_points;
    R_points=0;
    L_points=0;
    State = Start; // Initiate State to Start
    NextState = Start;
    Speed = 500000; // Initial number of loops for speed

    /* Infinite loop */
    while (1)
    {

      while(L_points<=4 || R_points <=4){
    	  if(L_points==4 || R_points ==4){
    		  Show_points(L_points,R_points);
    		  HAL_Delay(5000);
    		  Led_off();
    		  L_points=0;
    		  R_points=0;
    		  Speed = 500000; // Initial number of loops for speed
    		  NextState = Start;
    	  }
    		  //break;
    	  State = NextState;
        switch (State) // State machine
        {
            case Start:
                Led_on(0); // Turn off all LEDs

                if (L_hit() == true) // L serve
                {
                    Led = 1;
                    NextState = MoveRight;
                    while (L_hit() == true); // wait until button is released
                }
                else if (R_hit() == true) // R serve
                {
                    Led = 8;
                    NextState = MoveLeft;
                    while (R_hit() == true); // wait until button is released
                }
                else
                {
                    NextState = Start; // Stay in Start state
                }
                break;

            case MoveRight:
            {
                Led_on(Led);
                Varv = Speed;

                while (Varv != 0)
                {
                    if (R_hit()) ButtonPressed = true; // R hit
                    Varv--;
                }

                if (ButtonPressed) // R pressed
                {
                    if (Led == 8) // and LED8 active
                    {
	                    // Decrease speed to increase game pace
						if (Speed > 100000) {  // Ensure Speed doesn’t go below a safe threshold
							Speed -= 30000;
						}
                        NextState = MoveLeft; // return ball
                        Led = 7;
                    }
                    else
                    {

                    	Led_on_if_missed();
					    HAL_Delay(1000);
					    Led_off();
						L_points++;
						Speed=400000;
						Show_points(L_points,R_points);
					    HAL_Delay(1000);
						Led_off();
						NextState = Start;
                    	//NextState = MoveRight; // hit too early
                    }


                }
                else
                {
                    if (Led == 9) // no hit or too late
                    {
                    	Led_on_if_missed();
                    	HAL_Delay(1000);
                    	Led_off();
                    	L_points++;
                    	Speed=400000;
                    	Show_points(L_points,R_points);
                    	HAL_Delay(1000);
                    	Led_off();
                    	NextState = Start;
                    }
                    else
                    {
                    	//if(Led<8)
                        NextState = MoveRight; // ball continues to move right
                    }
                }
                if (!ButtonPressed) Led++; // prepare to turn next LED on
                ButtonPressed = false;
            }
            break;

            case MoveLeft:
            {
                Led_on(Led);
                Varv = Speed;

                while (Varv != 0)
                {
                    if (L_hit()) ButtonPressed = true; // L hit
                    Varv--;
                }

                if (ButtonPressed) // L pressed
                {
                    if (Led == 1) // and LED1 active
                    {
	                    // Decrease speed to increase game pace
						if (Speed > 100000) {  // Ensure Speed doesn’t go below a safe threshold
							Speed -= 30000;
						}
                        NextState = MoveRight; // return ball
                        Led = 2;
                    }
                    else
                    {
                    	Led_on_if_missed();
						HAL_Delay(1000);
						Led_off();
						R_points++;
						Speed=400000;
						Show_points(L_points,R_points);
						HAL_Delay(1000);
						Led_off();
						NextState = Start;
                    	//NextState = MoveLeft; // hit too early
                    }

                    // Decrease speed to increase game pace
                    if (Speed > 100000) {  // Ensure Speed doesn’t go below a safe threshold
                        Speed -= 20000;
                    }
                }
                else
                {
                    if (Led == 0) // no hit or too late
                    {
                    	Led_on_if_missed();
                    	HAL_Delay(1000);
                    	Led_off();
                    	R_points++;
                    	Speed=400000;
                        Show_points(L_points,R_points);
                        HAL_Delay(1000);
                    	Led_off();
                        NextState = Start;
                    }
                    else
                    {
                    	//if(Led>0)
                        NextState = MoveLeft; // ball continues to move left
                    }
                }
                if (!ButtonPressed) Led--; // prepare to turn next LED on
                ButtonPressed = false;
            }
            break;

            default:
                break;
        }
    }
   }
} // End of function Pingpong
/******************************************************************/
/**
******************************************************************************
@brief   Pingpong statemachine for Pingpong-program
@file    pingpong.c
@author  Mhnna Alatallah
@version 2.0
@date    09-November-2024
@brief   Functions and structures for program Pingpong
******************************************************************************
*/
void Test_pingpong_program_T02 (void)
{
    bool ButtonPressed=false; // To remember that button is pressed
    //Player's round
    bool R_player_round=false;
    bool L_player_round=false;
    uint32_t Varv, Speed; // Ball speed
    uint8_t Led; // LED nr
    uint8_t R_points, L_points;
    R_points=0;
    L_points=0;
    State = Start; // Initiate State to Start
    NextState = Start;
    Speed = 500000; // Initial number of loops for speed
    int j; //if any player pressed the button, and not his round
    /* Infinite loop */
    while (1)
    {

      while(L_points<=4 || R_points <=4){
    	  if(L_points==4 || R_points ==4){
    		  Show_points(L_points,R_points);
    		  HAL_Delay(5000);
    		  Led_off();
    		  L_points=0;
    		  R_points=0;
    		  R_player_round=false;
    		  L_player_round=false;
    		  Speed = 500000; // Initial number of loops for speed

    		  NextState = Start;
    	  }
    		  //break;
    	  State = NextState;
        switch (State) // State machine
        {
            case Start:
                Led_on(0); // Turn off all LEDs

                if (L_hit() == true) // L serve
                {
					if(L_player_round==false){
						Led = 1;
						L_player_round=true;
						R_player_round=false;
						NextState = MoveRight;
						while (L_hit() == true); // wait until button is released
					}else{
						for( j=0;j<3; j++){
							Led_on_if_missed();
						    HAL_Delay(200);
						    Led_off();
						    HAL_Delay(200);
						}
						j=0;

						NextState = Start; // Stay in Start state
					}

                }
                else if (R_hit() == true) // R serve
                {
                	if(R_player_round==false){
                		Led = 8;
						R_player_round=true;
						L_player_round=false;
						NextState = MoveLeft;
						while (R_hit() == true); // wait until button is released
                	}else{
                		for( j=0;j<3; j++){
							Led_on_if_missed();
							HAL_Delay(200);
							Led_off();
							HAL_Delay(200);
						}
						j=0;
                		NextState = Start; // Stay in Start state
                	}

                }
                else
                {
                    NextState = Start; // Stay in Start state
                }
                break;

            case MoveRight:
            {
                Led_on(Led);
                Varv = Speed;

                while (Varv != 0)
                {
                    if (R_hit()) ButtonPressed = true; // R hit
                    Varv--;
                }

                if (ButtonPressed) // R pressed
                {
                    if (Led == 8) // and LED8 active
                    {
                    	R_player_round=true; //R_hit, next round L_player
                    	L_player_round=false;
                        NextState = MoveLeft; // return ball
	                   // Decrease speed to increase game pace
					   if (Speed > 100000) {  // Ensure Speed doesn’t go below a safe threshold
						   Speed -= 20000;
					   }
                        Led = 7;
                    }
                    else
                    {
                    	R_player_round=false;//R_player missed, next round R_player
						L_player_round=true;
                    	Led_on_if_missed();
					    HAL_Delay(1000);
					    Led_off();
						L_points++;
						Speed = 400000;
						Show_points(L_points,R_points);
					    HAL_Delay(1000);
						Led_off();
						NextState = Start;
                    	//NextState = MoveRight; // hit too early
                    }


                }
                else
                {
                    if (Led == 9) // no hit or too late
                    {
                    	R_player_round=false;//R_player missed, next round R_player
						L_player_round=true;
                    	Led_on_if_missed();
                    	HAL_Delay(1000);
                    	Led_off();
                    	L_points++;
                    	Speed = 400000;
                    	Show_points(L_points,R_points);
                    	HAL_Delay(1000);
                    	Led_off();
                    	NextState = Start;
                    }
                    else
                    {
                    	//if(Led<8)
                        NextState = MoveRight; // ball continues to move right
                    }
                }
                if (!ButtonPressed) Led++; // prepare to turn next LED on
                ButtonPressed = false;
            }
            break;

            case MoveLeft:
            {
                Led_on(Led);
                Varv = Speed;

                while (Varv != 0)
                {
                    if (L_hit()) ButtonPressed = true; // L hit
                    Varv--;
                }

                if (ButtonPressed) // L pressed
                {
                    if (Led == 1) // and LED1 active
                    {
                    	R_player_round=false;
                        L_player_round=true;//L_hit, next round R_player
                        NextState = MoveRight; // return ball
	                   // Decrease speed to increase game pace
					   if (Speed > 100000) {  // Ensure Speed doesn’t go below a safe threshold
						   Speed -= 20000;
					   }
                        Led = 2;
                    }
                    else
                    {
                    	R_player_round=true;
                        L_player_round=false;//L_player missed, next round L_player
                    	Led_on_if_missed();
						HAL_Delay(1000);
						Led_off();
						R_points++;
						Speed = 400000;
						Show_points(L_points,R_points);
						HAL_Delay(1000);
						Led_off();
						NextState = Start;
                    	//NextState = MoveLeft; // hit too early
                    }


                }
                else
                {
                    if (Led == 0) // no hit or too late
                    {
                    	R_player_round=true;
                    	L_player_round=false;//L_player missed, next rounf L_player
                    	Led_on_if_missed();
                    	HAL_Delay(1000);
                    	Led_off();
                    	R_points++;
                    	Speed = 400000;
                        Show_points(L_points,R_points);
                        HAL_Delay(1000);
                    	Led_off();
                        NextState = Start;
                    }
                    else
                    {
                    	//if(Led>0)
                        NextState = MoveLeft; // ball continues to move left
                    }
                }
                if (!ButtonPressed) Led--; // prepare to turn next LED on
                ButtonPressed = false;
            }
            break;

            default:
                break;
        }
    }
   }
} // End of function Pingpong
/**************************************************************'**/


/*void Test_buttons(void)
{
    int8_t j;





    while (j<9 && j>0)
    {
      if ( L_hit() == true ) // Wait for left button hit
      {

        while ( L_hit() == true ); // Wait for button release
        HAL_Delay(100); // 100 ms

        for(j=1;j<9;j++){
        	Led_on(j);
        	HAL_Delay(100);
        }
        if(j==9)
        	j=0;
      }

      if ( R_hit() == true ) // Wait for right button hit
      {

        while ( R_hit() == true ); // Wait for button release
        HAL_Delay(100); // 100 ms
        for(j=9;j>0;j--){
        	Led_on(j);
            HAL_Delay(100);
        }
        if(j<1)
        	j=0;
      }

    }
}*/
/************************************************/

/*void Led_on(uint8_t Lednr) {
    // Arrays to store the GPIO ports and pins for each LED
    GPIO_TypeDef* ledPorts[] = {LED1_GPIO_Port, LED2_GPIO_Port, LED3_GPIO_Port, LED4_GPIO_Port,
                                LED5_GPIO_Port, LED6_GPIO_Port, LED7_GPIO_Port, LED8_GPIO_Port};
    uint16_t ledPins[] = {LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin,
                          LED5_Pin, LED6_Pin, LED7_Pin, LED8_Pin};

    // Check that the Lednr is within the valid range (1 to 8)
    if (Lednr > 0 && Lednr <= 8) {
        for (uint8_t i = 0; i < 8; i++) {
            if (Lednr == i + 1) {
                // If the current LED matches Lednr
                if (Lednr == 8) {
                    // Special handling for LED8: set and reset within this block
                    HAL_GPIO_WritePin(ledPorts[i], ledPins[i], GPIO_PIN_SET);
                    HAL_Delay(500);
                    HAL_GPIO_WritePin(ledPorts[i], ledPins[i], GPIO_PIN_RESET);
                } else {
                    // For other LEDs: set the pin and delay
                    HAL_GPIO_WritePin(ledPorts[i], ledPins[i], GPIO_PIN_SET);
                    HAL_Delay(500);
                    HAL_GPIO_WritePin(ledPorts[i], ledPins[i], GPIO_PIN_RESET);
                }
            }
        }
    }
    return;
}*/
