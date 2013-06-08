
#include "state_machine.h"





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

extern int g_inputs[NUM_PISOS];
extern int g_inputs_imagen[NUM_PISOS];



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




tBoolean comprobar_peticion(void) {

	int i;
	for (i=0; i<4 ;i++) {
		if (g_inputs[i] == 1)
			return true;
	}
	return false;
}

 void ESPERANDO_accion (void)
		{

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


