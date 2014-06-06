/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user_maestro.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /*  Initialize User Ports/Peripherals/Project here */
    //Pongo todos los puertos en bajo antes de inicializarlos
    PORTB=0b00000000;
    //Solo pongo el enable del HT12 en alto por logica negada
   PORTA=0b00000000;
    
    /* Setup analog functionality and port direction */
      //Inicio el puerto b como salida salvo RB0 que sera la entrada del pulsador
   //El pin TX va a ser controlado por el USART
   TRISB=0b00000001;
    CMCON=0x00000111; //desactivo los comparadores
    //Inicio el puerto A como salida para evitar captar ruido
    TRISA=0b00000000;

    /* Initialize peripherals */

   OPTION_REGbits.PS=0b000; //000 -> 1/2 para el timer0
    OPTION_REGbits.PSA=0; ///Prescaler is assigned to the Timer0 module
    OPTION_REGbits.T0CS=0; //TMR0 Clock Source Select bit Internal
    OPTION_REGbits.T0SE=0; //TMR0 Source Edge Select bit (no usado ahora)
    OPTION_REGbits.nRBPU=1; //Deshabilito las resistencias pullup del puerto B, para no consumir corriente

    #ifdef UsaTecla
    //Para ver en que flanco debo detectar la pulsacion de RB0, testeo la entrada antes de elegirlo
    if (PORTBbits.RB0==true){
    OPTION_REGbits.INTEDG=0;
    }else{
    OPTION_REGbits.INTEDG=1; //Interrupcion por flanco de subida  de RB0
    }
    #else
    //si se usa pulsador solo tengo que detectar el flanco de bajada
    OPTION_REGbits.INTEDG=0; //Interrupcion por flanco de bajada  de RB0
    #endif
    /* Enable interrupts */

    INTCONbits.INTF=0; //Limpio el flag de interrupcion de RB0
    INTCONbits.INTE=1; //Habilito interrupcion RB0
    //PIE1bits.TXIE=1; //Habilito la interrupcion de transmision deUSART
 //   INTCONbits.PEIE=1; //habilito interrupcion de perifericos
    INTCONbits.GIE=1; //Habilito interrupciones globales

}

