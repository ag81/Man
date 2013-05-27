/** @addtogroup generic_display_MODULE
*
* @{
* @file RIT_display.c
* @brief La implementacion de las funciones para el display, este caso para el display RIT de la Stellaris
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
* @note Description : Version inicial sin comentarios.
*
* @}
*/

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "utils/drivers/rit128x96x4.h"

/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
**********************************************************************/

#define FRECUENCY ((unsigned long)1000000)

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
 * @brief  Inicializa tanto los elementos logicos como los de plataforma.
 * @param void
 * @return void
 * @details Inicializa la nota inicial, el procesador, la botonera y el reproductor
 * de sonido
 */

void GENERIC_DISPLAY_init(){
	RIT128x96x4Init(FRECUENCY);
}

/**
 * @brief  Inicializa tanto los elementos logicos como los de plataforma.
 * @param void
 * @return void
 * @details Inicializa la nota inicial, el procesador, la botonera y el reproductor
 * de sonido
 */

void GENERIC_DISPLAY_stringDraw(const char *pcStr,
        					    unsigned long ulX,
        					    unsigned long ulY,
        					    unsigned char ucLevel){
	RIT128x96x4StringDraw(pcStr, ulX, ulY, ucLevel);
}

/**
 * @brief  Inicializa tanto los elementos logicos como los de plataforma.
 * @param void
 * @return void
 * @details Inicializa la nota inicial, el procesador, la botonera y el reproductor
 * de sonido
 */

void GENERIC_DISPLAY_imageDraw(const unsigned char *pucImage,
        					   unsigned long ulX,
        					   unsigned long ulY,
        					   unsigned long ulWidth,
        					   unsigned long ulHeight){
	RIT128x96x4ImageDraw(pucImage, ulX, ulY, ulWidth, ulHeight);
}
