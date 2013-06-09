/**
*
* @{
* @file state_machine.h
* @brief definición de cabeceras para state_machine.h
*
* @version v1.0
* @date   	2013-06-09
*
* @note gpl2 license  2012, Andoni Galarraga
*
* @}
*/

#ifndef STATE_MACHINE_H_INCLUDED
#define STATE_MACHINE_H_INCLUDED

/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "utils/miniconsola/console.h"
#include "platformAbstraction/processor.h"
#include "platformAbstraction/LEDs.h"
#include "platformAbstraction/keypad.h"
//#include "platformAbstraction/sound.h"
#include "platformAbstraction/plat_uart.h"
#include "platformAbstraction/plat_timer.h"
#include "platformAbstraction/security.h"

/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/

#define ENVIO(valor) UARTSend((unsigned char *)valor,(unsigned long) sizeof(valor),0); \
					 UARTSend((unsigned char *)valor,(unsigned long) sizeof(valor),1);

#define ENVIO_P1(valor) UARTSend((unsigned char *)valor,(unsigned long) sizeof(valor),1);

#define PR(valor, x, y ) sprintf(str, "%d", valor); \
    	     	 	     consolePrintStr(x, y, str);

#define ESPERANDO 1
#define SUBIENDO 2
#define BAJANDO 3
#define ENPISO 4
#define ABRIENDO_PUERTAS 5
#define CERRANDO_PUERTAS 6

#define NUM_PISOS 4

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/

typedef struct
{	int pos_actual;
	unsigned char g_ucState;
	int sig_piso[4];
} tAscensor;

/*****************************************************************************
**								 											**
** EXPORTED VARIABLES 														**
** 																			**
******************************************************************************/

/*****************************************************************************
**					 														**
** EXPORTED FUNCTIONS 														**
** 																			**
******************************************************************************/
void read_inputs(void);
void ELEVATOR_Update(void);

#endif // STATE_MACHINE_H_INCLUDED

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/

