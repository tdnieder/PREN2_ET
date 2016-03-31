/* ###################################################################
**     Filename    : Events.h
**     Project     : FRDM_OpenSDA_USBCDC
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-23, 19:12, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

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
#include "PwmLdd7.h"
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


#ifdef __cplusplus
extern "C" {
#endif 

static long counterLeft;
static long counterRight;

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


/*
** ===================================================================
**     Event       :  motor_rechts_OnEnd (module Events)
**
**     Component   :  motor_rechts [PWM]
**     Description :
**         This event is called when the specified number of cycles has
**         been generated. (Only when the component is enabled -
**         <Enable> and the events are enabled - <EnableEvent>). The
**         event is available only when the <Interrupt service/event>
**         property is enabled and selected peripheral supports
**         appropriate interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void motor_rechts_OnEnd(void);

/*
** ===================================================================
**     Event       :  motor_links_OnEnd (module Events)
**
**     Component   :  motor_links [PWM]
**     Description :
**         This event is called when the specified number of cycles has
**         been generated. (Only when the component is enabled -
**         <Enable> and the events are enabled - <EnableEvent>). The
**         event is available only when the <Interrupt service/event>
**         property is enabled and selected peripheral supports
**         appropriate interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void motor_links_OnEnd(void);

/*
** ===================================================================
**     Event       :  TU2_OnChannel0 (module Events)
**
**     Component   :  TU2 [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel0 event and
**         Timer unit must be enabled. See [SetEventMask] and
**         [GetEventMask] methods. This event is available only if a
**         [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU2_OnChannel0(LDD_TUserData *UserDataPtr);

void Battery_OnEnd(void);
/*
** ===================================================================
**     Event       :  Battery_OnEnd (module Events)
**
**     Component   :  Battery [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Battery_OnCalibrationEnd(void);
/*
** ===================================================================
**     Event       :  Battery_OnCalibrationEnd (module Events)
**
**     Component   :  Battery [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  DC_Greifer_Schiene_Vertikal_OnEnd (module Events)
**
**     Component   :  DC_Greifer_Schiene_Vertikal [PWM]
**     Description :
**         This event is called when the specified number of cycles has
**         been generated. (Only when the component is enabled -
**         <Enable> and the events are enabled - <EnableEvent>). The
**         event is available only when the <Interrupt service/event>
**         property is enabled and selected peripheral supports
**         appropriate interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DC_Greifer_Schiene_Vertikal_OnEnd(void);

/*
** ===================================================================
**     Event       :  Mulde_leeren_OnEnd (module Events)
**
**     Component   :  Mulde_leeren [PWM]
**     Description :
**         This event is called when the specified number of cycles has
**         been generated. (Only when the component is enabled -
**         <Enable> and the events are enabled - <EnableEvent>). The
**         event is available only when the <Interrupt service/event>
**         property is enabled and selected peripheral supports
**         appropriate interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Mulde_leeren_OnEnd(void);

/*
** ===================================================================
**     Event       :  Drehen_OnEnd (module Events)
**
**     Component   :  Drehen [PWM]
**     Description :
**         This event is called when the specified number of cycles has
**         been generated. (Only when the component is enabled -
**         <Enable> and the events are enabled - <EnableEvent>). The
**         event is available only when the <Interrupt service/event>
**         property is enabled and selected peripheral supports
**         appropriate interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Drehen_OnEnd(void);

/*
** ===================================================================
**     Event       :  Greifen_OnEnd (module Events)
**
**     Component   :  Greifen [PWM]
**     Description :
**         This event is called when the specified number of cycles has
**         been generated. (Only when the component is enabled -
**         <Enable> and the events are enabled - <EnableEvent>). The
**         event is available only when the <Interrupt service/event>
**         property is enabled and selected peripheral supports
**         appropriate interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Greifen_OnEnd(void);

/*
** ===================================================================
**     Event       :  TU3_OnChannel1 (module Events)
**
**     Component   :  TU3 [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel1 event and
**         Timer unit must be enabled. See [SetEventMask] and
**         [GetEventMask] methods. This event is available only if a
**         [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU3_OnChannel1(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  TU3_OnChannel0 (module Events)
**
**     Component   :  TU3 [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if compare register match the counter registers or
**         capture register has a new content. OnChannel0 event and
**         Timer unit must be enabled. See [SetEventMask] and
**         [GetEventMask] methods. This event is available only if a
**         [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void TU3_OnChannel0(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  DC_Greifer_Schiene_Horizontal_OnEnd (module Events)
**
**     Component   :  DC_Greifer_Schiene_Horizontal [PWM]
**     Description :
**         This event is called when the specified number of cycles has
**         been generated. (Only when the component is enabled -
**         <Enable> and the events are enabled - <EnableEvent>). The
**         event is available only when the <Interrupt service/event>
**         property is enabled and selected peripheral supports
**         appropriate interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void DC_Greifer_Schiene_Horizontal_OnEnd(void);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
