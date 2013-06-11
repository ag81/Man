
#include "plant_simulator.h"

extern tBoolean g_subida;
extern tBoolean g_bajada;

extern tAscensor miAscensor;

extern tBoolean g_timer0_expired;
extern tBoolean g_timer3_expired;

tBoolean g_timer0_activado = false;
tBoolean g_timer3_activado = false;

tBoolean g_open_door_limit = false;
tBoolean g_close_door_limit = false;

extern tBoolean g_open_door;
extern tBoolean g_close_door;

void plant_simulator_execute(void){

	//execite para timer de subida();

	if (g_subida || g_bajada) {
			if (!g_timer0_activado) {
				g_timer0_activado = true;
				enable_Timer_0();
			}
	if (g_timer0_expired) {
		g_timer0_expired = false;
		g_timer0_activado = false;
		if (g_subida) miAscensor.pos_actual = miAscensor.pos_actual +  1;
		else if (g_bajada) miAscensor.pos_actual = miAscensor.pos_actual - 1;
		}
	}

	if (!g_subida && !g_bajada) {
	//	disable_Timer0();
	//	g_timer0_activado = false;

		if (g_open_door) {
			if (!g_timer3_activado) {
				g_timer3_activado = true;
				enable_Timer_3();
				}
			if (g_timer3_expired) {
				g_timer3_expired = false;
				g_timer3_activado = false;
				g_open_door_limit = true;
				disable_Timer3();
			}
		}

		/*if (g_close_door) {
			if (!g_timer3_activado) {
				g_timer3_activado = true;
				enable_Timer_3();
				}
			if (g_timer3_expired) {
				g_timer3_expired = false;
				g_close_door_limit = true;
				}
		}*/
	}
}
