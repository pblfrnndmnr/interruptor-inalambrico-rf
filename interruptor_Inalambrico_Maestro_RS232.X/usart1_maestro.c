

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>
#include "usart1_maestro.h"
#include "system_maestro.h"

void configura_USART (void){
    //Calculo la carga del registro en base al baudrate elegido baudrate
//FOSC=_XTAL_FREQ
//X=SPBRG
//BAUDRATE=FOSC/(64(X+1)) //en low speed
//BAUDRATE=FOSC/(16(X+1)) //en high speed
//X=FOSC/64/BAUDRATE-1 en low speed
//X=FOSC/16/BAUDRATE-1 en low speed
 //Si FOSC=20MHZ
//X=20000000/64/2400-1

//X=129 para low speed
SPBRG= _XTAL_FREQ/64/baudrate-1;
//SPBRG=129;
    TXSTAbits.CSRC=1; /*Asynchronous mode
Don?t care
Synchronous mode
1 = Master mode (Clock generated internally from BRG)
0 = Slave mode (Clock from external source)*/
    TXSTAbits.TX9=0;/*9-bit Transmit Enable bit
        1 = Selects 9-bit transmission
        0 = Selects 8-bit transmission*/

TXSTAbits.SYNC=0;/* USART Mode Select bit
1 = Synchronous mode
0 = Asynchronous mode*/


TXSTAbits.BRGH=0; /*High Baud Rate Select bit
Asynchronous mode
1 = High speed
0 = Low speed
Synchronous mode
Unused in this mode*/
TXSTAbits.TX9D=1;// 9th bit of transmit data. Can be parity bit.
//Note: SREN/CREN overrides TXEN in SYNC mode.
 

TXSTAbits.TXEN=1; /*Transmit Enable bit(1)
1 = Transmit enabled
0 = Transmit disabled*/
RCSTAbits.SPEN=0;/*Dejo deshabilitado el puerto serie para ahorar energia, solo se habilita al momento de enviar datos
(Configures RB1/RX/DT and RB2/TX/CK pins as serial port pins when bits TRISB<2:1> are set)
1 = Serial port enabled
0 = Serial port disabled*/
RCSTAbits.CREN=0;/*Continuous Receive Enable bit
Asynchronous mode:
1 = Enables continuous receive
0 = Disables continuous receive
Synchronous mode:
1 = Enables continuous receive until enable bit CREN is cleared (CREN overrides SREN)
0 = Disables continuous receive*/
}


//prototipo de la funcion PUTCH para poder enviar al USART con printf
void putch(char data) {
 while( ! TXIF)
 continue;
 TXREG = data;
}