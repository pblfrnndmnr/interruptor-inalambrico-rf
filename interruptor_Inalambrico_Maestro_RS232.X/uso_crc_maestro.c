
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

// CONSTANTS
#define MACHINE_ADDRESS 0x31
#define SEND_ADDRESS    0x32
#define ACK             0x01
#define NACK            0xFF
#define BUFFER_SIZE     9

// GLOBAL VARIABLES
int packet_buffer[BUFFER_SIZE];

char paquete[]="123456789";

// SEND_PACKET
// function to send a packet of data to another PIC
void send_packet(char* packet_ptr, int packet_length)
{
   char *ptr;
  unsigned int  CRC;
   unsigned int i;
   ptr = packet_ptr;                            // set pointer
   i= bit_test(0b0111111111111111,15);
   CRC = generate_16bit_crc(ptr, packet_length, CRC_CCITT);
   CRC=calcula_CRC16();
   // make CRC
   for(i=0; i<packet_length; i++)               // send packet
      putch(packet_ptr[i]);

   printf("%X",CRC);
   //putch((int)(CRC>>8));                         // send CRC
   //putch((int)(CRC));
}



void envia_mensaje_crc(void)   {

   
  

       /*  packet_buffer[0] = SEND_ADDRESS;
         packet_buffer[1] = MACHINE_ADDRESS;
         packet_buffer[2] = 'H';
         packet_buffer[3] = 'i';
         packet_buffer[4] = ' ';
         packet_buffer[5] = 't';
         packet_buffer[6] = 'h';
         packet_buffer[7] = 'e';
         packet_buffer[8] = 'r';
         packet_buffer[9] = 'e';
         packet_buffer[10] = '!';*/
         send_packet(paquete,9);        // send message


   }

int8_t generate_8bit_crc(char* data, int length, int8_t pattern)
{
   char   *current_data;
   int8_t   crc_byte;
   int byte_counter;
   int8_t   bit_counter;

   current_data = data;
   crc_byte = *current_data++;

   for(byte_counter=0; byte_counter < (length-1); byte_counter++)
   {
      for(bit_counter=0; bit_counter < 8; bit_counter++)
      {
         if(!bit_test(crc_byte,7))
         {
            crc_byte <<= 1;
            bit_test(*current_data, 7 - bit_counter) ?
               bit_set(crc_byte,0) : bit_clear(crc_byte,0);
            continue;
         }
         crc_byte <<= 1;
         bit_test(*current_data, 7 - bit_counter) ?
            bit_set(crc_byte,0) : bit_clear(crc_byte,0);
         crc_byte ^= pattern;
      }
      current_data++;
   }
   for(bit_counter=0; bit_counter < 8; bit_counter++)
   {
      if(!bit_test(crc_byte,7))
      {
         crc_byte <<= 1;
         continue;
      }
      crc_byte <<= 1;
      crc_byte ^= pattern;
   }
   return crc_byte;
}


unsigned int generate_16bit_crc(char* data, unsigned int length,unsigned int pattern)
{
   char   *current_data;
   unsigned int crc_Dbyte;
   int byte_counter;
   uint8_t   bit_counter;

   current_data = data + 2;
   crc_Dbyte =  (data[0] << 8) ||  data[1];

   for(byte_counter=0; byte_counter < (length-2); byte_counter++)
   {
      for(bit_counter=0; bit_counter < 8; bit_counter++)
      {
         if(!bit_test(crc_Dbyte,15))
         {
            crc_Dbyte <<= 1;
            bit_test(*current_data, 7 - bit_counter) ?
               bit_set(crc_Dbyte,0) : bit_clear(crc_Dbyte,0);
            continue;
         }
         crc_Dbyte <<= 1;
         bit_test(*current_data, 7 - bit_counter) ?
            bit_set(crc_Dbyte,0) : bit_clear(crc_Dbyte,0);
         crc_Dbyte ^= pattern;
      }
      current_data++;
   }

   for(bit_counter=0; bit_counter < 16; bit_counter++)
   {
      if(!bit_test(crc_Dbyte,15))
      {
         crc_Dbyte <<= 1;
         continue;
      }
      crc_Dbyte <<= 1;
      crc_Dbyte ^= pattern;
   }

   return crc_Dbyte;
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

int calcula_CRC16(void)
{
    //QCoreApplication a(argc, argv);
    char datos[]="123456789";
    int i;
    long inival;

    inival=0x0000;
    for(i=0;i<strlen(datos);i++){
        inival=CRC16(datos[i],CRC_CCITT_INV,inival,0x0000);
    }

    inival^=0x0000;
    
    return inival;


   // return a.exec();
}

