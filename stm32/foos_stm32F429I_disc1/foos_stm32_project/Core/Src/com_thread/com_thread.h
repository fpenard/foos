/**
 * @file com_thread.h
 * @brief Thread that allows the management of communication
 * @author fpenard
 *
 * @addtogroup COM_THREAD
 * @{
 *
 */

#ifndef SRC_COM_THREAD_H_
#define SRC_COM_THREAD_H_

// --------------------------------- Includes ----------------------------------

#include "cmsis_os.h"

// --------------------------------- Structures --------------------------------

/** @brief COM Thread - event list */
typedef enum COM_ThreadEvent
{
    COM_THREAD_EVENT_PING = 0U,
    COM_THREAD_EVENT_BTN_YELLOW_DEC_UP = 1U,
    COM_THREAD_EVENT_BTN_YELLOW_DEC_DOWN = 2U,
    COM_THREAD_EVENT_BTN_YELLOW_INC_UP = 3U,
    COM_THREAD_EVENT_BTN_YELLOW_INC_DOWN = 4U,
    COM_THREAD_EVENT_BTN_BLACK_DEC_UP = 5U,
    COM_THREAD_EVENT_BTN_BLACK_DEC_DOWN = 6U,
    COM_THREAD_EVENT_BTN_BLACK_INC_UP = 7U,
    COM_THREAD_EVENT_BTN_BLACK_INC_DOWN = 8U,
    COM_THREAD_EVENT_BTN_REPLAY_UP = 9U,
    COM_THREAD_EVENT_BTN_REPLAY_DOWN = 10U,
    COM_THREAD_EVENT_GOAL_YELLOW_DOWN = 11U,
    COM_THREAD_EVENT_GOAL_YELLOW_UP = 12U,
    COM_THREAD_EVENT_GOAL_BLACK_DOWN = 13U,
    COM_THREAD_EVENT_GOAL_BLACK_UP = 14U,
    COM_THREAD_EVENT_NUM = 15U
} COM_ThreadEvent_t;

// ----------------------- External function prototypes ------------------------

extern osThreadId COM_CreateThread(void);
extern void COM_SendEvent(COM_ThreadEvent_t event);

#endif /* SRC_COM_THREAD_H_ */

/** @} */
