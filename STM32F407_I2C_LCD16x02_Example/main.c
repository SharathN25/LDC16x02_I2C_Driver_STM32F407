/**
  ******************************************************************************************** 
  *@file   : main.c
  *@author : Sharath N
  *@brief  : Example to display Data on 16x02 LCD using I2C LCD Driver
	********************************************************************************************
*/	


#include "stdio.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "STM32F407_I2C_LCD16x02_Driver.h"

void GPIO_Config(void); 
void I2C_Config(void);
void Systick_Interrupt_Enable(void);

/* !!! Make sure that I2C_HandleTypedef has same name in both in "STM32F407_I2C_LCD16x02_Driver.c" 
and here !!! */
I2C_HandleTypeDef myI2Chandle;


int main(void)
{
	//HAL Initialise
	HAL_Init();
	
	//Enable Systick interrupt for delay
	Systick_Interrupt_Enable();

	//Configure GPIOs
	GPIO_Config();
	
	//Configure I2C
	I2C_Config();

  //Initialize LCD
	LCD_Init();

	LCD_Send_String("LCD on STM32F407");
	LCD_Send_Cmd(LCD_SET_ROW2_COL1);
	LCD_Send_String("Using I2C Module");
	
	while(1)
	{
   
 
	}
	
}




/* Configure GPIOs */
void GPIO_Config(void)
{
	//Enable Ports clocks
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	//Init tyoeDef
	GPIO_InitTypeDef myPinInit;
	//LED pins config
	myPinInit.Pin = GPIO_PIN_12;
	myPinInit.Mode = GPIO_MODE_OUTPUT_PP;
	myPinInit.Pull = GPIO_NOPULL;
	myPinInit.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &myPinInit);
	//I2C pins config
	myPinInit.Pin = GPIO_PIN_6 |GPIO_PIN_7;
	myPinInit.Mode = GPIO_MODE_AF_OD;
	myPinInit.Pull = GPIO_PULLUP;
	myPinInit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	myPinInit.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &myPinInit);
	
}



/*Configure I2C Peripheral */
void I2C_Config(void)
{
	//Enable I2C peripheral clock
	__HAL_RCC_I2C1_CLK_ENABLE();
	
	myI2Chandle.Instance = I2C1;
	myI2Chandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	myI2Chandle.Init.ClockSpeed = 100000;
	myI2Chandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	myI2Chandle.Init.DutyCycle = I2C_DUTYCYCLE_2;
	myI2Chandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	myI2Chandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
	myI2Chandle.Init.OwnAddress1 = 0;
	myI2Chandle.Init.OwnAddress2 = 0;
	HAL_I2C_Init(&myI2Chandle);
}



void Systick_Interrupt_Enable(void)
{
	//Systick interrupt enable for HAL_Delay function
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}



/*Systick Handler*/
void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}
