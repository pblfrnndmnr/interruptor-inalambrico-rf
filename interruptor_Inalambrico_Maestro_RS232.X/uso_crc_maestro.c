
/////////////////////////////////////////////////////////////////////////
////                            EX_CRC.C                             ////
////                                                                 ////
////  This example program shows how to send messages between two    ////
////  PICs using CRC error checking.  Pushing a button on the        ////
////  prototype card sends a message from that PIC to any other PICs ////
////  that are connected.  The receiving PIC then sends back an ACK  ////
////  after it correctly receives the message.                       ////
////                                                                 ////
////  Two seperate PICs are needed for this example.  Compile the    ////
////  code as is and program the first PIC.  Then switch the         ////
////  MACHINE_ADDRESS and SEND_ADDRESS and program the second PIC.   ////
////                                                                 ////
////                                                                 ////
////  Packet Protocol:                                               ////
////  +------------+--------------+---------+--------+------+-----+  ////
////  | Address TO | Address FROM | Control | Length | Data | CRC |  ////
////  +------------+--------------+---------+--------+------+-----+  ////
////                                                                 ////
////  Address TO:    1 byte         Address of sending PIC           ////
////  Address FROM:  1 byte         Address of receiving PIC         ////
////  Control:       1 byte         Used for ACK and NACK            ////
////  Length:        2 bytes        Number of bytes in Data field    ////
////  Data:          0 to N bytes   Data being sent                  ////
////  CRC:           2 bytes        16 Bit CRC                       ////
////                                                                 ////
////  Configure the CCS prototype card as follows:                   ////
////     Jumper from PIC 1 pin B0 to PIC 2 pin B1                    ////
////     Jumper from PIC 1 pin B1 to PIC 2 pin B0                    ////
////     Jumper from PIC 1 GND to PIC 2 GND                          ////
////     Jumper from PIC 1 Switch to PIC 1 pin B2                    ////
////     Jumper from PIC 2 Switch to PIC 2 pin B2                    ////
////     See additional connections below.                           ////
////                                                                 ////
////  This example will work with the PCM and PCH compilers.  The    ////
////  following conditional compilation lines are used to include a  ////
////  valid device for each compiler.  Change the device, clock and  ////
////  RS232 pins for your hardware if needed.                        ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2003 Custom Computer Services         ////
//// This source code may only be used by licensed users of the CCS  ////
//// C compiler.  This source code may only be distributed to other  ////
//// licensed users of the CCS C compiler.  No other use,            ////
//// reproduction or distribution is permitted without written       ////
//// permission.  Derivative programs created using this software    ////
//// in object code form are not restricted in any way.              ////
/////////////////////////////////////////////////////////////////////////

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

// SEND_PACKET
// Funcion que envia el paquete al otro pic, codificado con CRC
void calcula_mensaje_crc(char* packet_ptr)
{
   //char *ptr;
  unsigned int  CRC;
   //ptr = packet_ptr;                            // set pointer
   //CRC = generate_16bit_crc(ptr, packet_length, CRC_CCITT);
   CRC=calcula_CRC16(packet_ptr,CRC_16_INV,INIVAL_CRC_16);
   // make CRC
   

   printf("%s el crc es:%X\n\r",packet_ptr,CRC);
   //putch((int)(CRC>>8));                         // send CRC
   //putch((int)(CRC));
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CALC_CRC16
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Calcula CRC de polinomios de 17 bits               By BrunoF(Bruno Fascendini) para el foro todopic:http://www.todopic.com.ar/foros
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Recibe:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//value: int16 del valor del cual calcular el CRC
//poly: int16 del valor del polinomio ASOCIADO* con el cual se calcula el CRC
//Tener en cuenta que el algoritmo usa el polinomio invertido
//enter_value: int16 del valor de entrada con el cual realizar XOR
//exit_value: int16 del valor de salida con el cual realizar XOR
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Devuelve:
//value: int16 con el CRC calculado
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long CRC16(char value, long poly, long init_value, long exit_value){
     long res;
     long i;

     res=value;

     res^=init_value;

     for(i=0;i<8;i++){
         if(res & 1){
             res>>= 1;
             res^=poly;
         }else{
             res>>= 1;
         }
     }
    res^=exit_value;
    return res;
}

int calcula_CRC16(char datos[],long polinomio,long inival)
{
   
    int i;
 
    for(i=0;i<strlen(datos);i++){
        inival=CRC16(datos[i],polinomio,inival,0x0000);
    }
    switch (polinomio){
        case CRC_DNP_INV:
            inival^=0xFFFF; //complemento a 1 del CRC
            unsigned int aux;
            aux=(unsigned int)inival;
            inival=(long)((aux<<8)+(aux>>8)); //invierto los bytes

            break;
         default:
            break;

    }
    
    return inival;


   // return a.exec();
}

