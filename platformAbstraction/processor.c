/** @addtogroup processor_MODULE
*
* @{
* @file processor.c
* @brief La implementacion de las funciones especificas del procesador
*
* @version v1.0
* @date   	2012-11-23
*
* @note gpl2 license  2012, Andoni Galarraga
*
*
* @}
*/


/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "processor.h"


/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
**********************************************************************/

/*********************************************************************
** 																	**
** TYPEDEFS AND STRUCTURES 											**
** 																	**
**********************************************************************/

/*********************************************************************
** 																	**
** PROTOTYPES OF LOCAL FUNCTIONS 									**
** 																	**
*********************************************************************/

/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/

/*********************************************************************
** 																	**
** EXPORTED FUNCTIONS 												**
** 																	**
**********************************************************************/

/**
 * @brief  Inicializa el procesador con los parametros convenientes
 * @param void
 * @return void
 *
 */
void PROCESSOR_init(void){
         //125ns
         SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
}

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/


/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
