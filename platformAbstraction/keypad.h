/** @addtogroup keypad_MODULE
*
* @{
* @file keypad.h
* @brief La definicion de las funciones para interactuar con el keypad.
*
* @version v2.0
* @date   	2012-12-15
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

/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/
#ifndef KEYPAD_H_INCLUDED
#define KEYPAD_H_INCLUDED


#define PISO_0 0xe    //1110
#define PISO_1 0x7    //1101
#define PISO_2 0xd    //1011
#define PISO_3 0xb    //0111


/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/
void KEYPAD_init();
void ELEVATOR_readSwitches();
void ELEVATOR_readSelect(void);


/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef KEYPAD_C
#define PUB_KEYPAD extern
#else
#define PUB_KEYPAD
#endif
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
