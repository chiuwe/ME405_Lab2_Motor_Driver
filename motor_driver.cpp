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

// use mask...
motor_driver::motor_driver(emstream *p_serial_port,
                           volatile uint8_t *p_ddr,
                           uint8_t ddr_mask, 
                           volatile uint8_t *pwm,
                           uint8_t pwm_mask,
                           volatile uint8_t *p_tccra,
                           uint8_t tccra_mask,
                           volatile uint8_t *p_tccrb,
                           uint8_t tccrb_mask,
                           volatile uint16_t *OCR) {  

   ptr_to_serial = p_serial_port;
   compare = OCR;

   *p_ddr = ddr_mask;
   *pwm = pwm_mask;
   *p_tccra = tccra_mask;
   *p_tccrb = tccrb_mask;
   *compare = 0;

   DBG(ptr_to_serial, "Motor driver constructor OK" << endl);
}

void motor_driver::set_power(int16_t power) {
   // compare = something;
   // 128 = 0;
   // < 128 = negative;
   // > 128 = positive;
}

void motor_driver::brake(void) {


}

void motor_driver::sample(void) {
   DBG(ptr_to_serial, "TCNT1: " << TCNT1 << endl);
}