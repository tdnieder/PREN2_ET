/* ###################################################################
 **     Filename    : main.c
 **     Project     : FRDM_OpenSDA_USBCDC
 **     Processor   : MKL25Z128VLK4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2016-02-23, 19:12, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LEDRed.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDGreen.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LEDBlue.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "WAIT1.h"
#include "USB1.h"
#include "USB0.h"
#include "CDC1.h"
#include "Tx1.h"
#include "Rx1.h"
#include "CS1.h"
#include "TMOUT1.h"
#include "MS1.h"
#include "BitIoLdd4.h"
#include "TRIG.h"
#include "Greifen.h"
#include "motor_rechts.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "PwmLdd2.h"
#include "Drehen.h"
#include "PwmLdd3.h"
#include "Mulde_leeren.h"
#include "PwmLdd4.h"
#include "TU2.h"
#include "DC_Greifer_Schiene_Vertikal.h"
#include "PwmLdd6.h"
#include "Battery.h"
#include "AdcLdd1.h"
#include "DCHorizontalBit.h"
#include "BitIoLdd5.h"
#include "TU3.h"
#include "DC_Greifer_Schiene_Horizontal.h"
#include "PwmLdd8.h"
#include "DCVib.h"
#include "BitIoLdd14.h"
#include "SwitchGreen.h"
#include "BitIoLdd15.h"
#include "SwitchBlue.h"
#include "BitIoLdd16.h"
#include "AnschlagVertikalOben.h"
#include "BitIoLdd17.h"
#include "AnschlagHorizontalHinten.h"
#include "BitIoLdd18.h"
#include "AnschlagHorizontalVorne.h"
#include "BitIoLdd19.h"
#include "motor_links.h"
#include "PwmLdd5.h"
#include "DCVertikalBit.h"
#include "BitIoLdd6.h"
#include "MS2.h"
#include "BitIoLdd7.h"
#include "MS3.h"
#include "BitIoLdd8.h"
#include "DIRLeft.h"
#include "BitIoLdd9.h"
#include "Sleep.h"
#include "BitIoLdd10.h"
#include "Enable.h"
#include "BitIoLdd11.h"
#include "DIRright.h"
#include "BitIoLdd12.h"
#include "ModeDC.h"
#include "BitIoLdd13.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "engine.h"
#include "greifer.h"
#include "mulde.h"
#include "interface.h"
#include "Ultrasonic.h"
#include "inttypes.h"
//#include "mbed.h"

//---------------------------
//Global variables
//---------------------------
int Duty1ms = 58500;
int Duty2ms = 61500;
int Duty360Deg1 = 62750;
int Duty360Deg2 = 59000;
//---------------------------
//Methods
//---------------------------

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	shitDown();
	//motor_links_DisableEvent();motor_rechts_DisableEvent();
	CDC_Run();


	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
}
