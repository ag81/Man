/**
*
* @{
* @file main.c
* @brief La implementacion de las funciones usadas por el main.
*
* @version v2.0
* @date   	2013-06-07
*
* @note gpl2 license  2012, Andoni Galarraga
*
* @par VERSION HISTORY
* @note Version : 1
* @note Date : 2012-02-03
* @note Revised by : 	andoni.galarraga@alumni.eps.mondragon.edu
* @note Description : version inicial sin comentarios y sin estructura de carpetas adecuadas.
*
* @}
*/

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "state_machine.h"
#include "state_machine_aux.h"

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

extern tAscensor miAscensor;

extern int g_selector;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

/**
 * @brief  Inicialización del Display.
 *
 * @return     -
 *
 * Se incializa el Display a usar.
 *
*/

void DISPLAY_init(void) {

	//
	// Se inicializa el Buffer auxiliar y el display de la placa usada.
	//
	initConsole();
	//
	// Se incluye el texto fijo a mostrar
	//
	consolePrintStr(2, 0, "_Asc v6.14b_16M_");
	consolePrintStr(2, 1, "----------------");
	refreshConsole();

}

/**
 * @brief  Inicialización de la estructura usada como buffer.
 *
 * @return     -
 *
 * Se incializa del Buffer a usar.
 *
*/

void init_structura(void){

	miAscensor.pos_actual = 0;
	miAscensor.g_ucState = ESPERANDO;
	miAscensor.sig_piso[0] = -5;
	miAscensor.sig_piso[1] = -5;
	miAscensor.sig_piso[2] = -5;
	miAscensor.sig_piso[3] = -5;
}

/**
 * @brief  Inicialización del HW del ascensor.
 *
 * @return     -
 *
 * Se inicializan los elementos de Hardware necesarios de la placa
 *
*/

void  ELEVATOR_HW_init(void) {

	//
	// Se inicializa el Procesador
	//
		PROCESSOR_init();
	//
	// Se inicializan los elementos GPIO usados (LEDs)
	//
		GPIO_init();

	//
	// Se inicializan los botones del keypad
	//
		KEYPAD_init();

	//
	// Se inicializa el envio por el UART
	//
		UART_init();

		init_Timer0(2);

		init_Timer2(2);

		init_Timer3(2);

	//
	// Se inicializan los elementos para el Display
	//
		DISPLAY_init();

		init_structura();

		init_WaitTick();

		ENVIO("v6.14b_16M\n\r")
}

/**
 * @brief  Ejecución principal del programa
 *
 * @return     -
 *
 * Ejecución principal del programa
 *
*/


int main(void)
{
	// se inicializa
	ELEVATOR_HW_init();

    while(1)
    {
    	switch(g_selector) {
    	case 0:	read_inputs();
    			break;
    	case 1: ELEVATOR_Update();
    			break;
    	default: break;
    	}
    }

    return 0;
}



/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/

