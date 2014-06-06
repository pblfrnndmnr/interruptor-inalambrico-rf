/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#include <stdbool.h>
#include <stdint.h>        /* For uint8_t definition */


char cadenarecibida[]="\0\0\0\0\0";
bool recibi_datos=false;
#define Sincronizacion '\n'
#define DireccionDispositivo '1'
#define Encendido 'Y'
#define Apagado   'N'
unsigned char indice_de_dato=0;
bool Bandera_estado_llave=false;
bool pasaron_20ms=false;

//unsigned char datos_recibidos=0xFF; //inicio la variable datos_recibidos con un valor arbitrario
/*  Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/*  User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
