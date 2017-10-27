/*
 * PAINT.cpp
 *
 *  Created on: Oct 9, 2017
 *      Authors:  Luisa Fernanda Quesada  &
 *                Jose Pablo Martinez
 *               
 */

/*
 * Message received: m_iLines and m_bColor from PIX
 */

#include "HOR.hpp"

HOR::HOR(uint16_t)
{
    m_stRect.xMin = 0;
    m_stRect.xMax = 127;
}


uint8_t HOR::run()
{
    //################################
    // Internal counter
    //################################
    int j;
    
    //################################
    // - Calculate the lines to be
    //   painted on the x-axis (roll) 
    //   and z-axis (scroll), from the 
    //   line formed by the extreme 
    //   values of the ADC and normalized 
    //   to 128 (number of pixels)
    //################################
   
    m_iX = 128*(m_uint16ADC14Rx-8250)/(3100.0);
    // Calcula los cambios en Z
    m_iZ = 128*(11400-m_uint16ADC14Rz)/(6500.0);

    
    if(m_iX<0)
    {
        //################################
        // - Roll to the left 
        //    Upper rectangule the sky
        //    Middle rectangule, the division
        //    Lower rectangule the ground
        //################################
        
        // Paint the upper rectangule (sky)
        m_stRect.yMin = -1;
        m_stRect.yMax =  m_iZ + m_iX;
        m_uint16tulValue = 0X00FF; 
        Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect, m_uint16tulValue);

        //    Middle rectangule, the division
        for (j = 0; j <= -2*m_iX; j++)
        {
            // Lower triangule (ground)
            m_stRect2.xMin = 0;
            m_stRect2.xMax = (128/(-2.0*m_iX))*j;
            m_stRect2.yMin = m_iZ + m_iX + j - 1;
            m_stRect2.yMax = m_iZ + m_iX + j;
            m_uint16tulValue = 0XAA00; //brown
            Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect2, m_uint16tulValue);
            
            //################################
            // - Hypotenuse
            //   Calculate the hypotenuse of 
            //   the triangle formed and dis-
            //   cretize the value at 
            //    -2.0 * m_iX
            //################################
           
            m_iHip = (sqrt(128*128 + 4*m_iX*m_iX))/(-2.0*m_iX);
            
            // Paint the white line
            m_stRect1.xMin = m_stRect2.xMax ;
            m_stRect1.xMax = m_stRect2.xMax + m_iHip;
            m_stRect1.yMin = m_iZ + m_iX + j - 2;
            m_stRect1.yMax = m_iZ + m_iX + j - 1;
            m_uint16tulValue = 0XFFFF; //white
            Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect1, m_uint16tulValue);

            // Upper triangule (sky)
            m_stRect2.xMin = (128/(-2.0*m_iX))*j;
            m_stRect2.xMax = 128;
            m_stRect2.yMin = m_iZ + m_iX + j - 3;
            m_stRect2.yMax = m_iZ + m_iX + j - 2;
            m_uint16tulValue = 0X00FF; //blue
            Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect2, m_uint16tulValue);
        }

        // Paint the lower rectangule (ground)
        m_stRect.yMin = m_iZ - m_iX;
        m_stRect.yMax = 128;
        m_uint16tulValue = 0XAA00; //brown
        Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect, m_uint16tulValue);

    }
    else if (m_iX>0)
    {
        //################################
        // - Roll to the right 
        //    Upper rectangule the sky
        //    Middle rectangule, the division
        //    Lower rectangule the ground
        //################################
        
        // Paint the upper rectangule (sky)
        m_stRect.yMin = -1;
        m_stRect.yMax =  m_iZ - m_iX ;
        m_uint16tulValue = 0X00FF; //blue
        Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect, m_uint16tulValue);

        for (j = 0; j <= 2*m_iX; j++)
        {
            // Upper triangule (sky)
            m_stRect2.xMin = 0;
            m_stRect2.xMax = 128-(128/(2.0*m_iX))*j;
            m_stRect2.yMin = m_iZ - m_iX + j - 1;
            m_stRect2.yMax = m_iZ - m_iX + j ;
            m_uint16tulValue = 0X00FF; //blue
            Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect2, m_uint16tulValue);
            
            //################################
            // - Hypotenuse
            //   Calculate the hypotenuse of 
            //   the triangle formed and dis-
            //   cretize the value at 
            //    2.0 * m_iX
            //################################
            
            m_iHip = (sqrt(128*128 + 4*m_iX*m_iX))/(2.0*m_iX);
            
            // Paint the white line
            m_stRect1.xMin = m_stRect2.xMax;
            m_stRect1.xMax = m_stRect2.xMax + m_iHip;
            m_stRect1.yMin = m_iZ - m_iX + j ;
            m_stRect1.yMax = m_iZ - m_iX + j + 1;
            m_uint16tulValue = 0XFFFF; //white
            Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect1, m_uint16tulValue);

            // Lower triangule (ground)
            m_stRect2.xMin = 128-(128/(2.0*m_iX))*j-m_iHip;
            m_stRect2.xMax = 128;
            m_stRect2.yMin = m_iZ - m_iX + j + 1;
            m_stRect2.yMax = m_iZ - m_iX + j + 2;
            m_uint16tulValue = 0XAA00; //brown
            Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect2, m_uint16tulValue);
        }

        // Paint the lower rectangule (ground)
        m_stRect.yMin = m_iZ + m_iX + 2 ;
        m_stRect.yMax = 128;
        m_uint16tulValue = 0XAA00; //brown
        Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect, m_uint16tulValue);
    }
    else
    {
        //################################
        // - Without roll
        //    Upper rectangule the sky
        //    Middle line, the division
        //    Lower rectangule the ground
        //################################
        
        // Paint the upper rectangule (sky)
        m_stRect.yMin = -1;
        m_stRect.yMax =  m_iZ + m_iX;
        m_uint16tulValue = 0X00FF; //blue
        Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect, m_uint16tulValue);
    
        // Paint the middle line
        m_stRect.yMin = m_iZ - m_iX  ;
        m_stRect.yMax = m_iZ - m_iX + 1;
        m_uint16tulValue = 0XFFFF; //white
        Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect, m_uint16tulValue);

        // Paint the upper rectangule (ground)
        m_stRect.yMin = m_iZ - m_iX + 1;
        m_stRect.yMax = 128;
        m_uint16tulValue = 0XAA00; //brown
        Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRect, m_uint16tulValue);
    }

    m_bRunFlag = false; //- Sets RunFlag low
    return (NO_ERR);
}

