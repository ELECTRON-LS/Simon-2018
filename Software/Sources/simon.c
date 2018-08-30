#include "derivative.h"

#include "simon.h"

const word Notas[]={
  SILENCIO,2*C,2*Db,2*D,2*Eb,2*E,2*F,2*Gb,2*G,2*Ab,2*A,2*Bb,2*B,
  C,Db,D,Eb,E,F,Gb,G,Ab,A,Bb,B,
  C/2,Db/2,D/2,Eb/2,E/2,F/2,Gb/2,G/2,Ab/2,A/2,Bb/2,B/2    
};

/* Canciones */
const RINGTONE Cuca[]={
  {C1,1},{C1,1},{C1,1},{F1,2},{A1,2},
  {C1,1},{C1,1},{C1,1},{F1,2},{A1,2}, 
  {SILENCIO,1},
  {F1,1},{F1,1},{E1,1},{E1,1},{D1,1},{D1,1},{C1,2},
  {SILENCIO,1},
  {C1,1},{C1,1},{C1,1},{E1,2},{G1,2},
  {C1,1},{C1,1},{C1,1},{E1,2},{G1,2}, 
  {SILENCIO,1},
  {C2,1},{D2,1},{C2,1},{Bb1,1},{A1,1},{G1,1},{F1,2},
  {SILENCIO,1},
  {0,0}
};


const RINGTONE Hava[]={
  
  {E1,4},{E1,4},{SILENCIO,1},{Ab1,2},{F1,2},{E1,2},{Ab1,4},{Ab1,4},{SILENCIO,1},
  {B1,2},{A1,2},{Ab1,2},{A1,4},{A1,4},{SILENCIO,1},
  {C2,2},{B1,2},{A1,2},{Ab1,4},{F1,1},{E1,2},{E1,2},{Ab1,4},{SILENCIO,2},
   
  {E1,4},{E1,4},{SILENCIO,1},{Ab1,2},{F1,2},{E1,2},{Ab1,4},{Ab1,4},{SILENCIO,1},
  {B1,2},{A1,2},{Ab1,2},{A1,4},{A1,4},{SILENCIO,1},
  {C2,2},{B1,2},{A1,2},{Ab1,4},{F1,1},{E1,2},{E1,2},{Ab1,4},{SILENCIO,2},
   
  {Ab1,2},{Ab1,2},{SILENCIO,2},{F1,2},{E1,2},{E1,2},{E1,2},{SILENCIO,2},
  {F1,2},{F1,2},{SILENCIO,2},{E1,2},{D1,2},{D1,2},{D1,2},{SILENCIO,2},
  {D1,4},{F1,2},{SILENCIO,1},{E1,2},{D1,2},{D1,2},{A1,4},{Ab1,4},{F1,1},{E1,2},{E1,2},{Ab1,4},{SILENCIO,2},
  
  {Ab1,2},{Ab1,2},{SILENCIO,2},{F1,2},{E1,2},{E1,2},{E1,2},{SILENCIO,2},
  {F1,2},{F1,2},{SILENCIO,2},{E1,2},{D1,2},{D1,2},{D1,2},{SILENCIO,2},
  {D1,4},{F1,2},{SILENCIO,1},{E1,2},{D1,2},{D1,2},{A1,4},{Ab1,4},{F1,1},{E1,2},{E1,2},{Ab1,4},{SILENCIO,2},
  
   
  {A1,4},{SILENCIO,4},{A1,4},{SILENCIO,4},{A1,4},{A1,4},{A1,4},{A1,2},{SILENCIO,2},
  {A1,2},{A1,2},{C2,2},{SILENCIO,1},{B1,1},{A1,2},{C2,2},{B1,2},{A1,2}, 
  {A1,2},{A1,2},{C2,2},{SILENCIO,1},{B1,1},{A1,2},{C2,2},{B1,2},{A1,2},
  {B1,2},{B1,2},{D2,2},{SILENCIO,1},{C2,1},{B1,2},{D2,2},{C2,2},{B1,2}, 
  {B1,2},{B1,2},{D2,2},{SILENCIO,1},{C2,1},{B1,2},{D2,2},{C2,2},{B1,2}, 
  {B1,2},{B1,2},{E2,8},{B1,2},{B1,2},{E2,8},{B1,2},{B1,2},{E2,8},
  {D2,1},{C2,2},{B1,4},{A1,8}, 
    
  {0,0}

};

/*
D D Gb Eb D Gb Gb A G Gb G G Bb A G Gb Eb D Gb 

*/
const RINGTONE RM[]={
  {Bb0,8},{Db1,4},{C1,4},{Eb1,4},{Ab0,4},{Gb0,4},{F0,8},
  {Bb0,8},{Db1,4},{C1,4},{Eb1,4},{Ab1,4},{Gb1,4},{F1,8},
  {0,0}
};

