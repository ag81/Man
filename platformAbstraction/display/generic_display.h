/** @addtogroup generic_display_MODULE
*
* @{
* @file generic_display.h
* @brief La definicion de las funciones para el display, genericas. Esta cabecera valdra para todos los sistemas
* variara la implementacion segun el archivo .c compilado.
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
* @note Description : Version inicial sin comentarios
*
* @}
*/

#ifndef _GENERIC_DISPLAY_H
#define _GENERIC_DISPLAY_H

/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/

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


 void GENERIC_DISPLAY_init(void);
 void GENERIC_DISPLAY_stringDraw(const char *pcStr,
	    							   unsigned long ulX,
	    							   unsigned long ulY,
	    							   unsigned char ucLevel);
 void GENERIC_DISPLAY_imageDraw(const unsigned char *pucImage,
		   	   	   	   	   	   	      unsigned long ulX,
		   	   	   	   	   	   	      unsigned long ulY,
		   	   	   	   	   	   	      unsigned long ulWidth,
		   	   	   	   	   	   	      unsigned long ulHeight);

#endif // GENERIC_DISPLAY_H

 /*****************************************************************************
 ** 																			**
 ** EOF 																		**
 ** 																			**
 ******************************************************************************/