//################################
// Setup
// - Defines initial value for
//   m_iLastLine as 64 (middle line
//   LCD screen
//################################

uint8_t HOR::setup()
{

    m_bRunFlag = false; // - Sets RunFlag low
 
//################################
// - Initializing screen, top half
//   sky, bottom half ground and
//   the middle a white line 
//################################

    Graphics_Rectangle m_stRectInit;
    uint16_t l_uint16tValue;
    m_stRectInit.xMin = 0;
    m_stRectInit.xMax = 127;

    m_stRectInit.yMin = 0;
    m_stRectInit.yMax = 63;
    l_uint16tValue = 0X00CF; //- Blue
    Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRectInit,
                                    l_uint16tValue);

    m_stRectInit.yMin = 64;
    m_stRectInit.yMax = 65;
    l_uint16tValue = 0XFFFF; //- White
    Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRectInit,
                                    l_uint16tValue);
    m_stRectInit.yMin = 65;
    m_stRectInit.yMax = 127;
    l_uint16tValue = 0XAA00; //- Brown
    Graphics_fillRectangleOnDisplay(&g_sCrystalfontz128x128, &m_stRectInit,
                                    l_uint16tValue);

    return (NO_ERR);
}

//################################
// Reads message received
// - Reads uin16t data for ADC result
// - Turns on RunFlag
//################################

uint8_t HOR::readMessage(st_Message *l_stNewMessage)
{
    m_uint16ADC14Rz = l_stNewMessage->std_u16IntData;
    m_uint16ADC14Rx = l_stNewMessage->std_u16IntData2;
    m_bRunFlag = true;
    return (NO_ERR);
}
