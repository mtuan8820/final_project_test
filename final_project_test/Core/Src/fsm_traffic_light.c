/*
 * fsm_traffic_light.c
 *
 *  Created on: Nov 26, 2022
 *      Author: legolas
 */


#include "fsm_traffic_light.h"
#include "global.h"
#include "scheduler.h"
#include "hardware_layer.h"
#include "input_reading.h"
#include "software_timer.h"
#include "stdio.h"
#include "main.h"
#include "stdint.h"
char str[50];
void fsm(){
	switch(state){
	case AUTO_RED:
		//reset flag for setting button and manual button
		is_button_pressed(SETTING_IDX);
		is_button_pressed(MANUAL_IDX);
		//hien thi mau do tren den giao thong 1
		set_color_light1(1);
		//dem lui moi 1s
		if(timer1_flag==1){
			counter1--;
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"red=%d\r\n"
								  		,counter1),1000) ;
			setTimer1(1000);
		}
		//neu counter1 == 0 chuyen trang thai sang auto_green
		if (counter1<=0) {
			counter1=green_duration;//nap lai thoi gian cho duration
			state=AUTO_GREEN;
		}//nguoc lai van o trang thai auto_red

		//neu an nut 1 thi chuyen sang trang thai setting
		if (is_button_pressed(0))
			{
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"setting_red=%d\r\n"
										,red_duration),1000);
			state=SETTING_RED;
			}
		break;
	case AUTO_GREEN:
		//reset flag for setting button and manual button
		is_button_pressed(SETTING_IDX);
		is_button_pressed(MANUAL_IDX);
		//hien thi mau xanh tren den giao thong 1
		set_color_light1(2);
		//gui tin hieu uart de hien thi thoi gian
			//can bo sung them ham trong hardware_layer
		//dem lui moi 1s
		if(timer1_flag==1){
			counter1--;
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"green=%d\r\n"
											  		,counter1),1000) ;
			setTimer1(1000);
		}
		//neu counter1 == 0 chuyen trang thai sang auto_yellow
		if (counter1==0) {
			counter1=yellow_duration;//nap lai thoi gian cho duration
			state=AUTO_YELLOW;
		}//nguoc lai van o trang thai auto_green

		//neu an nut 1 thi chuyen sang trang thai setting_red
		if (is_button_pressed(0))
		{
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"setting_red=%d\r\n"
										,red_duration),1000);
			state=SETTING_RED;
		}
		break;
	case AUTO_YELLOW:
		//reset flag for setting button and manual button
		is_button_pressed(SETTING_IDX);
		is_button_pressed(MANUAL_IDX);
		//hien thi mau xanh tren den giao thong 1
		set_color_light1(3);
		//gui tin hieu uart de hien thi thoi gian
			//can bo sung them ham trong hardware_layer
		//dem lui moi 1s
		if(timer1_flag==1){
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"yellow=%d\r\n"
														  		,counter1),1000) ;
			counter1--;
			setTimer1(1000);
		}
		//neu counter1 == 0 chuyen trang thai sang auto_red
		if (counter1==0) {
			counter1=red_duration;//nap lai thoi gian cho duration
			state=AUTO_RED;
		}//nguoc lai van o trang thai auto_yellow

		//neu an nut 1 thi chuyen sang trang thai setting_red
		if (is_button_pressed(0))
		{
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"setting_red=%d\r\n"
							,red_duration),1000) ;
			state=SETTING_RED;

		}
		break;
	case SETTING_RED:
		//reset flag for manual button
		is_button_pressed(MANUAL_IDX);
		//hien thi mau do tren den giao thong 1
		set_color_light1(1);
		//neu an nut 2 thi se tang red_duration
		if(is_button_pressed(1)){
			red_duration++;
			if(red_duration>=10) red_duration=1;
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"setting_red=%d\r\n"
							,red_duration),1000) ;

		}
		//gui tin hieu uart de hien thi thoi gian
					//can bo sung them ham trong hardware_layer

		//neu an nut 1 thi chuyen sang trang thai setting_green
		if (is_button_pressed(0)){
			state=SETTING_GREEN;
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"setting_green=%d\r\n"
										,green_duration),1000) ;
			}
		break;
	case SETTING_GREEN:
		//reset flag for manual button
		is_button_pressed(MANUAL_IDX);
		//hien thi mau xanh tren den giao thong 1
		set_color_light1(2);
		//neu an nut 2 thi se tang red_duration
		if(is_button_pressed(1)){
			green_duration++;
			if(green_duration>=10) green_duration=1;
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"setting_green=%d\r\n"
							,green_duration),1000) ;

		}
		//gui tin hieu uart de hien thi thoi gian
					//can bo sung them ham trong hardware_layer

		//neu an nut 1 thi chuyen sang trang thai setting_yellow
		if (is_button_pressed(0)){
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"setting_yellow=%d\r\n"
										,yellow_duration),1000) ;
			state=SETTING_YELLOW;
			}
		break;
	case SETTING_YELLOW:
		//reset flag for manual button
		is_button_pressed(MANUAL_IDX);
		//hien thi mau vang tren den giao thong 1
		set_color_light1(3);
		//neu an nut 2 thi se tang red_duration
		if(is_button_pressed(1)){
			yellow_duration++;
			if(yellow_duration>=10) yellow_duration=1;
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"setting_yellow=%d\r\n"
							,yellow_duration),1000) ;

		}
		//gui tin hieu uart de hien thi thoi gian
					//can bo sung them ham trong hardware_layer

		//neu an nut 1 thi chuyen sang trang thai manual
		if (is_button_pressed(0)){
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"manual\r\n"
										),1000) ;
			state=MANUAL;
			}
		break;
	case MANUAL:
		//reset flag for setting reset button
		is_button_pressed(SETTING_IDX);
		set_color_light1(manual_state);
		if (is_button_pressed(MANUAL_IDX)) manual_state++;
		if (manual_state>3) manual_state=1;
		else if (is_button_pressed(0)){
			HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"auto_red=%d\r\n",
										red_duration),1000) ;
			counter1=red_duration;
			state=AUTO_RED;
		}
		is_button_pressed(SETTING_IDX);

		break;
	default:
		break;
	}
}

void pedestrian_fsm(){
	switch (pedes_state){
	case NONE:
		set_color_pedestrian_light(0);
		if(is_button_pressed(3)){
			if(
				(state==AUTO_RED&&counter1>=3)||
			     state==SETTING_RED||
			   ((state==MANUAL)&&(manual_state==1||manual_state==3))
			) pedes_state = GREEN;
			else pedes_state=RED;
		}
		break;
	case GREEN:
		set_color_pedestrian_light(2);
		if(
			(state==AUTO_GREEN)||
			(state==SETTING_GREEN)||
			(state==MANUAL&&manual_state==2)
		) pedes_state=NONE;
		//PWM
		//__HAL_TIM_SetCompare (&htim3,TIM_CHANNEL_1, counter1/red_duration*100);
		break;
	case RED:
		set_color_pedestrian_light(1);
		if(
			(state==AUTO_RED&&counter1>=3)
			||state==SETTING_RED
			||((state==MANUAL)&&(manual_state==1||manual_state==3))
		) pedes_state = GREEN;

		break;
	default:
		break;
	}
}
