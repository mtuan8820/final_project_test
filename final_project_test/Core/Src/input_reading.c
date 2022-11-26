/*
 * input_reading.c
 *
 *  Created on: Nov 26, 2022
 *      Author: legolas
 */


#include "input_reading.h"
#include "math.h"
#include "main.h"

int button_flag[NO_OF_BUTTONS]={0};
int KeyReg0[NO_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg1[NO_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg2[NO_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg3[NO_OF_BUTTONS] = {NORMAL_STATE};
int FlagFor3secPressed[NO_OF_BUTTONS] = {0};
int TimeForKeyPress = 300;

int is_button_pressed(int index){
	if(button_flag[index]==1){
		button_flag[index]=0;
		return 1;
	}
	return 0;
}

void input_reading(){
for(int i=0;i<3;i++){
	KeyReg0[i]=KeyReg1[i];
	KeyReg1[i]=KeyReg2[i];
	//sua lai ham readpin
	KeyReg2[i]=HAL_GPIO_ReadPin(GPIOA, Button1_Pin*pow(2,i));
	if((KeyReg0[i]==KeyReg1[i])&&(KeyReg1[i]==KeyReg2[i])){
		if(KeyReg3[i]!=KeyReg2[i]){
			KeyReg3[i]=KeyReg2[i];
			if(KeyReg2[i]==PRESSED_STATE){
				button_flag[i]=1;

				//after 3 sec button change to pressed_more_than_3sec_state
				TimeForKeyPress=300;
				}
		}else{
			TimeForKeyPress--;
			if(TimeForKeyPress==0) {
				//pressed_more_than_3sec_state
			    //PressedKeyProcess(index);
				if(KeyReg2[i]==PRESSED_STATE) //TODO
				TimeForKeyPress=100;
				}
			}
	}//end if
}//end for

}
