/*Simon.h
 * Definiciones para el juego de Simon
 * Proyecto Integrador 2018
 */


#ifndef _SIMON_H
#define _SIMON_H

#include "derivative.h"

#pragma MESSAGE DISABLE C1106

#define MAX_STEPS 20             //Máxima cantidad de pasos de la secuencia

/*Sonidos para los pulsadores*/
#define SILENCIO       0
#define NOTA_ROJO      12500     //Sonido del color Rojo  200Hz
#define NOTA_VERDE     10000     //Sonido del color Verde 300Hz
#define NOTA_AZUL      7500      //Sonido del color Azul  400Hz
#define NOTA_AMARILLO  5000      //Sonido del color Amarillo 500Hz
#define NOTA_ERROR     25000     //Sonido de error 50Hz
#define PuertoSalida    PTD
#define PuertoEntrada   PTA
#define ROJO            1
#define VERDE           2
#define AZUL            4
#define AMARILLO        8
#define APAGADO         0
#define PRESIONADO      15

/* Musica */
#define Tempo   50               

#define C	      9556      //Do   261.63 Hz
#define Db 	    9019      //Do#  277.18 Hz
#define D 	    8513      //Re   293.66 Hz
#define Eb 	    8035      //Re#  311.13 Hz
#define E	      7584      //Mi   329.63 Hz
#define F	      7159      //Fa   349.23 Hz
#define Gb 	    6757      //Fa#  369.99 Hz
#define G	      6378      //Sol  392.00 Hz
#define Ab 	    6020      //Sol# 415.30 Hz
#define A	      5682      //La   440.00 Hz
#define Bb 	    5363      //La#  466.16 Hz
#define B	      5062      //Si   493.88 Hz


#define C0	   1
#define Db0 	 2
#define D0 	   3
#define Eb0    4
#define E0     5
#define F0     6
#define Gb0    7
#define G0     8
#define Ab0    9
#define A0     10
#define Bb0    11
#define B0     12

#define C1	   13
#define Db1 	 14
#define D1 	   15
#define Eb1    16
#define E1     17
#define F1     18
#define Gb1    19
#define G1     20
#define Ab1    21
#define A1     22
#define Bb1    23
#define B1     24

#define C2	   25
#define Db2 	 26
#define D2 	   27
#define Eb2    28
#define E2     29
#define F2     30
#define Gb2    31
#define G2     32
#define Ab2    33
#define A2     34
#define Bb2    35
#define B2     36


typedef struct{
  byte nota;
  byte temp;
} RINGTONE;

const RINGTONE Cuca[];
const RINGTONE Hava[];
/*Puerto de Entrada*/
typedef union {
  struct {
    byte Rojo        :1;                                       /* Boton Rojo */
    byte Verde       :1;                                       /* Boton Verde */
    byte Azul        :1;                                       /* Boton Azul */
    byte Amarillo    :1;                                       /* Boton Amarillo*/
    byte             :1;                                       
    byte             :1;                                       
    byte             :1;                                       
    byte             :1;                                       
  } Bits;
  struct {
    byte grpBotones :4;
    byte            :1;
    byte            :1;
    byte            :1;
    byte            :1;
  } MergedBits;
} PENT;

extern volatile PENT _Botones @0x00000000;

#define BtnRojo      _Botones.Bits.Rojo
#define BtnVerde     _Botones.Bits.Verde
#define BtnAzul      _Botones.Bits.Azul
#define BtnAmarilla  _Botones.Bits.Amarilla
#define Botones      _Botones.MergedBits.grpBotones

/*
extern volatile PENT _Botones @0x00000000;
#define BotonRojo      _Botones.Bits.Rojo
#define BotonVerde     _Botones.Bits.Verde
#define BotonAzul      _Botones.Bits.Azul
#define BotonAmarillo  _Botones.Bits.Amarillo
#define Botones        _Botones.MergedBits.grpBtn
*/

/*Puerto de salida*/
typedef union {
  struct {
    byte Rojo        :1;                                       /* Luz Roja */
    byte Verde       :1;                                       /* Luz Verde */
    byte Azul        :1;                                       /* Luz Azul */
    byte Amarillo    :1;                                       /* Luz Amarilla*/
    byte             :1;                                       
    byte             :1;                                       
    byte             :1;                                       
    byte             :1;                                       
  } Bits;
  struct {
    byte grpLuces   :4;
    byte            :1;
    byte            :1;
    byte            :1;
    byte            :1;
  } MergedBits;
} PSAL;

extern volatile PSAL _Luces @0x00000003;

#define LuzRoja      _Luces.Bits.Rojo
#define LuzVerde     _Luces.Bits.Verde
#define LuzAzul      _Luces.Bits.Azul
#define LuzAmarilla  _Luces.Bits.Amarilla
#define Luces        _Luces.MergedBits.grpLuces

typedef struct{
  byte  t0  :1;
  byte  t1  :1;
  byte  t2  :1;
  byte  t3  :1;
  byte  t4  :1;
  byte  t5  :1;
  byte  t6  :1;
  byte  t7  :1;
} TIMFLAGS;

extern volatile TIMFLAGS _timflags;

#define T0F _timflags.t0
#define T1F _timflags.t1
#define T2F _timflags.t2
#define T3F _timflags.t3
#define T4F _timflags.t4
#define T5F _timflags.t5
#define T6F _timflags.t5
#define T7F _timflags.t7
 
  



typedef union {
  struct {
    byte LR          :1;                                       /* Luz Roja */
    byte LG          :1;                                       /* Luz Verde */
    byte LB          :1;                                       /* Luz Azul */
    byte LY          :1;                                       /* Luz Amarilla*/
    byte BR          :1;                                       /* Boton Rojo*/
    byte BG          :1;                                       /* Boton Verde*/
    byte BB          :1;                                       /* Boton Azul*/
    byte BY          :1;                                       /* Boton Amarillo*/
  } Bits;
  struct {
    byte grpLuces   :4;                                        //Luces
    byte grpBotones :4;                                        //Botones
  } MergedBits;  
} FLAGS;

extern volatile FLAGS _flags;

#define flgLuzRoja        _flags.Bits.LR
#define flgLuzVerde       _flags.Bits.LG
#define flgLuzAzul        _flags.Bits.LB
#define flgLuzAmarilla    _flags.Bits.LY
#define flgBtnRojo        _flags.Bits.BR
#define flgBtnVerde       _flags.Bits.BG
#define flgBtnAzul        _flags.Bits.BB
#define flgBtnAmarillo    _flags.Bits.BY
 
#define flgLuces          _flags.MergedBits.grpLuces
#define flgBotones        _flags.MergedBits.grpBotones


/*Variables globales*/ 

extern volatile word Timer;
extern volatile byte tDelay;
extern volatile byte Pasos[MAX_STEPS+1];




/*Prototipos de funciones*/
void AgregarPaso(void);             //Agrega un paso mas a la secuencia
byte Aleatorio(void);               //Genera un numero aleatorio entre 0 y 3
void Play(word);                    //Genera un tono de audio
void PlayNota(byte,byte);           //Genera un tono de audio
void Init_Secuencia(void);          //Inicializa el vector de pasos
byte SecuenciaCorrecta(void);       //Recibe la secuencia ingresada y verifica que sea correcta
void MostrarSecuencia(void);        //Muestra la secuencia almacenada
void Delay_ms(word);
byte PresionaBotonOk(byte);    
void MostrarColor(byte,word);
void SonidoBoton(byte);
void PlayCancion(const RINGTONE *);

#endif