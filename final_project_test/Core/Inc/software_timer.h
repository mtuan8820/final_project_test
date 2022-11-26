/*
 * software_timer.h
 *
 *  Created on: Nov 26, 2022
 *      Author: legolas
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TICK 10

extern int timer1_flag;
extern int timer1_counter;

extern int timer2_flag;
extern int timer2_counter;

void setTimer1(int duration);
void timer1_run();

void setTimer2(int duration);
void timer2_run();


#endif /* INC_SOFTWARE_TIMER_H_ */
