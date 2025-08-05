/*
 * pingpong_functions.h
 *
 *  Created on: Nov 5, 2024
 *      Author: Peter
 */

#ifndef INC_PINGPONG_FUNCTIONS_H_
#define INC_PINGPONG_FUNCTIONS_H_

#include <stdint.h>
#include<stdbool.h>

//void Led_on(uint8_t Lednr);
 void Show_points(uint8_t L_points, uint8_t R_points);
 void Led_on_if_missed(void);
 void Led_off(void);
 bool L_hit(void) ;
 bool R_hit(void);
#endif /* INC_PINGPONG_FUNCTIONS_H_ */



