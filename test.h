/*
 * test.h
 *
 *  Created on: Nov 6, 2024
 *      Author: Peter
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_
#include <stdint.h>

void Test_program(void) ;
void Test_Led(void) ;
void Led_on(uint8_t Lednr);
void Test_buttons(void);
void Test_pingpong_program(void);
void Test_pingpong_program_T(void);
void Test_pingpong_program_T01 (void);
void Test_pingpong_program_T02 (void);//Player will serve every each round
#endif /* INC_TEST_H_ */
