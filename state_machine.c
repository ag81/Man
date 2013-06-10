/**
 *
 * @{
 * @file state_machine.c
 * @brief La implementacion de las funciones usadas por la state_machine.
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

#include "state_machine.h"
#include "state_machine_aux.h"
#include "plant_simulator.h"

/*********************************************************************
 ** 																**
 ** GLOBAL VARIABLES 												**
 ** 																**
 *********************************************************************/


unsigned char g_ucState = ESPERANDO;
unsigned char g_ucCounter = 0;

tBoolean g_llamada;
tBoolean g_llamada_bool;

tBoolean g_escrito_and_enviado;
extern unsigned char g_ucKeypadSwitches;
extern unsigned char g_ucSelectSwitch;

unsigned char g_pressed_data = false;

tBoolean g_escrito;
tBoolean g_activado;
tBoolean g_activado_planta = false;
tBoolean g_primero_Int0 = false;
tBoolean g_enviado;

tBoolean g_primero;
tBoolean g_peticion;
tBoolean g_sensor_puerta_activado;

tBoolean g_pulsado = false;


extern int g_inputs[NUM_PISOS];
extern int g_inputs_imagen[NUM_PISOS];

tAscensor miAscensor;

tBoolean g_subida = false;
tBoolean g_bajada = false;

tBoolean g_open_door = false;
tBoolean g_close_door = false;

extern tBoolean g_open_door_limit;

/**
 * @brief Accion realizada en el estado ESPERANDO
 *
 * @return     -
 *
 * Accion realizada en el estado ESPERANDO
 *
 */

