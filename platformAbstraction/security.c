
#include "security.h"


//Comprueba si las serie puertas de cabina estan ok

tBoolean is_SPC_ok(void) {
	#if SPC
		return true;
	#else
		return false;
    #endif
}

//Comprueba si las series de cabina - series de cerraduras estan ok

tBoolean is_SC_SCE_ok(void) {
	#if SC_SCE
		return true;
	#else
		return false;
    #endif
}

//Comprueba si las serie puertas de cabina estan ok

tBoolean is_SP_ok(void) {
	#if SP
		return true;
	#else
		return false;
	#endif
}

//Comprueba si las series de cabina - series de cerraduras estan ok

tBoolean is_SH_ok(void) {
	#if SH
		return true;
	#else
		return false;
    #endif
}

//Comprueba si las serie puertas de cabina estan ok

tBoolean is_SCM_ok(void) {
	#if SCM
		return true;
	#else
		return false;
    #endif
}

//Comprueba si las series de cabina - series de cerraduras estan ok

tBoolean is_LV_ok(void) {
	#if LV
		return true;
	#else
		return false;
	#endif
}

// se comprueba la seguridad que invalida la etapa de potencia
tBoolean check_Security(void) {
	if (is_SPC_ok() && is_SC_SCE_ok() && is_SP_ok()&& is_SH_ok() && is_SCM_ok() && is_LV_ok())
			return true;
			else
				return false;

}
