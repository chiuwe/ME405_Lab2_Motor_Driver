//**************************************************************************************
/** \file task_brightness.cpp
 *    This file contains the code for a task class which controls the brightness of an
 *    LED using a voltage measured from the A/D as input. The fun part: the brightness
 *    that is being controlled can be on another AVR computer, with signals being sent
 *    and received via wireless transceivers. 
 *
 *  Revisions:
 *    \li 09-30-2012 JRR Original file was a one-file demonstration with two tasks
 *    \li 10-05-2012 JRR Split into multiple files, one for each task
 *    \li 10-25-2012 JRR Changed to a more fully C++ version with class task_sender
 *    \li 10-27-2012 JRR Altered from data sending task into LED blinking class
 *    \li 11-04-2012 JRR Altered again into the multi-task monstrosity
 *    \li 12-13-2012 JRR Yet again transmogrified; now it controls LED brightness
 *
 *  License:
 *    This file is copyright 2012 by JR Ridgely and released under the Lesser GNU 
 *    Public License, version 2. It intended for educational use only, but its use
 *    is not limited thereto. */
/*    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUEN-
 *    TIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 *    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 *    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 *    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
//**************************************************************************************

#include "frt_text_queue.h"                 // Header for text queue class
#include "motor_controller.h"                // Header for this task
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
 *  loop, it reads the A/D converter and uses the result to control the brightness of 
 *  an LED. 
 */

void motor_controller::run (void)
{
	// Make a variable which will hold times to use for precise task scheduling
	portTickType previousTicks = xTaskGetTickCount ();

	// (1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1) | (1 << WGM10) Fast PWM 8-bit
   // (1 << WGM12) | (1 << CS11) | (1 << CS10) clk/64 (prescaler)
   // outputs 16E6/64/255 = 980Hz PWM
	motor_driver *p_my_motor_driver1 = new motor_driver(p_serial, &DDRC, 0x06, &DDRB, 0x20, &TCCR1A, 0xA9, &TCCR1B, 0x0B, &OCR1B);
	motor_driver *p_my_motor_driver2 = new motor_driver(p_serial, &DDRD, 0x70, &DDRB, 0x10, &TCCR1A, 0xA9, &TCCR1B, 0x0B, &OCR1A);

	// Configure counter/timer 3 as a PWM for LED brightness. First set the data
	// direction register so that the pin used for the PWM will be an output. The 
	// pin is Port E pin 4, which is also OC3B (Output Compare B for Timer 3)
	DDRE = (1 << 4);

	// To set 8-bit fast PWM mode we must set bits WGM30 and WGM32, which are in two
	// different registers (ugh). We use COM3B1 and Com3B0 to set up the PWM so that
	// the pin output will have inverted sense, that is, a 0 is on and a 1 is off; 
	// this is needed because the LED connects from Vcc to the pin. 
	TCCR3A = (1 << WGM30)
			 | (1 << COM3B1) | (1 << COM3B0);

	// The CS31 and CS30 bits set the prescaler for this timer/counter to run the
	// timer at F_CPU / 64
	TCCR3B = (1 << WGM32)
			 | (1 << CS31)  | (1 << CS30);

	// This is the task loop for the brightness control task. This loop runs until the
	// power is turned off or something equally dramatic occurs
	for (;;)
	{
      p_my_motor_driver1->sample();
      // sample ADC
      // call setPower() each motor.
      // additional: check button for brake
      // additional: check button to switch between motors.
		delay_from_to (previousTicks, configMS_TO_TICKS (100));
	}
}

