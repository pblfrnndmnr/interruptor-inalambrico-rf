/******************************************************************************/
/* Interruptor inalámbrico
 Autor:Ing. Pablo Fernando Manieri
 Fecha: 27/04/2014

 Funcionamiento modo esclavo:
 El pic detecta los datos recibidos por el modulo RF a del USART
 
 Como el interruptor está conectado con otra tecla normal alimentada con 220V,
 se debe detectar el estado de esta tecla con un pin del pic y hacer las veces
 de una llave combinada, es decir, al momento de encender el circuito
 la lampara comienza apagada, se detecta si la lleve esta en on o en off y se
 guarda el estado, luego si se recibe un dato por RF o cambia el estado de la
 llave se enciende la lampara, hasta un nuevo cambio de estados.*/
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

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include <stdio.h>
#include <conio.h>
#include "usart1.h"
#include "crc_esclavo.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
//#define TransmisorON PORTBbits.RB1
//#define TE_HT12E PORTBbits.RB2
//bool Bandera_boton_pulsado;

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
  

void main(void)
{
    /* Configure the oscillator for the device */

    ConfigureOscillator();
   __delay_ms(20);
    /* Initialize I/O and Peripherals for application */
    InitApp();
   //TE_HT12E=1;
    configura_USART ();
   // __delay_ms(10);
    
   
    while(1)
    {   

     if (Bandera_estado_llave){
         Bandera_estado_llave=false;
         PORTBbits.RB3=~PORTBbits.RB3;
     }
     if (recibi_datos){
         
         recibi_datos=false;
         indice_de_dato=0;
         
         if (calcula_mensaje_crc(cadenarecibida)==0){
             PORTBbits.RB3=~PORTBbits.RB3;
         }
     }

    }

}

