/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
//Defino si se usa tecla o pulsador para comandar el sistema
//Si se usa tecla, se debe verificar el flanco de subida y vajada del RB0


#define UsaTecla

//#define TE_HT12E PORTBbits.RB2
#define TransmisorON PORTBbits.RB3

#define DireccionDispositivo '1'
#define Encendido 'Y'
#define Apagado   'N'

unsigned char datos=Apagado;
/*  Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/*  User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
