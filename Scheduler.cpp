#include "Scheduler.hpp"

// - Scheduler constructor
Scheduler::Scheduler()
{
    m_u8OpenSlots = static_cast<uint8_t>(NUMBER_OF_SLOTS);
    m_u8NextSlot = 0;
    m_pLinkedList = NULL;
    for(int index = 0; index < NUMBER_OF_SLOTS; index++)
    {
        m_aSchedule[index].pToAttach = (uintptr_t) 0; // Init to an invalid pointer
        m_aTaskInfoStructs[index].pToAttach = (uintptr_t) 0; // Init to an invalid pointer;
    }
    return;
}

// ##############################################
// The attach function, inserts the task into the
// schedule slots.
// ##############################################

uint8_t Scheduler::attach(Task * i_ToAttach, uint64_t i_u64TickInterval)
{
    uint8_t l_ErrorCode = NO_ERR;
    st_TaskInfo l_st_StructToAttach;

    l_st_StructToAttach.pToAttach = i_ToAttach;
    l_st_StructToAttach.pToKey = i_ToAttach->getKey();
    l_st_StructToAttach.u64ticks = this->m_u64ticks;
    l_st_StructToAttach.u64TickInterval = 0;
    l_st_StructToAttach.u64TickIntervalInitValue = i_u64TickInterval;

    if((m_u8OpenSlots>0) && (m_u8NextSlot < NUMBER_OF_SLOTS))
    {
        m_aSchedule[m_u8NextSlot] =  l_st_StructToAttach;
        m_u8OpenSlots--;
        m_u8NextSlot++;
    }
    else
    {
        l_ErrorCode = RET_ERR;
    }
    return l_ErrorCode;
}

// ##############################################
// Run
// - Execute the current schedule
// ##############################################

uint8_t Scheduler::run(void)
{
    int l_iNextTaskSlot = 0U;
    Task * l_pNextTask = (uintptr_t) 0;
    uint8_t l_u8ReturnCode = NO_ERR;

    while(l_iNextTaskSlot < NUMBER_OF_SLOTS)
    {
        l_pNextTask = static_cast<Task *> (m_aSchedule[l_iNextTaskSlot].pToAttach);
        if(l_pNextTask != ((uintptr_t) 0))
        {
            if(m_aSchedule[l_iNextTaskSlot].u64TickInterval == 0 && l_pNextTask->getRunFlag())
            {
                l_pNextTask->run();
            }
            m_aSchedule[l_iNextTaskSlot].u64TickInterval ++;
            if(m_aSchedule[l_iNextTaskSlot].u64TickInterval >= m_aSchedule[l_iNextTaskSlot].u64TickIntervalInitValue) {
                m_aSchedule[l_iNextTaskSlot].u64TickInterval = 0;
            }
        }
        l_iNextTaskSlot++;
    }

    CollectMessages();
    DistributeMessages();

    return l_u8ReturnCode;
}

// ##############################################
// Setup
// - Execute the setup function for all tasks
// ##############################################

uint8_t Scheduler::setup(void)
{
    int l_iNextTaskSlot = 0U;
    Task * l_pNextTask = (uintptr_t) 0;
    uint8_t l_u8ReturnCode = NO_ERR;

    while(l_iNextTaskSlot < NUMBER_OF_SLOTS)
    {
        l_pNextTask = static_cast<Task *> (m_aSchedule[l_iNextTaskSlot].pToAttach);
        if(l_pNextTask != ((uintptr_t) 0))
        {
            l_pNextTask->setup();
        }
        l_iNextTaskSlot++;
    }
    return l_u8ReturnCode;
}

uint8_t Scheduler::CalculateNextSchedule(void)
{

} 

// ##############################################
// Collects messages from Tasks on m_aSchedule
// - Checks Task's m_MssgFlag. If it is ON its
//   sendMessage() function is runned
// - The message received is attached to the
//   message's linked list
// ##############################################

uint8_t Scheduler::CollectMessages(void)
{
    Task *l_pNextSender = NULL;
    int l_iCounter;
    for(l_iCounter = 0; l_iCounter < NUMBER_OF_SLOTS; l_iCounter++)
    {
        l_pNextSender = static_cast<Task *> (m_aSchedule[l_iCounter].pToAttach);
        if(l_pNextSender != ((uintptr_t) 0))
        {
            if (l_pNextSender->getMssgFlag())
            {
                st_Message l_stNewMessage;
                l_pNextSender->sendMessage(&l_stNewMessage);
                InsertNode(m_pLinkedList, l_stNewMessage);
                //break;
            }
        }
    }
    return(NO_ERR);
}

// ##############################################
// Function that inserts new node on linked list
// - creates new node
// - saves message structure to node
// - links node at the end of the list
// ##############################################

uint8_t Scheduler::InsertNode(st_Node *&l_pLinkedList, st_Message l_stNewMessage)
{
    st_Node *l_stNewNode = new st_Node();
    l_stNewNode->std_stMssg = l_stNewMessage;

    st_Node *l_stAux1 = l_pLinkedList;
    st_Node *l_stAux2 = NULL;

    while(l_stAux1 != NULL)
    {
        l_stAux2 = l_stAux1;
        l_stAux1 = l_stAux1->std_pnext;
    }

    if(l_pLinkedList == l_stAux1)
    {
        l_pLinkedList = l_stNewNode;
    }
    else
    {
        l_stAux2->std_pnext = l_stNewNode;
    }
    l_stNewNode->std_pnext = l_stAux1;

    return(NO_ERR);
}

// ###################################################
// Function that distributes messages to their
// respective Tasks using DistributeEraseFirstNode()
// ###################################################

uint8_t Scheduler::DistributeMessages(void)
{
    st_Message l_stNewMessage;

    while(m_pLinkedList != NULL)
    {
            DistributeEraseFirstNode(m_pLinkedList, l_stNewMessage);
    }
    return(NO_ERR);
}

// ##############################################
// Function that erases a node on a linked list
// - Creates a temporary node to store the node
//   on the list that will be deleted
// - Current message is distributed to Task
// - Pointer to list then points to the second
//   node
// - Temporary node is deleted
// ##############################################

uint8_t Scheduler::DistributeEraseFirstNode(st_Node *&l_pLinkedList, st_Message l_stMessage)
{
    st_Node *l_stAux = l_pLinkedList; //- Saves first node of list temporarily
    l_stMessage = l_stAux->std_stMssg; //- Saves message on first node temporarily
    char *l_pKey = l_stMessage.std_pDestKey; //- Destination Key of message 
    Task *l_pTaskPointer = NULL; //

    for(int l_iCounter = 0; l_iCounter < NUMBER_OF_SLOTS; l_iCounter++)
    {
        l_pTaskPointer = static_cast<Task *> (m_aSchedule[l_iCounter].pToAttach);
        if(l_pTaskPointer != ((uintptr_t) 0))
        {
            if(l_pTaskPointer->getKey() == l_pKey)
            {
                l_pTaskPointer->readMessage(&l_stMessage);
            }
        }
    }
    l_pLinkedList = l_stAux->std_pnext;
    delete l_stAux;

    return(NO_ERR);
}

