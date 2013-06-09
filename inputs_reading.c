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

#include "inputs_reading.h"
#include "state_machine.h"

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

extern unsigned char g_ucKeypadSwitches;

extern tAscensor miAscensor;


int g_inputs[NUM_PISOS] = {0, 0, 0, 0};
int g_inputs_imagen[NUM_PISOS] = {0, 0, 0, 0};

/*********************************************************************
** 																	**
** GLOBAL FUNCTIONS 												**
** 																	**
**********************************************************************/

/**
 * @brief Se pasa de la pulsación del botón al buffer de llamadas.
 *
 * @return     -
 *
 * Se pasa de la pulsación del botón al buffer de llamadas.
 *
*/

void real_to_array(void) {


	switch(g_ucKeypadSwitches) {

		case PISO_0:	g_inputs[0] = 1;
						break;

		case PISO_1:	g_inputs[1] = 1;
						break;

		case PISO_2:	g_inputs[2] = 1;
						break;

		case PISO_3:	g_inputs[3] = 1;
						break;

		case PISO_00:	g_inputs[0] = 1;
								break;

		case PISO_11:	g_inputs[1] = 1;
								break;

		case PISO_22:	g_inputs[2] = 1;
								break;

		case PISO_33:	g_inputs[3] = 1;
								break;

		default:		break;
	}
}

/**
 * @brief Se pasa del array inicial al array imagen
 *
 * @return     -
 *
 * Se pasa del array inicial al array imagen
 *
*/

void array_to_image(void) {
	int i;

	for (i=0;i < NUM_PISOS; i++) {
		if (g_inputs[i] == 1) {

				g_inputs_imagen[i] = 1;
				g_inputs[i] = 0;
		}
	}

}

/**
 * @brief Leer los switches o pulsación de botones
 *
 * @return     -
 *
 * Leer los switches o pulsación de botones
 *
*/

void read_switches(void){

	unsigned char pressed_data;

	pressed_data = (
			GPIOPinRead( GPIO_PORTE_BASE , (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3))
			);


	g_ucKeypadSwitches = pressed_data;

}

/**
 * @brief Se registra la llamada encendiendo el LED
 *
 * @return     -
 *
 * Se registra la llamada encendiendo el LED
 *
*/
void registrar_llamada(void) {
	char str[16];
	int i;
	int j = 0;
	tBoolean incluido = false;
	for (i=0;i < 4; i++) {

		if (g_inputs[i] == 1) {

			while ((j < 4) && (!incluido)) {
				if ((miAscensor.sig_piso[j] == -5) && (j==0)) {
					miAscensor.sig_piso[j] = i;
					incluido = true;
					g_inputs[i] = 0;
					HW_Gpio_Main_ON();

				}
				else if ((miAscensor.sig_piso[j] == -5) && (j>0)){
					if (miAscensor.sig_piso[j-1] != i)
					{
						miAscensor.sig_piso[j] = i;
						g_inputs[i] = 0;
						HW_Gpio_Main_ON();
						HW_Gpio_LED_Eth_Green_ON();
						//incluido = true;
					}
					incluido = true;
					g_inputs[i] = 0;

				}
				j++;
			}


		}
	}
	eraseConsoleLine(3);
	for (i=0; i<4; i++) {
		if (miAscensor.sig_piso[i] != -5) {
			PR (miAscensor.sig_piso[i], 2*i+1, 3)
		}
	}
	refreshConsole();
}

/**
 * @brief Función general de leer entradas que se ejecuta periodicamente
 *
 * @return     -
 *
 * Función general de leer entradas que se ejecuta periodicamente
 *
*/

void read_inputs(void) {

	read_switches();
	UARTRec();
	UARTRec_2();
	if (g_ucKeypadSwitches != 0xf)
			real_to_array();
	registrar_llamada();
}
