#include "Manchester.h"
#include <string.h>


 int  Manchester (char cadena_v) {
        // Devuelve 2 cuando hay señal positiva
        // Devuelve 0 cuando hay señal negativa
        // si es cero devuelve señal + y señal -
        // si es uno devuelve señal - y señal +

       int temporal=0;

        for (int i=0; i <=7; i++) {
            if ((cadena_v&(0x01<<i)) == 0) {
                            
               temporal = temporal+ 0b10;
               
            }
            else {
                
               temporal = temporal+ 0b01;
                

            }
            if (i<=6){
                temporal=temporal<<2;
            }}
        //System.out.println(temporal);
        return temporal;
    }