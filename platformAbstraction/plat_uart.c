/** @addtogroup uart_MODULE
*
* @{
* @file plat_uart.c
* @brief La implementacion de las funciones para interactuar con el UART.
* Configuracion:
* 	<ul>
 *  	<li>9600 bps </li>
 *  	<li>8 bits de datos </li>
 *  	<li>Paridad: Par (Even)</li>
 *  	<li>Bit parada: 2 </li>
 *  	<li>Ctrl Flujo: Nada</li>
 *  </ul>
*
* @version v2.0
* @date   	2012-12-16
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

#define PLAT_UART_C
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "plat_uart.h"

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/
tBoolean g_peticion = false;
unsigned char g_ucKeypadSwitches;
char c, str_buf[MAX_ELEMENTS];
 int i, nChars=0;


/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
 * @brief  Se inicializan los elementos para usar el UART
 * @param void
 * @return void
 * @details
 *
 */
void UART_init() {
	 SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_8MHZ);
	 SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	 SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

	 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	 GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	 GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_2 | GPIO_PIN_3);

	 UARTDisable(UART0_BASE);

	 UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), BAUD_RATE,
	 		              (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_TWO |UART_CONFIG_PAR_EVEN));
	 UARTEnable(UART0_BASE);

	 UARTDisable(UART1_BASE);

	 UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), BAUD_RATE,
	 	 		              (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_TWO |UART_CONFIG_PAR_EVEN));
	 UARTEnable(UART1_BASE);


	 UARTSend((unsigned char *)"\n\r.Ascensor.\n\r",(unsigned long) sizeof("\n\r.Ascensor.\n\r"), 0);
	 UARTSend((unsigned char *)"\n\r.Ascensor.\n\r",(unsigned long) sizeof("\n\r.Ascensor.\n\r"), 1);


}

/**
 * @brief  Se envia la cadena de texto mediante UART
 * @param pucBuffer puntero a la cadena de texto a enviar
 * @param ulCount cantidad de caracteres a enviar
 * @return void
 * @details Envia el numero de caracteres indicados en el segundo parametro (hasta 16)
 */
/*void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount) {

	//
    // Loop while there are more characters to send.
    //
    while(ulCount--)
    {
        //
        // Write the next character to the UART.
        //
        UARTCharPutNonBlocking(UART0_BASE, *pucBuffer++);
    }
}*/

/**
 * @brief  Se envia la cadena de texto mediante UART
 * @param pucBuffer puntero a la cadena de texto a enviar
 * @param ulCount cantidad de caracteres a enviar
 * @return void
 * @details Envia el numero de caracteres indicados en el segundo parametro (hasta 16)
 */
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount, int iBase) {

	//
    // Loop while there are more characters to send.
    //
	if (iBase == 0) {
    while(ulCount--)
    {
        //
        // Write the next character to the UART.
        //
        UARTCharPutNonBlocking(UART0_BASE, *pucBuffer++);
    }
	}
    else if (iBase == 1) {
    	while(ulCount--)
    	    {
    	        //
    	        // Write the next character to the UART.
    	        //
    	        UARTCharPutNonBlocking(UART1_BASE, *pucBuffer++);
    	    }
    }
}

void UARTRec() {

	//
    // Loop while there are more characters to send.
    //
      //
        // Write the next character to the UART.
        //
	 if(UARTCharsAvail(UART0_BASE))
		  //{
		 	// ;
		 	 {		g_ucKeypadSwitches = (char)UARTCharGetNonBlocking(UART0_BASE);
		 		    c = g_ucKeypadSwitches;
		 		    if(nChars==MAX_ELEMENTS-1) for(i=0;i<nChars-1;i++) str_buf[i]=str_buf[i+1];
		 		    else nChars++;
		 		    str_buf[nChars-1]=c;

		 		   // consolePrintStr(3,2, str);
		 		   // refreshConsoleLine(2);
		 		 //   g_peticion = true;
		 		    //c=toupper(c);
		 		    //UARTCharPutNonBlocking(UART0_BASE, c);
		 		  }
		 		  else
		 		  {
		 			/*refresh=0;
		 		    consolePrintStr(3,2, str);
		 		    refreshConsoleLine(2);*/
		 		//	g_peticion = false;
		 		  }
	 //  UARTDisable(UART1_BASE);
	// UARTDisable(UART0_BASE);

	 if (g_ucKeypadSwitches!= 0xf)
	 		 g_peticion = true;
	 	 else
	 		 g_peticion = false;
}

void UARTRec_1() {

	//
    // Loop while there are more characters to send.
    //
      //
        // Write the next character to the UART.
        //
	 if(UARTCharsAvail(UART1_BASE))
		  //{
		 	// ;
		 	 {		g_ucKeypadSwitches = (char)UARTCharGetNonBlocking(UART1_BASE);
		 		    c = g_ucKeypadSwitches;
		 		    if(nChars==MAX_ELEMENTS-1) for(i=0;i<nChars-1;i++) str_buf[i]=str_buf[i+1];
		 		    else nChars++;
		 		    str_buf[nChars-1]=c;

		 		  //  consolePrintStr(3,2, str);
		 		 //   refreshConsoleLine(2);
		 		    		//    g_peticion = true;
		 		    //c=toupper(c);
		 		    //UARTCharPutNonBlocking(UART0_BASE, c);
		 		  }
		 		  else
		 		  {
		 			/*refresh=0;
		 		    consolePrintStr(3,2, str);
		 		    refreshConsoleLine(2);*/
		 			//g_peticion = false;
		 		  }
	 //UARTDisable(UART0_BASE);
	 //UARTDisable(UART0_BASE);

	 if (g_ucKeypadSwitches!= 0xf)
		 g_peticion = true;
	 else
		 g_peticion = false;
}

void UARTRec_2() {

	//
    // Loop while there are more characters to send.
    //
      //
        // Write the next character to the UART.
        //
	 if(UARTCharsAvail(UART1_BASE))
		  //{
		 	// ;
		 	 {		g_ucKeypadSwitches = (char)UARTCharGetNonBlocking(UART1_BASE);
		 		    c = g_ucKeypadSwitches;
		 		    if(nChars==MAX_ELEMENTS-1) for(i=0;i<nChars-1;i++) str_buf[i]=str_buf[i+1];
		 		    else nChars++;
		 		    str_buf[nChars-1]=c;

		 		   // consolePrintStr(2,2, str_buf);
		 		   // refreshConsoleLine(2);
		 		    //c=toupper(c);
		 		    //UARTCharPutNonBlocking(UART0_BASE, c);
		 		  }
		 		  else
		 		  {
		 			//refresh=0;
		 		  //  refreshConsoleLine(2);
		 		  }
	 if (g_ucKeypadSwitches!= 0xf)
	 		 g_peticion = true;
	 	 else
	 		 g_peticion = false;
}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/







