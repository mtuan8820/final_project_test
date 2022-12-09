/*
 * global.h
 *
 *  Created on: Nov 26, 2022
 *      Author: legolas
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
//fsm traffic light state
#define INIT 			0
#define AUTO_RED		1
#define AUTO_GREEN		2
#define AUTO_YELLOW		3
#define SETTING_RED		4
#define SETTING_GREEN	5
#define SETTING_YELLOW	6
#define MANUAL			7
//pedestrian light fsm
#define NONE			10
#define RED				11
#define GREEN			12
//system duration define
extern int red_duration;
extern int green_duration;
extern int yellow_duration;
//others
extern int counter1;//used for traffic light 1
extern int counter2;//used for traffic light 2
extern int state;
extern int manual_state;
extern int pedes_state;
#endif /* INC_GLOBAL_H_ */
