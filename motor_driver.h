//======================================================================================
/** \file motor_driver.h
 *    This file contains a very simple A/D converter driver. The driver is hopefully
 *    thread safe in FreeRTOS due to the use of a mutex to prevent its use by multiple
 *    tasks at the same time. There is no protection from priority inversion, however,
 *    except for the priority elevation in the mutex. */
//======================================================================================

// This define prevents this .H file from being included multiple times in a .CPP file
#ifndef _AVR_MOTOR_DRIVER_H_
#define _AVR_MOTOR_DRIVER_H_

#include "emstream.h"                       // Header for serial ports and devices
#include "FreeRTOS.h"                       // Header for the FreeRTOS RTOS
#include "task.h"                           // Header for FreeRTOS task functions
#include "queue.h"                          // Header for FreeRTOS queues
#include "semphr.h"                         // Header for FreeRTOS semaphores


//-------------------------------------------------------------------------------------
/** \brief This class should run the A/D converter on an AVR processor. 
 *  \details It should have some better comments. Yes, this is a \b subtle \b hint. 
 */

class motor_driver
{
   protected:
    emstream* ptr_to_serial;
    volatile uint16_t* compare;

   public:
      motor_driver(emstream *p_serial_port,
                   volatile uint8_t *p_ddr,
                   uint8_t ddr_mask, 
                   volatile uint8_t *pwm,
                   uint8_t pwm_mask,
                   volatile uint8_t *p_tccra,
                   uint8_t tccra_mask,
                   volatile uint8_t *p_tccrb,
                   uint8_t tccrb_mask,
                   volatile uint16_t *OCR);

      void set_power(int16_t power);
      void brake(void);
      void sample(void);

}; // end of class motor driver


#endif // _AVR_MOTOR_DRIVER_H_
