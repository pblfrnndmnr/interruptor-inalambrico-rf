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

    if(INTCONbits.INTF==1){
        // debo cambiar el flanco para saber en que estado está
    if (OPTION_REGbits.INTEDG==true){
    OPTION_REGbits.INTEDG=false;
        }else{
    OPTION_REGbits.INTEDG=true; //Interrupcion por flanco de subida  de RB0
     }

        

        Bandera_estado_llave=true;

       INTCONbits.INTF=0;

   /*Verifico si se proceso el comando, si es así deshabilito la interrupcion para
     dar tiempo a que se procese  y evitar el bouncing en el pulsador*/
   //if (!Bandera_dato_recibido)INTCONbits.INTE=0;

  
    }
    else{ if (PIR1bits.RCIF){
        //la secuencia que envia el maestro es  DireccionDispositivoEncendido\n\r
        //por ejemplo si
        // DireccionDispositivo 0xEA
        // Encendido 0b10100000= 0xA0
        // Apagado   0b01010000= 0x50
        //\n=0x0A
        //\r=0x0D
        //por lo tanto la secuencia completa es 
        //EAA00A0D para Encendido y
        //EA500A0D para apagado
        // con cualquiera de las dos secuencias correctas se debe validar el 
        //comando recibido
        datosrecibidos=getch();
        
        switch (indice_de_dato){
            case 0:
                if (datosrecibidos==DireccionDispositivo){
                    cadenarecibida[indice_de_dato]=datosrecibidos;
                    indice_de_dato++;
                }
                break;
            case 1:
                if ((datosrecibidos==Encendido)||(datosrecibidos==Apagado)){
                    cadenarecibida[indice_de_dato]=datosrecibidos;
                    indice_de_dato++;
                }

                break;
            case 2:
                //if (datosrecibidos=='\n'){
                cadenarecibida[indice_de_dato]=datosrecibidos;
                indice_de_dato++;
             
                //  }
                break;
            case 3:
               // if (datosrecibidos=='\r'){
               //       recibi_datos= true;
                cadenarecibida[indice_de_dato]=datosrecibidos;
                indice_de_dato++;
               // }
                break;
            case 4:
                if (datosrecibidos=='\n'){
                  indice_de_dato++;
                }
                  break;
            case 5:
                if (datosrecibidos=='\r'){

                    recibi_datos= true;
                      indice_de_dato=3;
                }


                break;
            default:
                recibi_datos= false;
                 indice_de_dato=0;
                break;
        
        
        }
 
    }
    //TODO Agregar y configurar interrupcion por timer0 o 1 para eliminar rebote pulsador
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


