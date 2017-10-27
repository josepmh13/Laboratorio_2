/*
 * Scheduler.hpp
 *
 *  Created on: Aug 31, 2016
 *      Authors: Jose Pablo Martinez &
 		 Luisa Fernanda Quesada &
		 Esteban Ortiz
 */

#ifndef TASKS_SCHEDULER_HPP_
#define TASKS_SCHEDULER_HPP_
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Task.hpp"
#include "Strct.hpp"
#include <stdio.h>
#include <string.h>


#define NUMBER_OF_SLOTS 255
#define NULL            0

// - This structure defines the Task Information
struct st_TaskInfo {
	Task * pToAttach; // - Pointer to the Task
	uint64_t u64TickInterval; // - How often the task is executed
	uint64_t u64ticks; // - Current tick count
	uint64_t u64TickIntervalInitValue; // - Value to reset
	char *pToKey;
};



class Scheduler
{
public:
    Scheduler();
    uint64_t m_u64ticks;
    uint8_t attach(Task * i_ToAttach, uint64_t i_u64TickInterval);
    uint8_t run(void);
    uint8_t setup(void);

private:
    uint8_t m_u8OpenSlots; // - Available slots
    uint8_t m_u8NextSlot;  // - Next available slot
    st_TaskInfo m_aSchedule[NUMBER_OF_SLOTS]; // - Current schedule to be executed
    //st_TaskInfo m_aNextSchedule[NUMBER_OF_SLOTS]; // - Next schedule to be executed (not implemented)
    //uint8_t CalculateNextSchedule(void); // - Calculate next schedule tasks (not implemented)
    //uint8_t SortScheduleByPriority(Task * i_pSchedule); // - Sorts a schedule based on priority (not implemented)

    st_TaskInfo m_aTaskInfoStructs[NUMBER_OF_SLOTS]; // - Keeping all task structures saved
    uint8_t CollectMessages(void); // - Collects al messages from Tasks
    uint8_t DistributeMessages(void); // - Distributes messages between Tasks
    uint8_t InsertNode(st_Node *&st_pLinkedList, st_Message l_stNewMessage); // - Inserts node to linked list with mail
    uint8_t DistributeEraseFirstNode(st_Node *&st_pLinkedList, st_Message l_stMessage); // - Erases first node of linked list
    st_Node *m_pLinkedList; // - Linked list of messages
};



#endif /* TASKS_SCHEDULER_HPP_ */
