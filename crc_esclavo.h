
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
/*/
     Contents  : Documentation for the CRC functions in uso_crc_maestro.c

   Support   : http://www.lammertbies.nl/forum/viewforum.php?f=11



   The file Uso_crc_maestro.c contains source code for functions to calculate
   two commonly used CRC values: CRC_8,CRC-16, CRC-DNP, CRC-SICK,
   CRC-Kermit and CRC-CCITT. The functions can be freely used.

   To calculate a CRC, the following three steps must be followed:

   1. Initialize the CRC value. For CRC-16, CRC-SICK CRC-Kermit and CRC-DNP
      the initial value of the CRC is 0. For CRC-CCITT and CRC-MODBUS,
      the value 0xffff is used.

      3. Only for CRC-DNP: After all input processing, the one's complement
      of the CRC is calcluated and the two bytes of the CRC are swapped.

   4. Only for CRC-Kermit and CRC-SICK: After all input processing, the
      one's complement of the CRC is calcluated and the two bytes of the CRC
      are swapped.



   An example of this calculation process can be found in the tst_crc.c
   sample program. The program and other CRC implementations can be
   tested with the test string "123456789" without the quotes. The
   results should be:

   CRC16        : BB3D
   CRC16 Modbus : 4B37
   CRC16 SICK   : 56A6
   CRC-CCITT    : 0x31C3 (starting value 0x0000)
   CRC-CCITT    : 0x29B1 (starting value 0xFFFF)
   CRC-CCITT    : 0xE5CC (starting value 0x1D0F)
   CRC-Kermit   : 0x8921
   CRC-DNP      : 82EA
   CRC32        : CBF43926



   The example program tst_crc.exe can be invoked in three ways:

   tst_crc -a

      The program will prompt for an input string. All characters in the
      input string are used for the CRC calculation, based on their ASCII
      value.

      Example input string: ABC
         CRC16              = 0x4521
         CRC16 (Modbus)     = 0x8550
         CRC16 (Sick)       = 0xC3C1
         CRC-CCITT (0x0000) = 0x3994
         CRC-CCITT (0xffff) = 0xF508
         CRC-CCITT (0x1d0f) = 0x2898
         CRC-CCITT (Kermit) = 0xE359
         CRC-DNP            = 0x5AD3
         CRC32              = 0xA3830348

   tst_crc -x

      The program will prompt for an input string. All characters will
      be filtered out, except for 0..9, a..f and A..F. The remaining characters
      will be paired, and every pair of two characters represent the hexadecimal
      value to be used for one byte in the CRC calculation. The result if an
      od number of valud characters is provided is undefined.

      Example input string: 41 42 43
         CRC16              = 0x4521
         CRC16 (Modbus)     = 0x8550
         CRC16 (Sick)       = 0xC3C1
         CRC-CCITT (0x0000) = 0x3994
         CRC-CCITT (0xffff) = 0xF508
         CRC-CCITT (0x1d0f) = 0x2898
         CRC-CCITT (Kermit) = 0xE359
         CRC-DNP            = 0x5AD3
         CRC32              = 0xA3830348

      You see, that the result is the same as for the ASCII input "ABC". This
      is, because A, B and C are represented in ASCII by the hexadecimal
      values 41, 42 and 43. So it is obvious that the result should be
      the same in both cases.

   tst_crc file1 file2 ...

      If neither the -a, nor the -x parameter is used, the test program
      assumes that the parameters are file names. Each file is opened and
      the CRC values are calculated.



   The newest version of these files can be found at:

        http://www.lammertbies.nl/download/lib_crc.zip

   On-line CRC calculations of strings can be performed at:

        http://www.lammertbies.nl/comm/info/crc-calculation.html

   Support for the CRC routines in this library in the Error Detection and
   Correction forum at

        http://www.lammertbies.nl/forum/viewforum.php?f=11*/


#define CRC_16    0x8005      //bit pattern (1)1000 0000 0000 0101

#define INIVAL_CRC_16 0x0000
#define INIVAL_CRC_16_SICK 0x0000
#define INIVAL_CRC_KERMIT 0x0000
#define INIVAL_CRC_DNP 0x0000
#define INIVAL_CRC_CCITT 0xFFFF
#define INIVAL_CRC_16_MODBUS 0xFFFF
#define CRC_16_INV   0xA001   //bit pattern (1)1010 0000 0000 0001
#define CRC_CCITT 0x1021      //bit pattern (1)0001 0000 0010 0001
#define CRC_CCITT_INV 0x8408      //bit pattern (1)0001 0000 0010 0001
#define CRC_DNP   0x3D65      //bit pattern (1)0011 1101 0110 0101
#define CRC_DNP_INV   0xA6BC     //bit pattern (1)0011 1101 0110 0101
#define bit_test(var,bit)   ((var) & ( 1<<(bit)))>>bit
#define bit_set(var,bit)     ((var)|= ((int) 1<<(bit)))
#define bit_clear(var,bit)     ((var)&=~((int) 1<<(bit)))



int calcula_mensaje_crc(char* packet_ptr);
//int8_t  generate_8bit_crc(char* data, int length, int8_t pattern);


//unsigned int generate_16bit_crc(char* data, unsigned int length, unsigned int pattern);
int calcula_CRC16(char datos[],long polinomio,long inival);
long CRC16(char value, long poly, long init_value, long exit_value);