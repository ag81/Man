/** @addtogroup LED_MODULE
*
* @{
* @file LEDs.h
* @brief La definicion de las funciones especificas de los GPIO para LEDs
*
* @version v1.0
* @date   	2012-11-23
*
* @note gpl2 license  2012, Andoni Galarraga
*
*
* @}
*/


#ifndef GPIOSEM_H_INCLUDED
#define GPIOSEM_H_INCLUDED

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


/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/

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
void GPIO_init();
void HW_Gpio_Main_ON(void);
void HW_Gpio_Main_OFF(void);
void HW_Gpio_LED_Eth_Green_ON();
void HW_Gpio_LED_Eth_Green_OFF();
void HW_Gpio_LED_Eth_Orange_ON();
void HW_Gpio_LED_Eth_Orange_OFF();

#endif // GPIOSEM_H_INCLUDED

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
