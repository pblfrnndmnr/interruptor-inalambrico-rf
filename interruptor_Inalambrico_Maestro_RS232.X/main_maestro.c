/******************************************************************************/
/* Interruptor inalámbrico por RS232
 Autor:Ing. Pablo Fernando Manieri
 Fecha: 27/04/2014

 Funcionamiento modo maestro:
 El pic controla el encendido del modulo RF y además codifica los datos a enviar
 a traves del puerto USART
 Cuando se pulsa el boton de encendido, se enciende el modulo RF, se esperan
 como mínimo 40us y luego se envian al USART los datos codificados medante codigo
 "Manchester u otro mejor" , una vez que finaliza se deshabilita el modulo y entra en un SLEEP
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
#include "Manchester.h"
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

   

   // datoptr = &dato;  //el puntero "datoptr" apunta a la variable dato
    /* Configure the oscillator for the device */
    ConfigureOscillator();
   
    /* Initialize I/O and Peripherals for application */
    configura_USART();
    InitApp();
    char enviaEncendido[5]={DireccionDispositivo,Encendido,0xD5, 0xAA};//debo poner el crc al reves sino no da 0 al volver a calcularlo
    char enviaApagado[5]={DireccionDispositivo,Apagado,0x95,0xA4};//debo poner el crc al reves sino no da 0 al volver a calcularlo
 // calcula_mensaje_crc(enviaEncendido); //se transmite 1Y,0xD5,0xAA
   //calcula_mensaje_crc(enviaApagado);//se trnasmite 1N,0x95,0xA4
   // dato="125";
 // int loco;
  //loco=Manchester(0xFF);
 //   printf("%c%c",(uint8_t)loco,(uint8_t)(loco>>8));
    RB2=0;
    RB1=0;
    while(1)
    {
  // PIE1bits.TXIE=0;
    if (Bandera_boton_pulsado){
         //Deshabilito la interrupcion del RB0
         INTCONbits.INTE=0;
         //Habilito transmisor
       
         RCSTAbits.SPEN=1;//habilito el puerto serie para transmitir los datos
         TransmisorON=1;
         
         //Espero a que se inicie correctamente el transmisor minimo 1.5ms (no verificado)
         __delay_ms(2);
           //Habilito la transmision de datos
         //Envio los datos codificados direccion y estado
         if (datos==Encendido){
             printf("\n%s\r", enviaEncendido);
         }else if(datos==Apagado){
           printf("\n%s\r", enviaApagado);
         }
        //Espero hasta que se transmita el ultimo byte testeando el TRMT//
         while (!TRMT){}
        TransmisorON=0;
        Bandera_boton_pulsado=false;
        //Borro el flag de interrupcion
        INTCONbits.INTF=0;

        //Habilito nuevamente la interrupcion RB0
        INTCONbits.INTE=1;
        
//        RCSTAbits.SPEN=0;//Deshabilito el puerto serie para ahorrar energia
     }
    
    RCSTAbits.SPEN=0;//deshabilito el puerto serie para ahorrar energia
    PORTBbits.RB2=0;//tambien debo poner el pin TX en 0 sino queda el transistor inversor en activo
    
     
     //Pongo a dormir al sistema hasta una nueva pulsación para ahorrar energia
     SLEEP();
    }

}

