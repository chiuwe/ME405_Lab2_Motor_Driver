//**************************************************************************************
/** \file motor_controller.h
 *    This file contains the header for a motor controller class which controls speed
 *    and direction of a motor using a voltage measured from the A/D as input. A 
 *    potentiomiter is used for speed and a single button controls the break. One each
 *    for each motor */
//**************************************************************************************

// This define prevents this .h file from being included multiple times in a .cpp file
#ifndef _MOTOR_CONTROLLER_H_
#define _MOTOR_CONTROLLER_H_

#include <stdlib.h>                         // Prototype declarations for I/O functions
#include <avr/io.h>                         // Header for special function registers

#include "FreeRTOS.h"                       // Primary header for FreeRTOS
#include "task.h"                           // Header for FreeRTOS task functions
#include "queue.h"                          // FreeRTOS inter-task communication queues

#include "frt_task.h"                       // ME405/507 base task class
#include "time_stamp.h"                     // Class to implement a microsecond timer
#include "frt_queue.h"                      // Header of wrapper for FreeRTOS queues
#include "frt_shared_data.h"                // Header for thread-safe shared data

#include "rs232int.h"                       // ME405/507 library for serial comm.
#include "adc.h"                            // Header for A/D converter driver class
#include "motor_driver.h"


//-------------------------------------------------------------------------------------
/** \brief This task controls the speed/direction of a motor using an analog input from
 *  the A/D converter. 
 *  \details The A/D converter is run using a driver in files \c adc.h and \c adc.cpp.
 *  An anolog input through a POT goes through the adc and is used to control the speed
 *  of the motor.
 */

class motor_controller : public frt_task
{
private:
	// No private variables or methods for this class

protected:
	// No protected variables or methods for this class

public:
	// This constructor creates a generic task of which many copies can be made
	motor_controller (const char*, unsigned portBASE_TYPE, size_t, emstream*);

	// This method is called by the RTOS once to run the task loop for ever and ever.
	void run (void);
};

#endif // _MOTOR_CONTROLLER_H_
