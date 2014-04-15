//*************************************************************************************
/** \file motor_driver.cpp
 *    This file contains a very simple A/D converter driver. This driver should be
 */
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