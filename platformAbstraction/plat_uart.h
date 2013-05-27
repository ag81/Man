/** @addtogroup uart_MODULE
*
* @{
* @file plat_uart.h
* @brief La definicion de las funciones para interactuar con el UART.
*
* @version v2.0
* @date   	2012-12-16
*
* @note gpl2 license  2012, Andoni Galarraga
*
* @par VERSION HISTORY
* @note Version : 1
* @note Date : 2012-11-22
* @note Revised by : 	andoni.galarraga@alumni.eps.mondragon.edu
* @note Description : version inicial sin comentarios y sin estructura de carpetas adecuadas.
*
* @}
*/

/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"

/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/
#ifndef PLAT_UART_H_INCLUDED
#define PLAT_UART_H_INCLUDED

#define BAUD_RATE 9600
#define MAX_ELEMENTS 4

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/
void UART_init();
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount, int iBase);
void UARTRec();
void UARTRec_1();

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef PLAT_UART_C
#define PUB_PLAT_UART extern
#else
#define PUB_PLAT_UART
#endif
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
