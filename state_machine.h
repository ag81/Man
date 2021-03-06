/**
*
* @{
* @file state_machine.h
* @brief definición de cabeceras para state_machine.h
*
* @version v1.0
* @date   	2013-06-09
*
* @note gpl2 license  2012, Andoni Galarraga
*
* @}
*/

#ifndef STATE_MACHINE_H_INCLUDED
#define STATE_MACHINE_H_INCLUDED

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

#define ESPERANDO 1
#define SUBIENDO 2
#define BAJANDO 3
#define ENPISO 4
#define ABRIENDO_PUERTAS 5
#define CERRANDO_PUERTAS 6
#define CHECK_BUFFER 7

#define NUM_PISOS 4

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
void read_inputs(void);
void ELEVATOR_Update(void);

#endif // STATE_MACHINE_H_INCLUDED

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/

