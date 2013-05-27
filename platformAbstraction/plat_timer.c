
#include "plat_timer.h"

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



