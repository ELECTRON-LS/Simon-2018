/*
 * lcd.h
 *
 *  Created on: Apr 5, 2014
 *      Author: Marcelo
 */

#ifndef LCD_H_
#define LCD_H_

#define LCD_OK		0
#define LCD_ERR		1

unsigned char LCD_WriteBuffer(unsigned char *origen);
unsigned char LCD_WriteChar(unsigned char dato);
unsigned char LCD_SetCurPos(unsigned char pos);
unsigned char LCD_Clear(void);
unsigned char LCD_Init(void);
void LCD_Tic(void);

#endif /* LCD_H_ */
