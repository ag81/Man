
/** @addtogroup console_MODULE
*
* @{
* @file console.c
* @brief Implementacion de las funciones del Buffer de texto para manejar de manera generica el display
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

/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "console.h"


/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
char consoleImage[MAX_LINES][MAX_COLUMNS+1];


/*********************************************************************
** 																	**
** EXPORTED FUNCTIONS 												**
** 																	**
**********************************************************************/

/**
 * @brief  Inicializa tanto al array temporal usado como la pantalla fisica usada segun la plataforma
 * @param void
 * @return void
 *
 */
void initConsole(void)
{
  int i,j;

  GENERIC_DISPLAY_init();
  for(i=0;i<MAX_LINES;i++)
  {
    for(j=0;j<MAX_COLUMNS;j++) consoleImage[i][j]=' ';
	  consoleImage[i][MAX_COLUMNS]='\0';
  }
}

/**
 * @brief  Introduce la cadena de caracteres en el buffer auxiliar
 * @param void
 * @return void
 *
 */
void consolePrintStr(int x, int y, char* str)
{
  int n;

  n=strlen(str);
  if(n>(MAX_COLUMNS-x)) n=MAX_COLUMNS-x;
  strncpy(consoleImage[y]+x,str,n);
}

/**
 * @brief  Refresca el display generico, segun lo incluido en el buffer auxiliar
 * @param void
 * @return void
 *
 */
void refreshConsole(void)
{
  int y;

  for(y=0;y<MAX_LINES;y++)
	  GENERIC_DISPLAY_stringDraw(consoleImage[y], 0, y*LINE_HEIGHT, 15);

}

/**
 * @brief  Refresca una linea del display generico, segun lo incluido en el buffer auxiliar
 * @param void
 * @return void
 *
 */
void refreshConsoleLine(int y)
{
	GENERIC_DISPLAY_stringDraw(consoleImage[y], 0, y*LINE_HEIGHT, 15);
}

/**
 * @brief  Se borra la información de la posicion seleccionada en el buffer
 * @param void
 * @return void
 *
 */
void eraseConsoleLine(int y)
{
  int j;

  for(j=0;j<MAX_COLUMNS;j++) consoleImage[y][j]=' ';
}
