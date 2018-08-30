/* Proyecto: Simon
 * Descripción: el clásico juego de los 80 donde el jugador tiene que repetir la secuencia
 * Entradas: 4 Pulsadores PTA0-PTA3 
 * Salidas:  4 Luces PTD0-PTD3
 *           1 Parlante PTD4 TIM1 CH0
 *           7 Display LCD 2x16
 *
*/

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#include "simon.h"

void Init_Puertos(void);
void Init_Timers(void);


void main(void) {
  byte i;
  
  EnableInterrupts; /* enable interrupts */
  CONFIG1_COPD=1;           //Pone a dormir al perrito guardian
 
 /*Inicialización de dispositivos*/
  Init_Puertos();           //Inicializa los puertos
  Init_Timers();            //Iniciliza los timers
  //Init_LCD();
  
 /*Inicio del sistema*/
 
    //Mensaje: *****SIMON****** 
    //         La Salette  2018
  Delay_ms(1000);
      
  for(;;) {
    
    //.Mensaje: PRESIONE UNA TECLA 
    //.         BOTON PARA COMENZAR
    
    while(!flgBotones){
        PlayCancion(Hava);//Espera que se presione un boton para comenzar
    }
    
    
    MostrarColor(ROJO,250);
    MostrarColor(VERDE,250);
    MostrarColor(AZUL,250);
    MostrarColor(AMARILLO,250);
    
    
    
    while(flgBotones);  
    Init_Secuencia();
    
    for(i=0;i<MAX_STEPS;i++){
        
        
        AgregarPaso();
        MostrarColor(APAGADO,1000);
        MostrarSecuencia();
        if(!SecuenciaCorrecta()){
            //. Mensaje: *****ERROR******
            //.          *****ERROR******
            Play(NOTA_ERROR);
            
            Luces=ROJO+AZUL;
            Delay_ms(250);
            Luces=VERDE+AMARILLO;
            Delay_ms(250);
            Luces=ROJO+AZUL;
            Delay_ms(250);
            Luces=VERDE+AMARILLO;
            Delay_ms(250);
            Luces=ROJO+AZUL;
            Delay_ms(250);
            Luces=VERDE+AMARILLO;
            Delay_ms(250);
            Luces=ROJO+AZUL;
            Delay_ms(250);
            Luces=VERDE+AMARILLO;
            Delay_ms(250);
            Luces=APAGADO;
            Play(SILENCIO);
            break;
        }
    }    


  } /* loop forever */
  /* please make sure that you never leave main */
}


void Init_Puertos(void){
    DDRA=0;          //Inicializa el puerto A: Pulsadores
    DDRD=0x0F;       //Inicializa el puerto D: Luces y sonido
    PTD=0;
    //DDRB=0xEF;       //Inicialoza el puerto B: LCD  
    //PTB=0;
}

void Init_Timers(void){
    /* Inicializa el timer 2 como temporizador para que genere un tic cada 10ms */
    T2MOD=25000;
    T2SC=0b01000000;
    
    /* Inicializa el timer 1 como PWM al 50% por el Ch0 */
    T1SC_TSTOP=1;
    T1SC_TRST=1;
    T1MOD=50000;    //50Hz    
    T1CH0=25000;
    T1SC0_MS0B=0;
    T1SC0_MS0A=1;
    T1SC0_TOV0=1;
    T1SC0_ELS0B=1;
    T1SC0_ELS0A=0;    
}



interrupt 9 void TIM2Ovr_IRS(void){
    static word cont=0;
    /* Descuenta uno cada 1ms*/
    
    T2SC_TOF=0;               //Borra el TOF
    
    if(T0F)
      if (Timer>0) 
          Timer--;
      
    if (T1F)
      if (tDelay>0) 
          tDelay--;            
      
    /*Lee el puerto de entrada cada 25ms*/
    if (cont)
      cont--;
    else{
      cont=5;                //debounce
      flgBotones=~Botones;
      if (flgLuces) {
        if (Luces!=flgBotones) SonidoBoton(flgBotones);
        Luces=flgBotones;
        
      }
      //.Sonido
       
    }    
}

interrupt 15 void KBI_IRS (void){
    
}

