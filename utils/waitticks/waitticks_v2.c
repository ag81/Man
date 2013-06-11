/** @addtogroup waitticks_MODULE
*
* @{
* @file waitticks_v2.c
* @brief La implementacion de las funciones del waittick.
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

/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/

#include "waitticks.h"

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

static unsigned int contador;

int g_selector;

#define CICLOS 4

/*********************************************************************
** 																	**
** EXPORTED FUNCTIONS 												**
** 																	**
**********************************************************************/

/**
 * @brief  Inicializa los ticks, configurando el periodo con el que se realizara
 * @param void
 * @return void
 *
 */
void init_WaitTick(void) {
	// periodo=25 ms seg Programamos el period del Ticka 400.000 -> CPU a 16 Mhz, interrumpe cada 25ms.

	SysTickPeriodSet(400000);
	// Habilitar para que provoque interrupciones
	SysTickIntEnable();
	SysTickEnable();
	IntMasterEnable();
	contador = 0;
}



/**
 * @brief Funcion que salta cuando se ejecuta la interrupcion, segun la configuracion de micro y periodo de ciclos
 * sera cada 25ms.
 * @param void
 * @return void
 * @details En startup_lm3.c hay que definir esta funcion como extern, para que sepa que la implementamos nosotros.
 */

void SysTickInt_Handler(void) {
	contador++;
	if (contador %4 == 0)
		g_selector = 0;
	else if(contador %4 == 1)
		g_selector = 1;
	else if (contador % 4 == 2 || contador % 4 ==3)
		g_selector = 2;
	}
