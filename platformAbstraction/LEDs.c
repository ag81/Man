/** @addtogroup LED_MODULE
*
* @{
* @file LEDs.c
* @brief La implementacion de las funciones especificas de los GPIO para LEDs
*
* @version v1.0
* @date   	2012-11-23
*
* @note gpl2 license  2012, Andoni Galarraga
*
*
* @}
*/

/*****************************************************************************
** 																			**
** MODULES USED 															**
** 																			**
****************************************************************************/
#include "LEDs.h"


/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
**********************************************************************/

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
 * @brief  Inicializa el GPIOF para el uso de los LEDs, cada uno con el pin correspondiente
 * @param void
 * @return void
 *
 */

void GPIO_init(){
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		 //LED-AK
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); //led de placa
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); //primer led del  rj45
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);//primer led del  rj45
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
}

/**
 * @brief  Cuando esta en verde se activa el LED "principal"
 * @param void
 * @return void
 *
 */

/*void HW_Gpio_greenON(){

	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_0);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_0);
}*/

/**
 * @brief  Cuando esta en ambar se activa uno de los LEDs del Ethernet
 * @param void
 * @return void
 *
 */

void HW_Gpio_LED_Eth_Green_ON(){

	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);

}

void HW_Gpio_LED_Eth_Green_OFF(){

	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);

}

void HW_Gpio_LED_Eth_Orange_ON(){
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);

}

void HW_Gpio_LED_Eth_Orange_OFF(){
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);

}

void HW_Gpio_Main_ON(void) {
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);


}

void HW_Gpio_Main_OFF(void) {
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
}
