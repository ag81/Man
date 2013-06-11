/** @addtogroup waitticks_MODULE
*
* @{
* @file waitticks.h
* @brief La definicion de las funciones del waittick.
*
* @version v2.0
* @date   	2012-11-23
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

#ifndef WAITTICK_H
#define WAITTICK_H

/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "driverlib/systick.h"
#include "../../platformAbstraction/plat_timer.h"



/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/

//#define CYCLES 10; //Dado que interrumpimos cada 0,25seg, cuando divide por 12 y "hondarra" sea 1 pasan 3 segundos

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

void init_WaitTick(void);
//void waitTick(void);


#endif // WAITTICK_H

/*****************************************************************************
 ** 																			**
 ** EOF 																		**
 ** 																			**
 ******************************************************************************/
