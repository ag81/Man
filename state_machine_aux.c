
/**
 *
 * @{
 * @file state_machine.c
 * @brief La implementacion de las funciones usadas auxiliarmente por la state_machine.
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
 ** 																**
 **********************************************************************/

#include "state_machine_aux.h"
#include "state_machine.h"

/*********************************************************************
 ** 																**
 ** GLOBAL VARIABLES 												**
 ** 																**
 *********************************************************************/

extern tAscensor miAscensor;
extern unsigned char g_ucSelectSwitch;

extern tBoolean g_llamada_bool;
extern tBoolean g_escrito;
extern unsigned char g_ucState;
extern tBoolean g_primero_Int0;

/*********************************************************************
 ** 																**
 ** GLOBAL FUNCTIONS 												**
 ** 																**
 **********************************************************************/

/**
 * @brief Se registra la llamada encendiendo el LED
 *
 * @return     -
 *
 * Se registra la llamada encendiendo el LED
 *
 */

void llamada_registrada(void){

	int i;

	for (i=0; i<3;i++) {

		miAscensor.sig_piso[i] = miAscensor.sig_piso[i+1];

	}
	miAscensor.sig_piso[3] = -5;
	HW_Gpio_Main_OFF();

}

/**
 * @brief Se comprueba la simulación para el sensor de puertas
 *
 * @return     -
 *
 * Se comprueba la simulación para el sensor de puertas
 *
 */

tBoolean comprobar_select(void) {

	ELEVATOR_readSelect();

	if (g_ucSelectSwitch != 0x2)
		return true;
	else
		return false;
}

/**
 * @brief Se muestra el piso y se envía por UART la información
 *
 * @return     -
 *
 * Se muestra el piso y se envía por UART la información
 *
 */

void display_and_UART_Piso(void) {

	switch (miAscensor.pos_actual){
	case 0:
		consolePrintStr(3, 6, "Piso 0");
		ENVIO("PB\n\r")
		break;

	case 1:
		consolePrintStr(3, 6, "Piso 1");
		ENVIO("P1\n\r")
		break;

	case 2:
		consolePrintStr(3, 6, "Piso 2");
		ENVIO("P2\n\r")
		break;

	case 3: consolePrintStr(3, 6, "Piso 3");
	ENVIO("P3\n\r")
	break;

	default: break;
	}
	refreshConsole();
}

/**
 * @brief Se comprueba de que el buffer tiene una llamada pendiente
 *
 * @return     -
 *
 * Se comprueba de que el buffer tiene una llamada pendiente
 *
 */
void comprobar_buffer_llamadas(void) {

	if (miAscensor.sig_piso[0] != -5) {
			g_llamada_bool = true;
			HW_Gpio_LED_Eth_Green_OFF();
			HW_Gpio_Main_ON();

		}
		if ( miAscensor.sig_piso[0] > miAscensor.pos_actual ) {
			if (g_llamada_bool) {
				g_llamada_bool = false;
				g_escrito = false;
				g_primero_Int0 = false;
				g_ucState = SUBIENDO;

			}
		}
		else if (miAscensor.sig_piso[0] < miAscensor.pos_actual) {
			if (g_llamada_bool) {
				g_llamada_bool = false;
				g_escrito = false;
				g_primero_Int0 = false;
				g_ucState = BAJANDO;

			}
		}
		/*if (g_ucState == SUBIENDO || g_ucState == BAJANDO)
				return true;
		else return false;*/

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
