/*
 * HOR.hpp
 *
 *  Created on: Oct 9, 2017
 *      Authors: Jose Pablo Martinez &
                 Luisa Fernanda Quesada
 */

#ifndef HOR_HPP_
#define HOR_HPP_
#define __NOP __nop
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <C:/ti/simplelink_msp432_sdk_1_40_01_00/source/ti/grlib/grlib.h>
#include "Task.hpp"
#include "Strct.hpp"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <C:/ti/simplelink_msp432_sdk_1_40_01_00/source/ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <C:/ti/simplelink_msp432_sdk_1_40_01_00/source/ti/grlib/grlib.h>
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <math.h>


#define NUMBER_OF_SLOTS 255
#define NULL            0

class HOR : public Task
{
  public:
    HOR(uint16_t);
    virtual uint8_t run(void);
    virtual uint8_t setup(void);
    virtual uint8_t readMessage(st_Message * l_stNewMessage);
  protected:
    int m_iZ; //- Amount of lines to be painted on frame for Z axis 
    int m_iX; //- Amount of lines to be painted on frame for X axis 
    int m_iHip; // Hypotenuse of the triangle
    uint16_t m_uint16ADC14Rx; // Analog Digital Converter result in X axis
    uint16_t m_uint16ADC14Rz; // Analog Digital Converter result in Z axis
    uint16_t  m_uint16tulValue; //- Paint Blue, Brown or White
    Graphics_Rectangle m_stRect;
    Graphics_Rectangle m_stRect1;
    Graphics_Rectangle m_stRect2;
  private:
};

#endif /* PAINT_HPP_ */
