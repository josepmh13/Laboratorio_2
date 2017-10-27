/*
 * *******
 * Task ADC: (.cpp)
 * *******
 * Message received: none
 * Activates ADC to read and convert accelerometer values
 * Message sent: ADCResultZ, ADCResultZ, ADCResultZ
 * ADC interrupt: Send a message to Task "PIX" with ADCResultX, ADCResultY, ADCResultZ
 *
 * Created on: Oct 6, 2017
 * Authors: Luisa Fernanda Quesada &
 *          Jose Pablo Martinez
 */
#include "ADC.hpp"

ADC::ADC(uint16_t)
{
};

// ****************************
// Run:
// - Activates ADC conversion
// ****************************

uint8_t ADC::run()
{

    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC; // Start
    return (NO_ERR);
};

// ****************************
// Setup:
// - Sets ADC configuration
// ****************************

uint8_t ADC::setup()
{
    m_bRunFlag = true; // Set RunFlag high to run ADC continuously 

    // ****************************
    //         ADC CONFIG
    // ****************************
    // - Configure ADC14  with MCLK (3Mhz), Sample and Hold Source, ADC Clock Divider 7, Mode Multiple Sample and Convert

    ADC14->CTL0 = ADC14_CTL0_PDIV_0 | ADC14_CTL0_SHS_0 | ADC14_CTL0_DIV_7
            | ADC14_CTL0_SSEL__MCLK | ADC14_CTL0_SHT0_1 | ADC14_CTL0_ON
            | ADC14_CTL0_SHP | ADC14_CTL0_CONSEQ_3;

    // *****************************
    //  CONVERSION MEMORY REGISTER
    // *****************************
    // - Memory MCTL[0]-MCTL[2] for x, y, z accelerometer measurements

    ADC14->MCTL[1] = ADC14_MCTLN_INCH_11 | ADC14_MCTLN_VRSEL_0;
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_13 | ADC14_MCTLN_VRSEL_0;
    ADC14->MCTL[3] = ADC14_MCTLN_INCH_14 | ADC14_MCTLN_VRSEL_0;

    // ****************************
    //       INTERRUPT ENABLE
    // ****************************
    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_ENC;
    ADC14->IER0 = ADC14_IER0_IE1 | ADC14_IER0_IE2 | ADC14_IER0_IE3;

    return (NO_ERR);
};


uint8_t ADC::sendMessage(st_Message *l_stNewMessage)
{
    m_bMssgFlag = false; // Sent message, set m_bMssgFlag low
    *l_stNewMessage = m_stMssg; // Ataches task message structure
    return(NO_ERR);
}
