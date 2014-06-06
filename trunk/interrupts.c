/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "usart1.h"
#include "user.h"
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

void interrupt isr(void)
{
    //Verifico que se entro a la interrupcion por RB0

  if(INTCONbits.INTF==1&&INTCONbits.INTE==1){
      // debo cambiar el flanco para saber en que estado está
    /*  if (OPTION_REGbits.INTEDG==true){
      INTCONbits.INTE=0;
          OPTION_REGbits.INTEDG=false;
          
      }else{
          INTCONbits.INTE=0;
          OPTION_REGbits.INTEDG=true; //Interrupcion por flanco de subida  de RB0
          
      }*/
      TMR0=60;
      INTCONbits.T0IF=0;
     INTCONbits.T0IE=1;
     //Bandera_estado_llave=true;
    //  pasaron_20ms=false;
      INTCONbits.INTF=0;
      /*Verifico si se proceso el comando, si es así deshabilito la interrupcion para
      dar tiempo a que se procese  y evitar el bouncing en el pulsador*/
      //if (!Bandera_dato_recibido)INTCONbits.INTE=0;
  }else{
      if (PIR1bits.RCIF){
          //la secuencia que envia el maestro es  DireccionDispositivoEncendidoCRC\n\r
          //por ejemplo si
          // DireccionDispositivo '1'
          // Encendido 'Y'
          // Apagado   'N'
          // CRC 0xD5AA //para encendido
          // CRC 0x95A4 //para apagado
          //Sincronizacion \n
          //\r
          //por lo tanto la secuencia completa es
          //"\n1YÕª\r"  para Encendido y
          //"\n1Nòñ\r para apagado
          // con cualquiera de las dos secuencias de 6 bytes  correctas se debe validar el
          //comando recibido
          volatile unsigned char datosrecibidos;
          datosrecibidos=getch();
          if (indice_de_dato<4){
          cadenarecibida[indice_de_dato]=datosrecibidos;
          indice_de_dato++;
          } else {
              recibi_datos=true;
          }
          if (datosrecibidos==Sincronizacion){
              indice_de_dato=0;
          }
          if (datosrecibidos=='\r'){
              indice_de_dato=0;
          }
      }else {
          if(INTCONbits.T0IF){
             //debo entrar dos veces a la interrupcion para que pasen 20ms
             if (pasaron_20ms){
                 if(RB0==OPTION_REGbits.INTEDG){
                OPTION_REGbits.INTEDG= !OPTION_REGbits.INTEDG;
                     Bandera_estado_llave=true;
                  INTCONbits.INTF=0;
                 INTCONbits.INTE=1;
                 }
                 pasaron_20ms=false;
                 INTCONbits.T0IE=0;
                
             }
             else {
                 pasaron_20ms=true;
             
             }
             TMR0=60;
             INTCONbits.T0IF=0;
            
          }

      }

    /* Agregado y configurado interrupcion por timer0 para eliminar rebote
      pulsador, //TODO// debo tambien verificar que estado tenia la tecla antes de pulsarla
      comprobar que se encontraba en ese estado cuando termine la comprobacion,
     para eliminar disparos espureos, es decir que si viene un pulso que dura
      menos de 20ms ignorar esa situación*/
  }
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

#if 0
    
    /*  Add interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if(<Interrupt Flag 1>)
    {
        <Interrupt Flag 1=0>; /* Clear Interrupt Flag 1 */
    }
    else if (<Interrupt Flag 2>)
    {
        <Interrupt Flag 2=0>; /* Clear Interrupt Flag 2 */
    }
    else
    {
        /* Unhandled interrupts */
    }
#endif
}
#endif


