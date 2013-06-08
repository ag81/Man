
#include "state_machine.h"

extern tAscensor miAscensor;

void DISPLAY_init(void) {

	//
	// Se inicializa el Buffer auxiliar y el display de la placa usada.
	//
	initConsole();
	//
	// Se incluye el texto fijo a mostrar
	//
	consolePrintStr(2, 0, "_Asc v6.10_");
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

		ENVIO("v6.10\n\r")
}


int main(void)
{
	// se inicializa
	ELEVATOR_HW_init();

    while(1)
    {
    	//
    	read_inputs();

    	//sleep(2ms)
    	ELEVATOR_Update();

    }

    return 0;
}


