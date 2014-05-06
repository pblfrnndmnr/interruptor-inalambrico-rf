
/////////////////////// Driver to generate CRC //////////////////////////
////                                                                 ////
////  generate_8bit_crc(data, length, pattern)                       ////
////        Generates 8 bit crc from the data using the pattern.     ////
////                                                                 ////
////  generate_16bit_crc(data, length, pattern)                      ////
////        Generates 16 bit crc from the data using the pattern.    ////
////                                                                 ////
////  generate_32bit_crc(data, length, pattern)                      ////
////        Generates 32 bit crc from the data using the pattern.    ////
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

#define CRC_16    0x8005      //bit pattern (1)1000 0000 0000 0101
#define CRC_16_INV   0xA001   //bit pattern (1)1010 0000 0000 0001
#define CRC_CCITT 0x1021      //bit pattern (1)0001 0000 0010 0001
#define CRC_CCITT_INV 0x8408      //bit pattern (1)0001 0000 0010 0001
#define CRC_32    0x04C11DB7  //bit pattern (1)0000 0100 1100 0001 0001 1101 1011 0111
#define CRC_DNP   0x3D65      //bit pattern (1)0011 1101 0110 0101
#define bit_test(var,bit)   ((var) & ( 1<<(bit)))>>bit
#define bit_set(var,bit)     ((var)|= ((int) 1<<(bit)))
#define bit_clear(var,bit)     ((var)&=~((int) 1<<(bit)))
void envia_mensaje_crc(void);
int8_t  generate_8bit_crc(char* data, int length, int8_t pattern);


unsigned int generate_16bit_crc(char* data, unsigned int length, unsigned int pattern);
int calcula_CRC16(void);