//Bb Db C Eb Ab(lower) Gb F | Bb Db C Eb Ab(higher) Gb F

/*Puertos de entrada y de salida*/
volatile PENT _Botones;
volatile PSAL _Luces;

/*Variables globales*/
volatile word Timer;
volatile byte tDelay;
volatile byte Pasos[MAX_STEPS+1];
volatile FLAGS _flags;
volatile TIMFLAGS _timflags;

void Delay_ms(word ms){
    /*Espera una cantidad de milisegundos*/
    T1F=0;
    tDelay=ms/10;
    T1F=1;
    while(tDelay);    
}

void Play(word nota){
    /*Cambia la frecuencia del PWM manteniendo el ciclo al 50& */
    
    if(nota){
        T1MOD=nota;
        T1CH0=nota/2;
        T1SC0_MS0x=1;
        T1SC0_ELS0x=2;
        T1SC_TSTOP=0;
        T1SC_TOF=0;    
    }else {
      T1SC_TOF=0;
      T1SC_TSTOP=1;
      T1SC0_MS0x=0;
      T1SC0_ELS0x=0;
      PTD_PTD4=0;
    }
    
}

byte Aleatorio(void){
    byte paso;
    paso=1;
    paso=paso << (T2CNT & 0x03);   //Lee el contador del timer 2 y rescara los dos ultimos bits
    return (paso);
}

//void Luz(byte Luz)
void AgregarPaso(void){
    /*Agrega un nuevo paso a la secuencia*/
    byte i=0;
    
    while (Pasos[i]) i++;                      //Se mueve hasta la primera posicion libre
    
    if (i<=MAX_STEPS) Pasos[i]= Aleatorio();
           
}

void Init_Secuencia(void){ 
    /*Inicializa el vector de secuencia todo en 0*/
    byte i;
    
    for (i=0;i<MAX_STEPS+1;i++){
       Pasos[i]=0;
    }
}

void MostrarSecuencia(void){
  /*Muestra la secuencia de luces almacenada en Pasos*/  
    word i=0;
  
    while(Pasos[i]){
        MostrarColor(Pasos[i],500);
        MostrarColor(APAGADO,500);
        //. Sonido
        i++;
    }
}

void MostrarColor(byte color,word ms){
  /*Muestra un color durante un tiempo*/    
    Luces=APAGADO;
    Luces=color;
    SonidoBoton(Luces);
    Delay_ms(ms);
    //.Sonido
    Luces=APAGADO;    
    SonidoBoton(Luces);
    
}



void SonidoBoton(byte Boton){
  static byte ultimoBoton=0;
  
      switch(Boton){
        case ROJO:
          Play(NOTA_ROJO);
          break;
        case VERDE:
          Play(NOTA_VERDE);
          break;
        case AZUL:
          Play(NOTA_AZUL);
          break;
        case AMARILLO:
          Play(NOTA_AMARILLO);
          break;
        case SILENCIO:
          Play(SILENCIO);
      }
    
}


void PlayNota(byte nota, byte temp){
    if (nota) Luces=15;
    Play(Notas[nota]);
    Delay_ms((word) temp*Tempo);
    Luces=0;
    Play(SILENCIO);
    Delay_ms((word) temp*Tempo);
  
}


byte SecuenciaCorrecta(void){
    byte i=0,resultado=1;
    
    while (Pasos[i]){
        if(PresionaBotonOk(Pasos[i]))
            i++;
        else {
            resultado=0;
            break;
        }      
    }
 
    return (resultado);
    
}

byte PresionaBotonOk(byte boton){
    /*Espera a que se presione un boton y verifica si es correcto y el timeout*/    
    byte resultado=0;
    T0F=0;
    Timer=10000;                              //Setea el timer
    T0F=1;
    flgLuces=15;                              //Habilita las luces controldas por los botones
    while (Timer){
        if(Luces){                               //Boton presionado
            
            if (Luces==boton) {  
                
                while (Luces)                           //Espera a que se libere el boton
                  resultado=(byte) Timer;     //Si se acaba el tiempo devuelve 0                 
            }
        
            break;
        }
    }
    
    Luces=0;
    flgLuces=0;                               //Deshabilita las luces
    return (resultado);
}

void PlayCancion(const RINGTONE  *cancion){
  byte i=0;
  while(cancion[i].temp){
     PlayNota(cancion[i].nota,cancion[i].temp);
     if (flgBotones)  break;
     i++;
  }

}