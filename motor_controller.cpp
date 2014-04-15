//**************************************************************************************
/** \file motor_controller.cpp
 *    This file contains the code for a motor controller class which controls speed and
 *    direction of a motor using a voltage measured from the A/D as input. One button
 *    will trigger stop and go. A second button will determine which motor is being
 *    controlled. */
//**************************************************************************************

#include "frt_text_queue.h"                 // Header for text queue class
#include "motor_controller.h"               // Header for this motor controller
#include "shares.h"                         // Shared inter-task communications


//-------------------------------------------------------------------------------------
/** This constructor creates a task which controls the brightness of an LED using
 *  input from an A/D converter. The main job of this constructor is to call the
 *  constructor of parent class (\c frt_task ); the parent's constructor the work.
 *  @param a_name A character string which will be the name of this task
 *  @param a_priority The priority at which this task will initially run (default: 0)
 *  @param a_stack_size The size of this task's stack in bytes 
 *                      (default: configMINIMAL_STACK_SIZE)
 *  @param p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which can
 *                   be used by this task to communicate (default: NULL)
 */

motor_controller::motor_controller (const char* a_name, 
								 unsigned portBASE_TYPE a_priority, 
								 size_t a_stack_size,
								 emstream* p_ser_dev
								)
	: frt_task (a_name, a_priority, a_stack_size, p_ser_dev)
{
	// Nothing is done in the body of this constructor. All the work is done in the
	// call to the frt_task constructor on the line just above this one
}


//-------------------------------------------------------------------------------------
/** This method is called once by the RTOS scheduler. Each time around the for (;;)
 *  loop, it reads the A/D converter and change the selected motors speed. Each loop
 *  also check the two additional buttons.
 */

void motor_controller::run (void) {
   uint16_t a2d_reading1;
   uint16_t a2d_reading2;
	// Make a variable which will hold times to use for precise task scheduling
	portTickType previousTicks = xTaskGetTickCount ();

	// (1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1) | (1 << WGM10) Fast PWM 8-bit
   // (1 << WGM12) | (1 << CS11) | (1 << CS10) clk/64 (prescaler)
   // outputs 16E6/64/255 = 980Hz PWM
	motor_driver *p_my_motor_driver1 = new motor_driver(p_serial, &DDRC, 0x07, &DDRB, 0x40, &PORTC, 0x05, 0x06, &TCCR1A, 0xA9, &TCCR1B, 0x0B, &OCR1B);
	motor_driver *p_my_motor_driver2 = new motor_driver(p_serial, &DDRD, 0xE0, &DDRB, 0x20, &PORTD, 0xA0, 0xC0, &TCCR1A, 0xA9, &TCCR1B, 0x0B, &OCR1A);
   adc *p_my_adc = new adc(p_serial);

	// This is the task loop for the motor control task. This loop runs until the
	// power is turned off or something equally dramatic occurs.
   p_my_motor_driver2->set_power(250);
   p_my_motor_driver1->set_power(-250);
	for (;;) {
      a2d_reading1 = p_my_adc->read_once(0);
      a2d_reading2 = p_my_adc->read_once(1);
      p_my_motor_driver1->set_power((a2d_reading1 / 2) - 255);
      p_my_motor_driver2->set_power((a2d_reading2 / 2) - 255);
		delay_from_to (previousTicks, configMS_TO_TICKS (100));
	}
}

