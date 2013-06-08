

#include "inputs_reading.h"
#include "state_machine.h"

extern unsigned char g_ucKeypadSwitches;

extern tAscensor miAscensor;


int g_inputs[NUM_PISOS] = {0, 0, 0, 0};
int g_inputs_imagen[NUM_PISOS] = {0, 0, 0, 0};


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

void read_switches(void){

	unsigned char pressed_data;

	pressed_data = (
			GPIOPinRead( GPIO_PORTE_BASE , (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3))
			);


	g_ucKeypadSwitches = pressed_data;

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
