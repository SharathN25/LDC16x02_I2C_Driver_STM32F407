/**
  ******************************************************************************************** 
  *@file   : STM32F407_I2C_LCD16x02_Driver.c
  *@author : Sharath N
  *@brief  : LCD driver source file for interfacing 16x02 LCD on STM32Fxx MCU using I2C Serial 
	           Interface Module
	********************************************************************************************
*/	

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "STM32F407_I2C_LCD16x02_Driver.h"

/* !!! Make sure that I2C_HandleTypedef has same name in both in "main.c" and here !!! */
extern I2C_HandleTypeDef myI2Chandle;


/**
 * @brief Send Command to LCD
 * @param cmd : LCD commands 
 * @retval None
 */
void LCD_Send_Cmd(uint8_t cmd)
{
	uint8_t data_u, data_l;
	uint8_t data_u_tx[2], data_l_tx[2];

	/*Store upper nibble*/
	data_u = (cmd & 0xF0);

	/*Store lower nibble*/
	data_l = ((cmd << 4) & 0xF0);

	/* Construct upper byte-> compatible for LCD*/
	data_u_tx[0] = data_u|BACKLIGHT|PIN_EN;
	data_u_tx[1] = data_u|BACKLIGHT;
	
	/* Construct lower byte-> compatible for LCD*/
	data_l_tx[0] = data_l|BACKLIGHT|PIN_EN;
	data_l_tx[1] = data_l|BACKLIGHT;

	/* Transmit upper nibble using I2C APIs*/
	if(HAL_I2C_IsDeviceReady(& myI2Chandle, I2C_SLAVE_ADDRESS, 1, 10) == HAL_OK)
		HAL_I2C_Master_Transmit(& myI2Chandle,I2C_SLAVE_ADDRESS, data_u_tx, 2, 100); 
	
	/*Provide a delay */
	HAL_Delay(5);

	/* Transmit lower nibble using I2C APIs*/
	if(HAL_I2C_IsDeviceReady(& myI2Chandle, I2C_SLAVE_ADDRESS, 1, 10) == HAL_OK)
		HAL_I2C_Master_Transmit(& myI2Chandle,I2C_SLAVE_ADDRESS, data_l_tx, 2, 100);	
	HAL_Delay(5);
}




/**
 * @brief Send Data to LCD
 * @param data: Data to be sent to LCD
 * @retval None
 */
void LCD_Send_Data(uint8_t data)
{
	uint8_t data_u, data_l;
	uint8_t data_u_tx[2], data_l_tx[2];

	/*Store upper nibble*/
	data_u = (data & 0xF0);

	/*Store lower nibble*/
	data_l = ((data << 4) & 0xF0);

	/* Construct upper byte-> compatible for LCD*/
	data_u_tx[0] = data_u|BACKLIGHT|PIN_EN|PIN_RS;
	data_u_tx[1] = data_u|BACKLIGHT|PIN_RS;
	
	/* Construct lower byte-> compatible for LCD*/
	data_l_tx[0] = data_l|BACKLIGHT|PIN_EN|PIN_RS;
	data_l_tx[1] = data_l|BACKLIGHT|PIN_RS;

	/* Transmit upper nibble using I2C APIs*/
	if(HAL_I2C_IsDeviceReady(& myI2Chandle, I2C_SLAVE_ADDRESS, 1, 10) == HAL_OK)
		HAL_I2C_Master_Transmit(& myI2Chandle,I2C_SLAVE_ADDRESS, data_u_tx, 2, 100); 
	
	/*Provide a delay */
	//HAL_Delay(1);

	/* Transmit lower nibble using I2C APIs*/
	if(HAL_I2C_IsDeviceReady(& myI2Chandle, I2C_SLAVE_ADDRESS, 1, 10) == HAL_OK)
		HAL_I2C_Master_Transmit(& myI2Chandle,I2C_SLAVE_ADDRESS, data_l_tx, 2, 100);	
  HAL_Delay(5);
}



/**
 * @brief  Initializes LCD
 * @retval None
 */
void LCD_Init(void)
{
	/* Wait for 15ms */
	HAL_Delay(15);
	
	/*Function Set - As per HD44780U*/
	LCD_Send_Cmd(LCD_FUNCTION_SET1);
	
	/*Function Set -As per HD44780U*/
	LCD_Send_Cmd(LCD_FUNCTION_SET2);
	
	/*Set 4bit mode and 2 lines */
	LCD_Send_Cmd(LCD_4BIT_2LINE_MODE);
	
	/*Display on, cursor off*/
	LCD_Send_Cmd(0x0C);
	
	/* SET Row1 and Col1 (1st Line) */
	LCD_Send_Cmd(0x80);
	
	/*Clear Display*/
	LCD_Send_Cmd(LCD_CLEAR_DISPLAY);
	
}



/**
 * @brief Send Strings to LCD
 * @param str: pointer to strings
 * @retval None
 */
void LCD_Send_String(char *str)
{
	while (*str)  
	{
		LCD_Send_Data(*str++);
	}
}





