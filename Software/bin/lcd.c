/*
 * lcd.c
 *
 *  Created on: Apr 5, 2014
 *      Author: Marcelo
 */

#include "includes.h"

#define RS			PTCD_PTCD3
#define RW			PTCD_PTCD2
#define E			PTCD_PTCD1

#define LCD0		PTBD_PTBD4
#define LCD1		PTBD_PTBD5
#define LCD2		PTBD_PTBD6
#define LCD3		PTBD_PTBD7
#define PINBUSY		PTBD_PTBD7
#define LCDBUS(x)	PTBD = (PTBD & 0x0F);PTBD = (PTBD | x)
#define LCDDIR		PTBDD
#define LCDOUT()	LCDDIR = (LCDDIR | 0xF0)
#define LCDIN()		LCDDIR = (LCDDIR & 0x0F)
#define	LCDHIGH(x) 	(x & 0xF0)
#define	LCDLOW(x) 	((x & 0x0F)<<4)

volatile unsigned short lcd_tout;

unsigned char LCD_ReadBusy(void);
void LCD_WriteData(unsigned char dato);
void LCD_WriteCmd(unsigned char dato);
void LCD_WriteByte(unsigned char dato);

unsigned char LCD_WriteBuffer(unsigned char *origen){
	while (*origen != '\0'){
		if(LCD_WriteChar(*origen)!=LCD_OK) return LCD_ERR;
		origen++;
	}
	return LCD_OK;
}

unsigned char LCD_WriteChar(unsigned char dato){
	LCD_WriteData(dato);
	if(LCD_ReadBusy()!=LCD_OK) return LCD_ERR;
	return LCD_OK;
}

unsigned char LCD_SetCurPos(unsigned char pos){
	pos |= 0x80;
	LCD_WriteCmd(pos);
	if(LCD_ReadBusy()!=LCD_OK) return LCD_ERR;
	return LCD_OK;
}

unsigned char LCD_Clear(void){
	LCD_WriteCmd(0x01);
	if(LCD_ReadBusy()!=LCD_OK) return LCD_ERR;
	return LCD_OK;
}

unsigned char LCD_ReadBusy(void){
	unsigned char busy=1;

	LCDIN();				// Bus como entrada
	RS = 0;
	RW = 1;
	lcd_tout = 100;
	do{
		E = 1;
		busy = PINBUSY;
		E = 0;
		E = 1;
		(void)PINBUSY;
		E = 0;
		if(!lcd_tout) return LCD_ERR;
	}while(busy);
	RW = 0;
	LCDBUS(0);
	LCDOUT();
	__RESET_WATCHDOG();
	return LCD_OK;
}

void LCD_WriteData(unsigned char dato){
	RS = 1;
	RW = 0;
	LCD_WriteByte(dato);
	RS = 0;
}

void LCD_WriteCmd(unsigned char dato){
	RS = 0;
	RW = 0;
	LCD_WriteByte(dato);
}

void LCD_WriteByte(unsigned char dato){
	LCDBUS(0);
	E = 1;
	LCDBUS(LCDHIGH(dato));
	E = 0;
	LCDBUS(0);
	E = 1;
	LCDBUS(LCDLOW(dato));
	E = 0;
	LCDBUS(0);
}

unsigned char LCD_Init(void){
	lcd_tout = 50;
	while(lcd_tout) __RESET_WATCHDOG();
	LCD_WriteCmd(0x30);	//Function set (8 bits)
	lcd_tout = 5;
	while(lcd_tout);
	LCD_WriteCmd(0x30);	//Function set (8 bits)
	lcd_tout = 1;
	while(lcd_tout);
	LCD_WriteCmd(0x30);	//Function set (8 bits)
	lcd_tout = 1;
	while(lcd_tout);
	LCD_WriteCmd(0x20);	//Function set (4 bit)
	lcd_tout = 1;
	while(lcd_tout);
	LCD_WriteCmd(0x28);	//2 lineas, 5x8 caracter
	lcd_tout = 1;
	while(lcd_tout);
	LCD_WriteCmd(0x0C);	//Display ON, cursor y blinking OFF
	lcd_tout = 1;
	while(lcd_tout);
	LCD_WriteCmd(0x01);	//Clear display
	lcd_tout = 20;
	while(lcd_tout);
	LCD_WriteCmd(0x06);	//Autoincremento a izquierda
	if(LCD_ReadBusy()!=LCD_OK) return LCD_ERR;
	return LCD_OK;
}

void LCD_Tic(void){
	if (lcd_tout) lcd_tout--;
}
