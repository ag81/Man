
/**
 *
 * @{
 * @file state_machine.h
 * @brief La declaración de las funciones usadas auxiliarmente por la state_machine.
 *
 * @version v2.0
 * @date   	2013-06-07
 *
 * @note gpl2 license  2012, Andoni Galarraga
 *
 * @par VERSION HISTORY
 * @note Version : 1
 * @note Date : 2012-02-03
 * @note Revised by : 	andoni.galarraga@alumni.eps.mondragon.edu
 * @note Description : version inicial sin comentarios y sin estructura de carpetas adecuadas.
 *
 * @}
 */

#ifndef STATE_MACHINE_AUX_H_INCLUDED
#define STATE_MACHINE_AUX_H_INCLUDED

/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/

#include "utils/miniconsola/console.h"
#include "platformAbstraction/processor.h"
#include "platformAbstraction/LEDs.h"
#include "platformAbstraction/keypad.h"
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

void llamada_registrada(void);
tBoolean comprobar_select(void);
void display_and_UART_Piso(void);

#endif // STATE_MACHINE_AUX_H_INCLUDED

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
