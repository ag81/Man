
#include "utils/miniconsola/console.h"

#include "platformAbstraction/processor.h"
#include "platformAbstraction/LEDs.h"
#include "platformAbstraction/keypad.h"
//#include "platformAbstraction/sound.h"
#include "platformAbstraction/plat_uart.h"
#include "platformAbstraction/plat_timer.h"
#include "platformAbstraction/security.h"

#define ENVIO(valor) UARTSend((unsigned char *)valor,(unsigned long) sizeof(valor),0); \
					 UARTSend((unsigned char *)valor,(unsigned long) sizeof(valor),1);

#define ENVIO_P1(valor) UARTSend((unsigned char *)valor,(unsigned long) sizeof(valor),1);

#define PR(valor, x, y ) sprintf(str, "%d", valor); \
    	     	 	     consolePrintStr(x, y, str);

// ..4AAAAAA4..
// .4AAAAAAAA4.
// 4AAAAAAAAAA4
// 4AAAAAAAAAA4
// 4AAAAAAAAAA4
// 4AAAAAAAAAA4
// .4AAAAAAAA4.
// ..4AAAAAA4.

const unsigned char g_pucNada[60]  =  {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
const unsigned char g_pucCirc[60]  =  {
        0x00, 0x00, 0x44, 0x44, 0x00, 0x00,
        0x00, 0x4a, 0xaa, 0xaa, 0xa4, 0x00,
        0x04, 0xaa, 0xaa, 0xaa, 0xaa, 0x40,
        0x4a, 0xaa, 0x00, 0x00, 0xaa, 0xa4,
        0x4a, 0xaa, 0x00, 0x00, 0xaa, 0xa4,
        0x4a, 0xaa, 0x00, 0x00, 0xaa, 0xa4,
        0x4a, 0xaa, 0x00, 0x00, 0xaa, 0xa4,
        0x04, 0xaa, 0xaa, 0xaa, 0xaa, 0x40,
        0x00, 0x4a, 0xaa, 0xaa, 0xa4, 0x00,
        0x00, 0x00, 0x44, 0x44, 0x00, 0x00
    };

#define ESPERANDO 1
#define SUBIENDO 2
#define BAJANDO 3
#define ENPISO 4
#define ABRIENDO_PUERTAS 5
#define CERRANDO_PUERTAS 6
//#define REVISION '3'

#define PISO_00 0x30
#define PISO_11 0x31
#define PISO_22 0x32
#define PISO_33 0x33

#define NUM_PISOS 4

//void SEMAPHORE_init(void);
//void SEMAPHORE_task(void);


unsigned char g_ucState = ESPERANDO;
unsigned char g_ucCounter = 0;
//unsigned char g_revision = REVISION;

tBoolean g_llamada;
tBoolean g_llamada_bool;
//int g_posicion = 0;

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

int g_inputs[NUM_PISOS] = {0, 0, 0, 0};
int g_inputs_imagen[NUM_PISOS] = {0, 0, 0, 0};

typedef struct
{	int pos_actual;
	unsigned char g_ucState;
	int sig_piso[4];
} tAscensor;

tAscensor miAscensor;


void llamada_registrada(void){

	int i;

	for (i=0; i<3;i++) {

				miAscensor.sig_piso[i] = miAscensor.sig_piso[i+1];

			}
			miAscensor.sig_piso[3] = -5;
			HW_Gpio_Main_OFF();
			//HW_Gpio_LED_Eth_Green_OFF();
}



void getPiso() {



	switch(g_ucKeypadSwitches ) {

	case PISO_0:
					 miAscensor.sig_piso[0] = 0;
		 	 	 	 g_llamada_bool = true;
		 	 	 	 break;
	case PISO_00:	 miAscensor.sig_piso[0] = 0;
			 	 	 g_llamada_bool = true;
			 	 	 break;

	case PISO_1:
					 miAscensor.sig_piso[0] = 1;
			 	 	 g_llamada_bool = true;
			 	 	 break;
	case PISO_11:	 miAscensor.sig_piso[0] = 1;
				 	 g_llamada_bool = true;
				 	 break;

	case PISO_2:
					 miAscensor.sig_piso[0] = 2;
		 	 	 	 g_llamada_bool = true;
		 	 	 	 break;
	case PISO_22:	 miAscensor.sig_piso[0] = 2;
			 	 	 g_llamada_bool = true;
			 	 	 break;

	case PISO_3:
					 miAscensor.sig_piso[0] = 3;
		 	 	     g_llamada_bool = true;
		 	 	     break;
	case PISO_33:	 miAscensor.sig_piso[0] = 3;
			 	 	 g_llamada_bool = true;
			 	 	 break;

		default:	 if (!g_escrito_and_enviado)
						//display_and_UART_Piso();

					 g_llamada_bool = false;
	}
}

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

void array_to_image(void) {
	int i;

	for (i=0;i < NUM_PISOS; i++) {
		if (g_inputs[i] == 1) {

				g_inputs_imagen[i] = 1;
				g_inputs[i] = 0;
		}
	}

}

void read_switches(){
	char str[16];

	unsigned char pressed_data;

	pressed_data = (
			GPIOPinRead( GPIO_PORTE_BASE , (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3))
			);


	g_ucKeypadSwitches = pressed_data;


	/*eraseConsoleLine(4);
	sprintf(str, "key %u", g_pressed_data);
	consolePrintStr(6, 4, str);
	refreshConsole();*/



	//array_to_image();
}


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

void read_inputs(void) {

	read_switches();
	UARTRec();
	UARTRec_2();
	if (g_ucKeypadSwitches != 0xf)
			real_to_array();
	registrar_llamada();
}

void leer_array_imagen() {
	int i;
	for (i=0;i<NUM_PISOS;i++) {
		if (g_inputs_imagen[i] == 1) {
			miAscensor.sig_piso[0] = i;
			g_llamada_bool = true;
		}
		else g_llamada_bool = false;
	}
}

tBoolean comprobar_select() {

	ELEVATOR_readSelect();

	if (g_ucSelectSwitch != 0x2)
				return true;
			else
				return false;


	//espera(TIEMPO3);

}

void display_and_UART_Piso() {

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


void
Timer3IntHandler(void)
{
	//char str[1];
    //
    // Clear the timer interrupt.
    //
    TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Update the interrupt status on the display.
    //
    IntDisable(INT_TIMER3A);

   // g_cont_abre_puertas++;
    g_activado = true;
    g_escrito = false;

    /*sprintf(str, "%d", miAscensor.pos_actual);
    consolePrintStr(6,4,str);
    refreshConsoleLine(4);*/

    IntEnable(INT_TIMER3A);
}


void
Timer2IntHandler(void)
{
	//char str[1];
    //
    // Clear the timer interrupt.
    //
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Update the interrupt status on the display.
    //
    IntDisable(INT_TIMER2A);

   // g_cont_abre_puertas++;
    g_activado_planta = true;


    /*sprintf(str, "%d", miAscensor.pos_actual);
    consolePrintStr(6,4,str);
    refreshConsoleLine(4);*/

    IntEnable(INT_TIMER2A);
}

//*****************************************************************************
//
// The interrupt handler for the first timer interrupt.
//
//*****************************************************************************
void
Timer0IntHandler(void)
{
	//char str[1];
    //
    // Clear the timer interrupt.
    //
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Update the interrupt status on the display.
    //
    IntDisable(INT_TIMER0A);
    if (miAscensor.sig_piso[0] != -5) {
    if (miAscensor.sig_piso[0] > miAscensor.pos_actual)
    	miAscensor.pos_actual++;
    else if (miAscensor.sig_piso[0] < miAscensor.pos_actual)
    	miAscensor.pos_actual--;
    }
    //g_activado_Int0 = true;
    g_escrito = false;

    /*sprintf(str, "%d", miAscensor.pos_actual);
    consolePrintStr(6,4,str);
    refreshConsoleLine(4);*/

    IntEnable(INT_TIMER0A);
}

void DISPLAY_init() {

	//
	// Se inicializa el Buffer auxiliar y el display de la placa usada.
	//
	initConsole();
	//
	// Se incluye el texto fijo a mostrar
	//
	consolePrintStr(2, 0, "_Ascensor v6.9_");
	consolePrintStr(2, 1, "----------------");
	refreshConsole();

}

void init_structura(void){

	miAscensor.pos_actual = 0;
	miAscensor.g_ucState = ESPERANDO;
	miAscensor.sig_piso[0] = -5;
	miAscensor.sig_piso[1] = -5;
	miAscensor.sig_piso[2] = -5;
	miAscensor.sig_piso[3] = -5;
}

tBoolean comprobar_peticion(void) {

	int i;
	for (i=0; i<4 ;i++) {
		if (g_inputs[i] == 1)
			return true;
	}
}


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

		init_Timer0(3);

		init_Timer2(2);

		init_Timer3(4);

	//
	// Se inicializan los elementos para el Display
	//
		DISPLAY_init();

		init_structura();

		ENVIO("v6.9\n\r")
}

/***
 *
 * Funciones read_Inputs
 *
 *
 *
 *
 *
 */






/******
 *
 * FUNCIONES ELEVATOR_Upadate
 *
 *
 *
 */

 void ESPERANDO_accion (void)
		{
		//ELEVATOR_readSwitches();
	 //	leer_imagen();
	 	leer_array_imagen();


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

 void ESPERANDO_evento(void) {

	 //hay que cambiar la lógica de este evento. Cuando funcione meter un estado más "Iniciando".


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



 void SUBIENDO_accion (void){
//	 TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() * 3);
	 //IntEnable(INT_TIMER0A);
	 g_enviado = false;
	 	if (!g_primero_Int0) {



	 			g_primero_Int0 = true;

	 			eraseConsoleLine(9);
	 			consolePrintStr(3, 9,"S R");
	 			refreshConsoleLine(9);
	 			ENVIO("S Rapida\n\r")

	 		}


	 	if (!g_escrito) {

			switch (miAscensor.pos_actual){
				case 0: enable_Timer_0();
						consolePrintStr(3, 6, "Piso 0");
						ENVIO("P0\n\r")
						break;

				case 1: enable_Timer_0();
						consolePrintStr(3, 6, "Piso 1");
						ENVIO("P1\n\r")
						break;

				case 2: enable_Timer_0();
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

void SUBIENDO_evento (void) {
	if (!g_escrito_and_enviado)
		display_and_UART_Piso();

	if (miAscensor.sig_piso[0] == miAscensor.pos_actual )
		g_ucState = ENPISO;
}


 void BAJANDO_accion (void){
	 //TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() * 3);
	 IntEnable(INT_TIMER0A);
	// TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() * 3);
	 g_enviado = false;
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

				case 1: enable_Timer_0();
						consolePrintStr(3, 6, "Piso 1");
						ENVIO("P1\n\r")
						break;

				case 2: enable_Timer_0();
						consolePrintStr(3, 6, "Piso 2");
						ENVIO("P2\n\r")
						break;

				case 3: enable_Timer_0();
						consolePrintStr(3, 6, "Piso 3");
						ENVIO("P3\n\r")
						break;

				default: break;
				}
				g_escrito = true;
			}

			refreshConsoleLine(6);


 }

 void BAJANDO_evento() {

	 if (!g_escrito_and_enviado)
		display_and_UART_Piso();

	if (miAscensor.sig_piso[0] == miAscensor.pos_actual ){
		g_primero = false;
		g_ucState = ENPISO;
	}
 }

 void ENPISO_accion(void) {

	 IntDisable(INT_TIMER0A);


	 if (!g_escrito) {

	 			switch (miAscensor.pos_actual){
	 				case 0: consolePrintStr(3, 6, "Piso 0");
	 						ENVIO("P0\n\r")
	 						ENVIO_P1(PISO_0)
	 						break;

	 				case 1: enable_Timer_0();
	 						consolePrintStr(3, 6, "Piso 1");
	 						ENVIO("P1\n\r")
	 						ENVIO_P1(PISO_1)
	 						break;

	 				case 2: enable_Timer_0();
	 						consolePrintStr(3, 6, "Piso 2");
	 						ENVIO("P2\n\r")
	 						ENVIO_P1(PISO_2)
	 						break;

	 				case 3: enable_Timer_0();
	 						consolePrintStr(3, 6, "Piso 3");
	 						ENVIO("P3\n\r")
	 						ENVIO_P1(PISO_3)
	 						break;

	 				default: break;
	 				}
	 			    ENVIO("En piso\n\r")
	 				consolePrintStr(3, 9,"En piso");
	 				refreshConsole();
	 				g_escrito = true;
	 				enable_Timer_2();
	 			}

 }

 void ENPISO_evento(void) {

	 if (g_activado_planta)
		 g_ucState = ABRIENDO_PUERTAS;
  }

 void ABRIENDO_PUERTAS_accion(void) {

	 g_activado_planta = false;
	 if (!g_primero) {

			enable_Timer_3();
		  //  miAscensor.pos_actual = miAscensor.sig_piso[0];
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

 void ABRIENDO_PUERTAS_evento(void) {

	 if (g_activado) {
		g_primero = false;
		g_activado = false;
		g_ucState = CERRANDO_PUERTAS;
	}
 }

 void CERRANDO_PUERTAS_accion(void) {

	 consolePrintStr(3, 9,"Cerrando puertas");
	 refreshConsole();

	 ENVIO("Cierra puer\n\r")

 }

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



 void ELEVATOR_Update(void) {

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





int main(void)
{
	ELEVATOR_HW_init();

    while(1)
    {
    	read_inputs();
    	//sleep(2ms)
    	ELEVATOR_Update();

    }
}


void SEMAPHORE_greenON(){
	 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);//on
	 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);//off
	 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);//off

}
void SEMAPHORE_orangeON(){
	 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);//off
	 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);//on
	 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);//off

}
void SEMAPHORE_redON(){
	 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);//on
	 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);//off
	 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);//on

}

void SysTick_Handler(void) {
	g_ucCounter++;
	if ( g_ucCounter == 45 ){
			g_ucCounter = 0;
	}
}
