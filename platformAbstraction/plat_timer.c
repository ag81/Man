
#include "plat_timer.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "state_machine.h"

extern tBoolean g_activado;
extern tBoolean g_escrito;

extern tBoolean g_activado_planta;
extern tAscensor miAscensor;

void init_Timer0(int factor){

		SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	    //
	    // Enable processor interrupts.
	    //
	    IntMasterEnable();

	    //
	    // Configure the two 32-bit periodic timers.
	    //
	    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_ONE_SHOT);

	    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() * factor);



}

void enable_Timer_0(void) {

	 //
		    // Setup the interrupts for the timer timeouts.
		    //
			//TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() * factor);

		    IntEnable(INT_TIMER0A);

		    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);


		    //
		    // Enable the timer.
		    //
		    TimerEnable(TIMER0_BASE, TIMER_A);

}


void init_Timer2(int factor){

		SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

	    //
	    // Enable processor interrupts.
	    //
	    IntMasterEnable();

	    //
	    // Configure the two 32-bit periodic timers.
	    //
	    TimerConfigure(TIMER2_BASE, TIMER_CFG_A_ONE_SHOT);

	    TimerLoadSet(TIMER2_BASE, TIMER_A, SysCtlClockGet() * factor);



}

void enable_Timer_2(void) {

	 //
		    // Setup the interrupts for the timer timeouts.
		    //
			//TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() * factor);

		    IntEnable(INT_TIMER2A);

		    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);


		    //
		    // Enable the timer.
		    //
		    TimerEnable(TIMER2_BASE, TIMER_A);

}



void init_Timer3(int factor){

		SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);

	    //
	    // Enable processor interrupts.
	    //
	    //IntMasterEnable();

	    //
	    // Configure the two 32-bit periodic timers.
	    //
	    TimerConfigure(TIMER3_BASE, TIMER_CFG_A_ONE_SHOT);

	    TimerLoadSet(TIMER3_BASE, TIMER_A, SysCtlClockGet() * factor);



}

void enable_Timer_3(void) {

	 //
		    // Setup the interrupts for the timer timeouts.
		    //


		    IntEnable(INT_TIMER3A);

		    TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);

		  //  TimerLoadSet(TIMER3_BASE, TIMER_A, SysCtlClockGet() / factor);

		    //
		    // Enable the timer.
		    //
		    TimerEnable(TIMER3_BASE, TIMER_A);

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



