#ifndef TASK_HPP_
#define TASK_HPP_

#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Strct.hpp"

#define NO_ERR 0
#define RET_ERR 1


class Task
{
	public:
		Task();
		uint8_t m_u8TaskID;
		virtual uint8_t     run(void){return(0);};
		virtual uint8_t     setup(void){return(0);};
		bool                IsTaskFinished(void){return m_bIsFinished;};
		uint8_t             GetTaskPriority(void) {return m_u8Priority;};
		void                SetTaskPriority(uint8_t i_u8NewPriority){m_u8Priority = i_u8NewPriority;};
	    virtual uint8_t     readMessage(st_Message *l_stNewMessage){return(0);};
	    virtual uint8_t     sendMessage(st_Message *l_stNewMessage){return(0);};
	    char                *getKey(void){return m_pKey;}; //- Returns Task Key
	    void                setKey(char *l_pKey){m_pKey = l_pKey;}; //- Sets Task Key
	    bool                getMssgFlag(){return m_bMssgFlag;}; //- Gets MssgFlag
	    void                setMssgFlag(bool message){m_bMssgFlag = message;}; //- Sets MssgFlag
	    bool                getRunFlag(){return m_bRunFlag;}; //- Gets RunFlag
	    void                setDestKey(char *l_pKey){m_stMssg.std_pDestKey = l_pKey;}; //- Sets Mssg Destination Key
	    st_Message m_stMssg;
	    bool m_bMssgFlag; // - Flag: Task has a message to send
	private:
	   static uint8_t m_u8NextTaskID;
	   uint8_t m_u8Priority;
	protected:
       bool m_bRunFlag; // - Flag: Task needs to be executed in next frame
	   bool m_bIsFinished;
	   char *m_pKey; //- Task Key for identification
};

#endif /* TASK_HPP_ */
