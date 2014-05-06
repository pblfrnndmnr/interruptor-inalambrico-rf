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
        // debo cambiar el flanco para saber en que estado est�
    if (OPTION_REGbits.INTEDG==true){
    OPTION_REGbits.INTEDG=false;
        }else{
    OPTION_REGbits.INTEDG=true; //Interrupcion por flanco de subida  de RB0
     }

        

        Bandera_estado_llave=true;

       INTCONbits.INTF=0;

   /*Verifico si se proceso el comando, si es as� deshabilito la interrupcion para
     dar tiempo a que se procese  y evitar el bouncing en el pulsador*/
   //if (!Bandera_dato_recibido)INTCONbits.INTE=0;

  
    }
    else{ if (PIR1bits.RCIF){
        
        datosrecibidos=getch();
        if (datosrecibidos==0x0a){
            recibi_datos= true;}
        // kbhit();
    }
    
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

