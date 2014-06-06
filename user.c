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

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /*  Initialize User Ports/Peripherals/Project here */
    //Pongo todos los puertos en bajo antes de inicializarlos
    PORTB=0b00000000;
   
    PORTA=0b00000000;
    
    /* Setup analog functionality and port direction */
    /*Inicio el puerto b como salida salvo RB0 que sera la entrada que me dice
     del estado de la llave*/
    //También RB1 que será la entrada de los datos recibidos por USART
    TRISB=0b00000011;
    CMCON=0x00000111; //desactivo los comparadores
    //Inicio el puerto A como salida para evitar captar ruido
    TRISA=0b00000000;

    /* Initialize peripherals */

//Inicio el TIMER0
    //elijo el prescaler para que interrumpa cada 13.05ms
    #define PRESCALER 0b111 //-> 256
//Ajusto la precarga del TIMER0 para que interrumpa cada 10ms
    // debe ser TIMER0=59, esto asignado al entrar a la interrupcion
    OPTION_REGbits.PS=PRESCALER; //000 -> 1/2 para el timer0
    OPTION_REGbits.PSA=0; ///Prescaler is assigned to the Timer0 module
    OPTION_REGbits.T0CS=0; //TMR0 Clock Source Select bit Internal
    OPTION_REGbits.T0SE=0; //TMR0 Source Edge Select bit (no usado ahora)
    OPTION_REGbits.nRBPU=0; //Habilito las resistencias pullup del puerto B
    OPTION_REGbits.INTEDG=1; //Interrupcion por flanco de subida de RB0
   
    /* Enable interrupts */

   // INTCONbits.INTF=0; //Limpio el flag de interrupcion de RB0
    PIE1bits.RCIE=1; //Habilito interrupcion de recepcion de USART
   
    INTCONbits.PEIE=1;//Habilito la interupcion de los perifericos
    //INTCONbits.T0IE=1; //Habilito la interrupcion del TIMER0
    INTCONbits.GIE=1; //Habilito interrupciones globales

 //Para ver en que flanco debo detectar la pulsacion de RB0, testeo la entrada antes de elegirlo
    if (PORTBbits.RB0==true){
    OPTION_REGbits.INTEDG=0;
    }else{
    OPTION_REGbits.INTEDG=1; //Interrupcion por flanco de subida  de RB0
    }
INTCONbits.INTF=0;
    INTCONbits.INTE=1; //Habilito interrupcion RB0
}

