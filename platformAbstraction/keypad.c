/** @addtogroup keypad_MODULE
*
* @{
* @file keypad.c
* @brief La implementacion de las funciones para interactuar con el keypad.
*
* @version v2.0
* @date   	2012-12-15
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

#define KEYPAD_C
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "keypad.h"

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

unsigned char g_ucKeypadSwitches = 0xf;
unsigned char g_ucSelectSwitch = 0x2;




/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
 * @brief  Inicializacaión del Keypad.
 *
 * @return     -
 *
 * Se inicializa el clock del GPIOE, para habilitar el keypad, y luego los pines correspondientes.
 *
*/

void KEYPAD_init(){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_0); /*pin 0*/
	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_0 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);
	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_1); /*pin 1*/
	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_1 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);
	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_2); /*pin 2*/
	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_2 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);
	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_3); /*pin 3*/
	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_3 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);
}

/**
 * @brief  Leer Switches del keypad
 *
 * @return     -
 *
 * Se lee el keypad y se guarda el valor del PIN pulsado.
*/

void ELEVATOR_readSwitches(){

	unsigned long pressed_data;

	pressed_data = (
			GPIOPinRead( GPIO_PORTE_BASE , (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3) )
			);


	g_ucKeypadSwitches = pressed_data;

}


void ELEVATOR_readSelect(void){

	unsigned long pressed_data;

	pressed_data = (
			GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1)
			);


	g_ucSelectSwitch = pressed_data;

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/







