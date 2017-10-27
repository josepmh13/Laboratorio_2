#include "LED.hpp"

LED::LED(uint16_t i_BITN)
{
	m_u16BITN = i_BITN;
}

uint8_t LED::run()
{
    /*###########################
     * Blink code Assuming PORT2
     ############################*/
	
    P2->OUT ^= m_u16BITN;

    return(NO_ERR);
}

uint8_t LED::setup()
{
    P2->DIR |= m_u16BITN; //Red LED
    P2->OUT &= m_u16BITN; // Initialize the LED Value
    m_bRunFlag = true;
    return(NO_ERR);
}



