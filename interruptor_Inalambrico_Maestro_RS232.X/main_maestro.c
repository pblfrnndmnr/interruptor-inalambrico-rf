/******************************************************************************/
/* Interruptor inalámbrico por RS232
 Autor:Ing. Pablo Fernando Manieri
 Fecha: 27/04/2014

 Funcionamiento modo maestro:
 El pic controla el encendido del modulo RF y además codifica los datos a enviar
 a traves del puerto USART
 Cuando se pulsa el boton de encendido, se enciende el modulo RF, se esperan
 como mínimo 40us y luego se envian al USART los datos codificados medante codigo
  TODO "Manchester u otro mejor" , una vez que finaliza se deshabilita el modulo y entra en un SLEEP
  hasta que se pulse nuevamente.*/
/******************************************************************************/


/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#ifndef __PICCPRO__
#define __PICCPRO__
#endif

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <stdio.h>
#include "system_maestro.h"        /* System funct/params, like osc/peripheral config */
#include "user_maestro.h"          /* User funct/params, such as InitApp */
#include "usart1_maestro.h"
#include <string.h>
#include "crc_maestro.h"
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
//#define TransmisorON PORTBbits.RB1
//#define TE_HT12E PORTBbits.RB2
bool Bandera_boton_pulsado;

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
  
///////////////////////////////////////////////////////////////////////////////
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();
   
    /* Initialize I/O and Peripherals for application */
    configura_USART();
    InitApp();
   //TE_HT12E=1;
    //configura_USART();
   // __delay_ms(10);

 /*  int i;
    for (i=1;i<=255;i++){
      __delay_ms(1000);
        printf("%u__",i);
        putch(i);
    }*/
 // printf("Codigo enviado: %x%x\n\r", DireccionDispositivo,Encendido);
   
  //printf("Codigo Enviado: %x%x\n\r", DireccionDispositivo,Apagado);
     char enviaEncendido[5]={DireccionDispositivo,Encendido,0xD5, 0xAA};//debo poner el crc al reves sino no da 0 al volver a calcularlo
    char enviaApagado[5]={DireccionDispositivo,Apagado,0x95,0xA4};//debo poner el crc al reves sino no da 0 al volver a calcularlo
  //calcula_mensaje_crc(enviaEncendido); //se transmite 1Y,0xD5,0xAA
   //calcula_mensaje_crc(enviaApagado);//se trnasmite 1N,0x95,0xA4
    
while(1)
    {

        if (Bandera_boton_pulsado){   
         //Deshabilito la interrupcion del RB0
         INTCONbits.INTE=0;
         //Habilito transmisor
         TransmisorON=1;
         PORTBbits.RB5=1;
         //Espero a que se inicie correctamente el transmisor minimo 40us (no verificado)
         __delay_ms(1);
           //Habilito la transmision de datos
         //Envio los datos codificados direccion y estado
         if (datos==Encendido){
         printf("%s\n\r", enviaEncendido);
         }else if(datos==Apagado){
         printf("%s\n\r", enviaApagado);
         }
        
         
               
        /*TODO Espero que se transmitan todos los datos a 2400b/seg, son 4 Bytes,
        o sea 48 bits, tarda ~20ms*/
        __delay_ms(30);
        TransmisorON=0;
        Bandera_boton_pulsado=false;
        //Borro el flag de interrupcion
        INTCONbits.INTF=0;

        //Habilito nievamente la interrupcion RB0
        INTCONbits.INTE=1;
        
        
     }
     //Pongo a dormir al sistema hasta una nueva pulsación para ahorrar energia
     SLEEP();
    }

}

