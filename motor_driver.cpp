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
/** \brief This constructor sets up a motor driver. 
 *  \details \b Details: The motor driver is enabled based on parameters. The motor
 *  initial spins clockwise.
 *  @param p_serial_port A pointer to the serial port where debugging info is written. 
 *  @param p_ddr A pointer to the DDRx for INx and DIAGx on h-bridge chip.
 *  @param ddr_mask Enable pin settings on h-bridge chip.
 *  @param p_pwm A pointer to the DDRx for pwn pin on h-bridge chip.
 *  @param p_port
 *  @param cw_mask
 *  @param ccw_mask
 *  @param pwm_mask Enable pwm pin on h-bridge chip.
 *  @param p_tccra A pointer to the timer/counter register A.
 *  @param tccra_mask Timer/counter register A mask.
 *  @param p_tccrb A pointer to the timer/counter register B.
 *  @param tccrb_mask Timer/counter register B mask.
 *  @param ocr A pointer to the output compare register.
 */

motor_driver::motor_driver(emstream *p_serial_port,
                           volatile uint8_t *p_ddr,
                           uint8_t ddr_mask, 
                           volatile uint8_t *p_pwm,
                           uint8_t pwm_mask,
                           volatile uint8_t *p_port,
                           uint8_t cw_mask,
                           uint8_t ccw_mask,
                           volatile uint8_t *p_tccra,
                           uint8_t tccra_mask,
                           volatile uint8_t *p_tccrb,
                           uint8_t tccrb_mask,
                           volatile uint16_t *p_ocr) {  

   ptr_to_serial = p_serial_port;
   compare = p_ocr;
   direction = p_port;
   cw = cw_mask;
   ccw = ccw_mask;

   *p_ddr = ddr_mask;
   *p_pwm = pwm_mask;
   *p_port = cw_mask;
   *p_tccra = tccra_mask;
   *p_tccrb = tccrb_mask;
   *compare = 128;

   // DDRC = (1 << 0) | (1 << 1) | (1 << 2);
   // DDRB = (1 << 6);
   // PORTC = (1 << 0) | (1 << 2);
   // TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1) | (1 << WGM10); // Fast PWM 8-bit
   // TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // clk/64 (prescaler)
   // OCR1B = 50;

   DBG(ptr_to_serial, "Motor driver constructor OK" << endl);
}


//-------------------------------------------------------------------------------------
/** \brief This method sets direction and duty cycle of the motor. 
 *  \details \b Details: This method determines direction and sets the duty cycle.
 *  @param power power setting, negative number reverse motor direction.
 */

void motor_driver::set_power(int16_t power) {
   // compare = something;
   // 128 = 0;
   // < 128 = negative;
   // > 128 = positive;
}

//-------------------------------------------------------------------------------------
/** \brief This method stops the motor.
 *  \details \b Details: This method stops the motor.
 */

void motor_driver::brake(void) {


}

void motor_driver::sample(void) {
   DBG(ptr_to_serial, "TCNT1: " << TCNT1 << endl);
}