void ESPERANDO_accion (void)		{
	if (!g_escrito_and_enviado){
		eraseConsoleLine(9);
		consolePrintStr(3, 9,"En espera");
		refreshConsoleLine(9);
		g_escrito_and_enviado = true;
		ENVIO("En espera\n\r")
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

}

/**
 * @brief Evento para salir del estado ESPERANDO
 *
 * @return     -
 *
 * Evento para salir del estado ESPERANDO
 *
 */

void ESPERANDO_evento(void) {

	if (check_Security()) {
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
	}
}

/**
 * @brief Accion realizada en el estado SUBIENDO
 *
 * @return     -
 *
 * Accion realizada en el estado SUBIENDO
 *
 */

void SUBIENDO_accion (void){

	g_enviado = false;
	g_subida = true;
	if (!g_primero_Int0) {
		g_primero_Int0 = true;
		eraseConsoleLine(9);
		consolePrintStr(3, 9,"S R");
		refreshConsoleLine(9);
		ENVIO("S Rapida\n\r")
	}
	if (!g_escrito) {
		switch (miAscensor.pos_actual){
		case 0: //enable_Timer_0();
		consolePrintStr(3, 6, "Piso 0");
		ENVIO("P0\n\r")
		break;

		case 1: //enable_Timer_0();
		consolePrintStr(3, 6, "Piso 1");
		ENVIO("P1\n\r")
		break;

		case 2: //enable_Timer_0();
		consolePrintStr(3, 6, "Piso 2");
		ENVIO("P2\n\r")
		break;

		case 3: consolePrintStr(3, 6, "Piso 3");
		ENVIO("P3\n\r")
		break;

		default: break;
		}
		g_escrito = true;
	}
	refreshConsoleLine(6);
}

/**
 * @brief Evento para salir del estado SUBIENDO
 *
 * @return     -
 *
 * Evento para salir del estado SUBIENDO
 *
 */

void SUBIENDO_evento (void) {
	if (!g_escrito_and_enviado)
		display_and_UART_Piso();

	if (miAscensor.sig_piso[0] == miAscensor.pos_actual )
		g_ucState = ENPISO;
}

/**
 * @brief Accion realizada en el estado BAJANDO
 *
 * @return     -
 *
 * Accion realizada en el estado BAJANDO
 *
 */
void BAJANDO_accion (void){
	//IntEnable(INT_TIMER0A);
	g_enviado = false;
	g_bajada = true;
	if (!g_primero_Int0) {
		g_primero_Int0 = true;
		eraseConsoleLine(9);
		consolePrintStr(3, 9,"B R");
		refreshConsoleLine(9);
		ENVIO("B Rapida\n\r")
	}
	if (!g_escrito) {
		switch (miAscensor.pos_actual){
		case 0: consolePrintStr(3, 6, "Piso 0");
		ENVIO("P0\n\r")
		break;

		case 1: //enable_Timer_0();
		consolePrintStr(3, 6, "Piso 1");
		ENVIO("P1\n\r")
		break;

		case 2: //enable_Timer_0();
		consolePrintStr(3, 6, "Piso 2");
		ENVIO("P2\n\r")
		break;

		case 3: //enable_Timer_0();
		consolePrintStr(3, 6, "Piso 3");
		ENVIO("P3\n\r")
		break;

		default: break;
		}
		g_escrito = true;
	}
	refreshConsoleLine(6);
}

/**
 * @brief Evento para salir del estado BAJANDO
 *
 * @return     -
 *
 * Evento para salir del estado BAJANDO
 *
 */

void BAJANDO_evento() {

	if (!g_escrito_and_enviado)
		display_and_UART_Piso();

	if (miAscensor.sig_piso[0] == miAscensor.pos_actual ){
		g_primero = false;
		g_ucState = ENPISO;
	}
}

/**
 * @brief Accion realizada en el estado ENPISO
 *
 * @return     -
 *
 * Accion realizada en el estado ENPISO
 *
 */

void ENPISO_accion(void) {

	//IntDisable(INT_TIMER0A);

	g_subida = false;
	g_bajada = false;
	if (!g_escrito) {

		switch (miAscensor.pos_actual){
		case 0: consolePrintStr(3, 6, "Piso 0");
		ENVIO("P0\n\r")
		ENVIO_P1(PISO_0)
		break;

		case 1: //enable_Timer_0();
		consolePrintStr(3, 6, "Piso 1");
		ENVIO("P1\n\r")
		ENVIO_P1(PISO_1)
		break;

		case 2: //enable_Timer_0();
		consolePrintStr(3, 6, "Piso 2");
		ENVIO("P2\n\r")
		ENVIO_P1(PISO_2)
		break;

		case 3: //enable_Timer_0();
		consolePrintStr(3, 6, "Piso 3");
		ENVIO("P3\n\r")
		ENVIO_P1(PISO_3)
		break;

		default: break;
		}
		//ENVIO("En piso\n\r")
		//consolePrintStr(3, 9,"En piso");
		//refreshConsole();
		g_escrito = true;
		//enable_Timer_2();
	}
}

/**
 * @brief Evento para salir del estado ENPISO
 *
 * @return     -
 *
 * Evento para salir del estado ENPISO
 *
 */

void ENPISO_evento(void) {

	if (g_activado_planta)
		g_ucState = ABRIENDO_PUERTAS;
}

/**
 * @brief Accion realizada en el estado ABRIENDO_PUERTAS
 *
 * @return     -
 *
 * Accion realizada en el estado ABRIENDO_PUERTAS
 *
 */

void ABRIENDO_PUERTAS_accion(void) {

	g_activado_planta = false;
	g_open_door = true;

	if (!g_primero) {

		//enable_Timer_3();
		llamada_registrada();

		g_primero = true;

		switch (miAscensor.pos_actual){
		case 0: consolePrintStr(3, 6, "Piso 0");
		ENVIO("PB\n\r")
		break;

		case 1:	consolePrintStr(3, 6, "Piso 1");
		ENVIO("P1\n\r")
		break;

		case 2:	consolePrintStr(3, 6, "Piso 2");
		ENVIO("P2\n\r")
		break;

		case 3: consolePrintStr(3, 6, "Piso 3");
		ENVIO("P3\n\r")
		break;

		default: break;
		}

		ENVIO("Abre puer\n\r")
		consolePrintStr(3, 9,"Abriendo puertas");
		refreshConsole();
	}
}

/**
 * @brief Evento para salir del estado ABRIENDO_PUERTAS
 *
 * @return     -
 *
 * Evento para salir del estado ABRIENDO_PUERTAS
 *
 */

void ABRIENDO_PUERTAS_evento(void) {

	if (g_open_door_limit) {
		g_primero = false;
		g_activado = false;
		g_open_door = false;
		g_ucState = CERRANDO_PUERTAS;
	}
}

/**
 * @brief Accion realizada en el estado CERRANDO_PUERTAS
 *
 * @return     -
 *
 * Accion realizada en el estado CERRANDO_PUERTAS
 *
 */

void CERRANDO_PUERTAS_accion(void) {
	g_open_door_limit = false;
	consolePrintStr(3, 9,"Cerrando puertas");
	refreshConsole();
	ENVIO("Cierra puer\n\r")

}

/**
 * @brief Evento para salir del estado CERRANDO_PUERTAS
 *
 * @return     -
 *
 * Evento para salir del estado CERRANDO_PUERTAS
 *
 */

void CERRANDO_PUERTAS_evento(void) {

	volatile int i;
	tBoolean pulsado;

	for (i=0; i<600000; i++) {

		if (g_pulsado) {

			ENVIO("Sens puerta act\n\r")
					pulsado = false;

			g_sensor_puerta_activado = true;
			g_ucState = ABRIENDO_PUERTAS;
			break;
		}
	}
	g_escrito_and_enviado = false;
	g_ucState = ESPERANDO;

}

/**
 * @brief Función que actualiza el estado del ascensor ejecutado periódicamente
 *
 * @return     -
 *
 * Función que actualiza el estado del ascensor ejecutado periódicamente
 *
 */

void state_machine_execute(void) {

	switch (g_ucState) {

	case ESPERANDO: 		ESPERANDO_accion();

	ESPERANDO_evento();

	break;

	case SUBIENDO:			SUBIENDO_accion();

	SUBIENDO_evento();

	break;

	case BAJANDO: 			BAJANDO_accion();

	BAJANDO_evento();

	break;

	case ENPISO:			ENPISO_accion();

	ENPISO_evento();

	case ABRIENDO_PUERTAS:	ABRIENDO_PUERTAS_accion();

	ABRIENDO_PUERTAS_evento();

	break;

	case CERRANDO_PUERTAS:	CERRANDO_PUERTAS_accion();

	CERRANDO_PUERTAS_evento();

	break;

	default:				break;

	}
}

void ELEVATOR_Update(void) {

	state_machine_execute();
	plant_simulator_execute();
}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
