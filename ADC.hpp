/*
 * *******
 * Task ADC: (.h)
 * *******
 * Created on: Oct 6, 2017
 * Authors: Luisa Fernanda Quesada Camacho &
 *          Jose Pablo Martinez Hernandez
 *
 */


#ifndef ADC_HPP_
#define ADC_HPP_
#define __NOP __nop
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <C:/ti/simplelink_msp432_sdk_1_40_01_00/source/ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <C:/ti/simplelink_msp432_sdk_1_40_01_00/source/ti/grlib/grlib.h>
#include "Task.hpp"

class ADC : public Task
{
  public:
        ADC(uint16_t);
        virtual uint8_t run(void);
        virtual uint8_t setup(void);
        virtual uint8_t sendMessage(st_Message * l_stNewMessage);
        uint16_t m_ADCResult;
  protected:
  private:
};

#endif /* ADC_HPP_ */
