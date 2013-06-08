#include "utils/miniconsola/console.h"
#include "platformAbstraction/processor.h"
#include "platformAbstraction/LEDs.h"
#include "platformAbstraction/keypad.h"
//#include "platformAbstraction/sound.h"
#include "platformAbstraction/plat_uart.h"
#include "platformAbstraction/plat_timer.h"
#include "platformAbstraction/security.h"

#define ENVIO(valor) UARTSend((unsigned char *)valor,(unsigned long) sizeof(valor),0); \
					 UARTSend((unsigned char *)valor,(unsigned long) sizeof(valor),1);

#define ENVIO_P1(valor) UARTSend((unsigned char *)valor,(unsigned long) sizeof(valor),1);

#define PR(valor, x, y ) sprintf(str, "%d", valor); \
    	     	 	     consolePrintStr(x, y, str);

typedef struct
{	int pos_actual;
	unsigned char g_ucState;
	int sig_piso[4];
} tAscensor;

#define ESPERANDO 1
#define SUBIENDO 2
#define BAJANDO 3
#define ENPISO 4
#define ABRIENDO_PUERTAS 5
#define CERRANDO_PUERTAS 6
//#define REVISION '3'

#define PISO_00 0x30
#define PISO_11 0x31
#define PISO_22 0x32
#define PISO_33 0x33

#define NUM_PISOS 4

void read_inputs(void);
void ELEVATOR_Update(void);

