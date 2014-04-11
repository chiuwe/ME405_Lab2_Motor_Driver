//*************************************************************************************
/** \file adc.cpp
 *    This file contains a very simple A/D converter driver. This driver should be
 *
 *  Revisions:
 *    \li 01-15-2008 JRR Original (somewhat useful) file
 *    \li 10-11-2012 JRR Less original, more useful file with FreeRTOS mutex added
 *    \li 10-12-2012 JRR There was a bug in the mutex code, and it has been fixed
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
//*************************************************************************************

#include <stdlib.h>                         // Include standard library header files
#include <avr/io.h>

#include "rs232int.h"                       // Include header for serial port class
#include "motor_driver.h"                   // Include header for the A/D class


//-------------------------------------------------------------------------------------
/** \brief This constructor sets up an A/D converter. 
 *  \details \b Details: The A/D converter is enabled and the division factor is set to 32.
 *  @param p_serial_port A pointer to the serial port where debugging info is written. 
 */

motor_driver::motor_driver (emstream* p_serial_port) {  

   ptr_to_serial = p_serial_port;

   DDRC = 0xFF;
   DDRB = 0xFF;
   PORTC = 0x05;
   PORTD = (1 << 5) | (1 << 7);
   TCCR1A = 0b10101001;   // Fast PWM 8-bit
   TCCR1B = 0b00010011;   // clk/64 (prescaler)
                          // outputs 16E6/64/255 = 980Hz PWM
   OCR1A = 50;            // compare value => 20% duty cycle
   OCR1B = 171;           // compare value => 75% duty cycle

   DBG(ptr_to_serial, "Motor driver constructor OK" << endl);
}