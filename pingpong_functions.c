/*
 * pingpong_functions.c
 *
 *  Created on: Nov 5, 2024
 *      Author: Peter
 */


#include"gpio.h"
#include "usart.h"
#include <stdint.h>
#include<stdbool.h>
#include "pingpong_functions.h"

/**
@brief Show_points, shows points after missed ball
@param1  uint8_t L_points points for left player
@param2  uint8_t R_points points for right player
@return void, no return value
*/
void Show_points(uint8_t L_points, uint8_t R_points){
	uint8_t i,j;
	for( i=0; i<=L_points;i++){

		  switch(i){
		  		case 1:
		  			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		  			break;
		  		case 2:
		  			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
		  			break;
		  		case 3:
		  			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
		  			break;
		  		case 4:
		  			HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
		  			break;
		  		default :
		  		      ;
		  }
	  }
	for( j=0; j<=R_points;j++){

			switch(j){
				case 1:
					HAL_GPIO_WritePin(LED7_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
					break;
				case 2:
					HAL_GPIO_WritePin(LED8_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
					break;
				case 3:
					HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
				    break;
				case 4:
					HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
					break;
				default :
				      ;
			}
	}
}

/**
@brief  Led_on_if_missed, blink all LEDs after missed ball in (0,1)s
@return void, no return value
*/
void Led_on_if_missed(void) {
    // Arrays to store the GPIO ports and pins for each LED
    GPIO_TypeDef* ledPorts[] = {LED1_GPIO_Port, LED2_GPIO_Port, LED3_GPIO_Port, LED4_GPIO_Port,
                                LED5_GPIO_Port, LED6_GPIO_Port, LED7_GPIO_Port, LED8_GPIO_Port};
    uint16_t ledPins[] = {LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin,
                          LED5_Pin, LED6_Pin, LED7_Pin, LED8_Pin};

    // Check that the Lednr is within the valid range (1 to 8)

        for (uint8_t i = 0; i < 8; i++) {
            // Set the specific LED if it matches Lednr, otherwise reset it
            HAL_GPIO_WritePin(ledPorts[i], ledPins[i], GPIO_PIN_SET );
        }

}

/**
@brief  Led_off, Reset all LEDs
@return void, no return value
*/

void Led_off(void) {
    // Arrays to store the GPIO ports and pins for each LED
    GPIO_TypeDef* ledPorts[] = {LED1_GPIO_Port, LED2_GPIO_Port, LED3_GPIO_Port, LED4_GPIO_Port,
                                LED5_GPIO_Port, LED6_GPIO_Port, LED7_GPIO_Port, LED8_GPIO_Port};
    uint16_t ledPins[] = {LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin,
                          LED5_Pin, LED6_Pin, LED7_Pin, LED8_Pin};

    // Check that the Lednr is within the valid range (1 to 8)

        for (uint8_t i = 0; i < 8; i++) {
            // Set the specific LED if it matches Lednr, otherwise reset it
            HAL_GPIO_WritePin(ledPorts[i], ledPins[i], GPIO_PIN_RESET );
        }

}

/**************************************/
/**
@brief L_hit, check if L button is pressed
@param void
@return bool, true if L button pushed, false otherwise
*/


bool L_hit(void)
{  if (HAL_GPIO_ReadPin(L_button_GPIO_Port, L_button_Pin) == 0) return true;
    else return  false;
  }

/**
@brief R_hit, check if R button is pressed
@param void
@return bool, true if R button pushed, false otherwise
*/

bool R_hit(void)
{  if (HAL_GPIO_ReadPin(R_button_GPIO_Port, R_button_Pin) == 0) return true;
    else return  false;
  }














/*void Led_on(uint8_t Lednr)
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
}*/    // end function Led_on
