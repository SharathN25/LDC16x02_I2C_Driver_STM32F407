/**
  ******************************************************************************************** 
  *@file   : main.c
  *@author : Sharath N
  *@brief  : Example to display Data on 16x02 LCD using I2C LCD Driver
  ********************************************************************************************
*/	
#include "stm32f4xx_hal.h"
#include "STM32F407_I2C_LCD16x02_Driver.h"

int main(void)
{
	//HAL Initialise
	HAL_Init();

   //Initialize LCD
	LCD_Init();

	LCD_Send_String("LCD on STM32F407");
	LCD_Send_Cmd(LCD_SET_ROW2_COL1);
	LCD_Send_String("Using I2C Module");	
  HAL_Delay(100);
	LCD_Display_Long_Message("This is a function to display long messages on 16x02 LCD :-)");
	while(1)
	{
   
 
	}
	
}













