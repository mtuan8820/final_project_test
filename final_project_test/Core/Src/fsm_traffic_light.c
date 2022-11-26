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
void auto_red(){
	//hien thi mau do tren den giao thong 1
	set_color_light1(1);
	//gui tin hieu uart de hien thi thoi gian
		//can bo sung them ham trong hardware_layer
//	HAL_UART_Transmit(&huart2 ,(void*)str,sprintf(str,"!red=%d#\n"
//		  		,counter1),1000) ;
	//neu counter1 == 0 chuyen trang thai sang auto_green
	if (counter1<=0) {
		counter1=green_duration;//nap lai thoi gian cho duration
		SCH_Add_Task(auto_green,0,1);
	}//nguoc lai van o trang thai auto_red
	else{

		SCH_Add_Task(auto_red,0,1);
	}
	//dem lui moi 1s
	if(timer1_flag==1){
		counter1--;
		setTimer1(1000);
	}
	//neu an nut 1 thi chuyen sang trang thai setting
	if (is_button_pressed(1))
	{
		SCH_Add_Task(setting_red,0,1);
	}
}

void auto_green(){
		//hien thi mau xanh tren den giao thong 1
		set_color_light1(2);
		//gui tin hieu uart de hien thi thoi gian
			//can bo sung them ham trong hardware_layer

		//neu counter1 == 0 chuyen trang thai sang auto_yellow
		if (counter1==0) {
			counter1=yellow_duration;//nap lai thoi gian cho duration
			SCH_Add_Task(auto_yellow,0,1);
		}//nguoc lai van o trang thai auto_green
		else{
			counter1--;
			SCH_Add_Task(auto_green,0,1);
		}
		//neu an nut 1 thi chuyen sang trang thai setting_red
		if (is_button_pressed(1))
		{
			SCH_Add_Task(setting_red,0,1);
		}
}

void auto_yellow(){
		//hien thi mau xanh tren den giao thong 1
		set_color_light1(3);
		//gui tin hieu uart de hien thi thoi gian
			//can bo sung them ham trong hardware_layer

		//neu counter1 == 0 chuyen trang thai sang auto_red
		if (counter1==0) {
			counter1=red_duration;//nap lai thoi gian cho duration
			SCH_Add_Task(auto_red,0,1);
		}//nguoc lai van o trang thai auto_yellow
		else{
			counter1--;
			SCH_Add_Task(auto_yellow,0,1);
		}
		//neu an nut 1 thi chuyen sang trang thai setting_red
		if (is_button_pressed(1))
		{
			SCH_Add_Task(setting_red,0,1);
		}
}

void setting_red(){
	//hien thi mau do tren den giao thong 1
	set_color_light1(1);

	//neu an nut 2 thi se tang red_duration
	if(is_button_pressed(2)){
		red_duration++;
		if(red_duration>=10) red_duration=0;
	}
	//gui tin hieu uart de hien thi thoi gian
				//can bo sung them ham trong hardware_layer

	//neu an nut 1 thi chuyen sang trang thai setting_green
	if (is_button_pressed(1)){
		SCH_Add_Task(setting_green,0,1);
		}
	else {//khong nhan nut 1 thi van o lai trang thai setting_red
		SCH_Add_Task(setting_red,0,1);
	}
}

void setting_green(){

}
