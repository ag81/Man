/** @addtogroup console_MODULE
*
* @{
* @file console.h
* @brief Definicion de las funciones del Buffer de texto para manejar de manera generica el display
*
* @version v2.0
* @date   	2012-12-15
*
* @note gpl2 license  2012, Andoni Galarraga
*
* @par VERSION HISTORY
* @note Version : 1
* @note Date : 2012-12-11
* @note Revised by : 	andoni.galarraga@alumni.eps.mondragon.edu
* @note Description : version inicial sin comentarios y sin estructura de carpetas adecuadas.
*
* @}
*/
#ifndef CONSOLE_H
#define CONSOLE_H

/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "console.h"
#include <stdio.h>
#include <string.h>
#include "platformAbstraction/display/generic_display.h"

/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/

#define MAX_COLUMNS 21
#define MAX_LINES 12

#define CHAR_WIDTH 6
#define LINE_HEIGHT 8

/*********************************************************************
** 																	**
** TYPEDEFS AND STRUCTURES 											**
** 																	**
**********************************************************************/

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
void initConsole(void);
void refreshConsole(void);
void consolePrintStr(int x, int y, char* str);
void refreshConsoleLine(int y);
void eraseConsoleLine(int y);

#endif //CONSOLE_H

/*****************************************************************************
 ** 																			**
 ** EOF 																		**
 ** 																			**
 ******************************************************************************/
