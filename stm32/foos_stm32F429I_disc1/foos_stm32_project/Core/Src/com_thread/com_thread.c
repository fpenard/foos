/**
 * @file com_thread.c
 * @brief Thread that allows the management of communication
 * @author fpenard
 *
 * @addtogroup COM_THREAD
 * @{
 *
 */

// --------------------------------- Includes ----------------------------------

#include "com_thread.h"
#include "main.h"
#include <stdint.h>
#include <stdio.h>

// ---------------------------------- Defines ----------------------------------

#define COM_PING_INTERVAL_MS 5000U /**< Send Pings 'P' every 5000 ms */
#define COM_BTN_INTERVAL_MS 10U    /**< Check buttons every 10 ms */

#define COM_PING_CMD_STR "P\n"                 /**< Ping command string */
#define COM_GOAL_BLACK_CMD_STR "BG %lu %lu\n"  /**< Black goal command pre-formatted string */
#define COM_GOAL_YELLOW_CMD_STR "YG %lu %lu\n" /**< Yellow goal command pre-formatted string */

// --------------------------------- Structures --------------------------------

/** @brief COM Thread - button list */
typedef enum COM_BtnId
{
    COM_BTN_YELLOW_DEC,
    COM_BTN_YELLOW_INC,
    COM_BTN_BLACK_DEC,
    COM_BTN_BLACK_INC,
    COM_BTN_REPLAY
} COM_BtnId_t;

/** @brief COM Thread - button status */
typedef enum COM_BtnStatus
{
    COM_BTN_DOWN,
    COM_BTN_UP
} COM_BtnStatus_t;

/** @brief COM Thread - goal team */
typedef enum COM_GoalTeam
{
    COM_GOAL_TEAM_BLACK = 0U,
    COM_GOAL_TEAM_YELLOW = 1U,
    COM_GOAL_TEAM_NUM = 2U
} COM_GoalTeam_t;

/** @brief COM Thread - goal status structure */
typedef struct COM_GoalStat
{
    uint32_t goalTickTime; /**< OS tick time of the last goal */
    uint32_t offTickTime;  /**< OS tick time of the last goal off period */
} COM_GoalStat_t;

/** @brief COM Thread - context structure */
typedef struct COM_TaskContext
{
    osThreadId threadId;                        /**< COM thread instance */
    osTimerId timerId;                          /**< Ping timer instance */
    osMutexId goalMutex;                        /**< Goal mutex instance */
    COM_GoalTeam_t goalTeamId;                  /**< Team identifier of the last goal */
    COM_GoalStat_t goalStat[COM_GOAL_TEAM_NUM]; /**< Goal status of each team */
} COM_TaskContext_t;

/** @brief COM Thread - event function callback type definition */
typedef void (*COM_TaskFunc_t)(COM_ThreadEvent_t);

/** @brief COM Thread - event item type definition */
typedef struct
{
    COM_ThreadEvent_t event;            /**< COM thread event identifier */
    void (*evtFunc)(COM_ThreadEvent_t); /**< COM thread envent callback function pointer */
} COM_TaskSmEvt_t;

// ------------------------ Static function prototypes -------------------------

static void _COM_SendPingCmd(void);
static void _COM_SendBtnCmd(COM_BtnId_t btnId, COM_BtnStatus_t btnState);
static void _COM_SendGoalCmd(COM_GoalTeam_t goalTeam, uint32_t usDuration, uint32_t usElapsed);

static void _COM_TaskMain(void const *argument);
static void _COM_TaskEvtPing(COM_ThreadEvent_t evtFlag);
static void _COM_TaskEvtBtn(COM_ThreadEvent_t evtFlag);
static void _COM_TaskEvtGoalStart(COM_ThreadEvent_t evtFlag);
static void _COM_TaskEvtGoalEnd(COM_ThreadEvent_t evtFlag);

static void _COM_TaskPingTimerCallback(void const *arg);

// ----------------------------- Global variables ------------------------------

/** @brief COM Thread - button command conversion const array */
const char *btnEvents[5][2] = {
    {"YD_D", "YD_U"}, {"YI_D", "YI_U"}, {"BD_D", "BD_U"}, {"BI_D", "BI_U"}, {"OK_D", "OK_U"}};

/** @brief COM Thread - context declaration */
static COM_TaskContext_t COM_TaskCntxt;

/** @brief COM Thread - event management array */
static COM_TaskSmEvt_t _COM_TaskSmEvtArr[COM_THREAD_EVENT_NUM] = {
    {COM_THREAD_EVENT_PING, _COM_TaskEvtPing},
    {COM_THREAD_EVENT_BTN_YELLOW_DEC_UP, _COM_TaskEvtBtn},
    {COM_THREAD_EVENT_BTN_YELLOW_DEC_DOWN, _COM_TaskEvtBtn},
    {COM_THREAD_EVENT_BTN_YELLOW_INC_UP, _COM_TaskEvtBtn},
    {COM_THREAD_EVENT_BTN_YELLOW_INC_DOWN, _COM_TaskEvtBtn},
    {COM_THREAD_EVENT_BTN_BLACK_DEC_UP, _COM_TaskEvtBtn},
    {COM_THREAD_EVENT_BTN_BLACK_DEC_DOWN, _COM_TaskEvtBtn},
    {COM_THREAD_EVENT_BTN_BLACK_INC_UP, _COM_TaskEvtBtn},
    {COM_THREAD_EVENT_BTN_BLACK_INC_DOWN, _COM_TaskEvtBtn},
    {COM_THREAD_EVENT_BTN_REPLAY_UP, _COM_TaskEvtBtn},
    {COM_THREAD_EVENT_BTN_REPLAY_DOWN, _COM_TaskEvtBtn},
    {COM_THREAD_EVENT_GOAL_YELLOW_UP, _COM_TaskEvtGoalEnd},
    {COM_THREAD_EVENT_GOAL_YELLOW_DOWN, _COM_TaskEvtGoalStart},
    {COM_THREAD_EVENT_GOAL_BLACK_UP, _COM_TaskEvtGoalEnd},
    {COM_THREAD_EVENT_GOAL_BLACK_DOWN, _COM_TaskEvtGoalStart}};

// ------------------------ Extern function definitions -------------------------

/**
 * @brief  COM_Thead - Create COM_Thread
 *
 * Function steps:
 * - Context initialisation
 * - Create timer for ping event
 * - Create thread
 *
 * @return thread instance
 */
osThreadId COM_CreateThread(void)
{
    // Context initialisation
    for (COM_GoalTeam_t teamId = 0; teamId < COM_GOAL_TEAM_NUM; teamId++)
    {
        COM_TaskCntxt.goalStat[teamId].goalTickTime = 0;
        COM_TaskCntxt.goalStat[teamId].offTickTime = 0;
    }
    osMutexDef(comMutexGoal);
    COM_TaskCntxt.goalMutex = osMutexCreate(osMutex(comMutexGoal));
    COM_TaskCntxt.goalTeamId = COM_GOAL_TEAM_BLACK;

    // Create timer for ping event
    osTimerDef(comPingTimer, _COM_TaskPingTimerCallback);
    COM_TaskCntxt.timerId = osTimerCreate(osTimer(comPingTimer), osTimerPeriodic, NULL);

    // Create thread
    osThreadDef(comTask, _COM_TaskMain, osPriorityHigh, 0, 1096);
    COM_TaskCntxt.threadId = osThreadCreate(osThread(comTask), NULL);

    // Return thread instance
    return COM_TaskCntxt.threadId;
}

/**
 * @brief  COM_Thead - Send event
 *
 * Function steps:
 * - Check and send event to COM thread
 *
 * @param [in]	event		Event identifier
 * @par Returns
 *    Nothing
 */
void COM_SendEvent(COM_ThreadEvent_t event)
{
    // check and send event to COM thread
    if (event < COM_THREAD_EVENT_NUM)
    {
        osSignalSet(COM_TaskCntxt.threadId, 0x01 << event);
    }
}

// ------------------------ Static function definitions -------------------------

/**
 * @brief  COM_Thead - Send ping command
 *
 * Function steps:
 * - Send ping command
 *
 * @return None
 */
static void _COM_SendPingCmd(void)
{
    // Send ping command
    printf(COM_PING_CMD_STR);
}

/**
 * @brief  COM_Thead - Send button command
 *
 * Function steps:
 * - Get command from button identifier and state
 * - Send button command
 *
 * @param [in]	btnId		Button identifier
 * @param [in]	btnState	Button state
 * @return None
 */
static void _COM_SendBtnCmd(COM_BtnId_t btnId, COM_BtnStatus_t btnState)
{
    // Get command from button identifier and state
    // Send button command
    printf(btnEvents[btnId][btnState]);
    printf("\n");
}

/**
 * @brief  COM_Thead - Send goal command
 *
 * Function steps:
 * - Format command depending on input parameters
 * - Send goal command
 *
 * @param [in]	goalTeam	Team identifier of the goal
 * @param [in]	usDuration	Goal detection time duration (in us)
 * @param [in]	usElapsed	Goal elapsed time duration (in us)
 * @return None
 */
static void _COM_SendGoalCmd(COM_GoalTeam_t goalTeam, uint32_t usDuration, uint32_t usElapsed)
{
    char cmdStr[100];

    // Format command depending on input parameters
    switch (goalTeam)
    {
    case COM_GOAL_TEAM_BLACK:
        sprintf(cmdStr, COM_GOAL_BLACK_CMD_STR, (unsigned long)usDuration, (unsigned long)usElapsed);
        break;
    case COM_GOAL_TEAM_YELLOW:
        sprintf(cmdStr, COM_GOAL_YELLOW_CMD_STR, (unsigned long)usDuration, (unsigned long)usElapsed);
        break;
    default:
        return;
    }

    // Send goal command
    printf(cmdStr);
}

/**
 * @brief  COM_Thread - main function
 *
 * Function steps:
 * - Start ping timer
 * - Infinite loop:
 * 		- Wait for event
 * 		- Detect event and launch callback function
 *
 * @param [in]	argument	Not used
 * @return None
 */
static void _COM_TaskMain(void const *argument)
{
    // Start ping timer
    osTimerStart(COM_TaskCntxt.timerId, COM_PING_INTERVAL_MS);

    // Infinite loop
    for (;;)
    {
        // Wait for event
        osEvent event = osSignalWait((0xFFFFFFFF >> (32U - COM_THREAD_EVENT_NUM)), osWaitForever);

        // Detect event and launch callback function
        if (event.status == osEventSignal)
        {
            for (uint32_t i = 0; i < COM_THREAD_EVENT_NUM; i++)
            {
                if (((event.value.signals >> i) & 0x01) != 0)
                {
                    COM_ThreadEvent_t evtFlag = _COM_TaskSmEvtArr[i].event;
                    _COM_TaskSmEvtArr[i].evtFunc(evtFlag);
                }
            }
        }
    }
}

/**
 * @brief  COM_Thread - Ping event callback function
 *
 * Function steps:
 * - Send command and wait 10ms
 *
 * @param [in]	evtFlag		Event flag identifier
 * @return None
 */
static void _COM_TaskEvtPing(COM_ThreadEvent_t evtFlag)
{
    // Send command and wait 10ms
    _COM_SendPingCmd();
    osDelay(10);
}

/**
 * @brief  COM_Thread - Button event callback function
 *
 * Function steps:
 * - Send command depending on input event identifier
 * - Wait button command interval time
 *
 * @param [in]	evtFlag		Event flag identifier
 * @return None
 */
static void _COM_TaskEvtBtn(COM_ThreadEvent_t evtFlag)
{
    // Send command depending on input event identifier
    switch (evtFlag)
    {
    case COM_THREAD_EVENT_BTN_YELLOW_DEC_UP:
        _COM_SendBtnCmd(COM_BTN_YELLOW_DEC, COM_BTN_UP);
        break;
    case COM_THREAD_EVENT_BTN_YELLOW_DEC_DOWN:
        _COM_SendBtnCmd(COM_BTN_YELLOW_DEC, COM_BTN_DOWN);
        break;
    case COM_THREAD_EVENT_BTN_YELLOW_INC_UP:
        _COM_SendBtnCmd(COM_BTN_YELLOW_INC, COM_BTN_UP);
        break;
    case COM_THREAD_EVENT_BTN_YELLOW_INC_DOWN:
        _COM_SendBtnCmd(COM_BTN_YELLOW_INC, COM_BTN_DOWN);
        break;
    case COM_THREAD_EVENT_BTN_BLACK_DEC_UP:
        _COM_SendBtnCmd(COM_BTN_BLACK_DEC, COM_BTN_UP);
        break;
    case COM_THREAD_EVENT_BTN_BLACK_DEC_DOWN:
        _COM_SendBtnCmd(COM_BTN_BLACK_DEC, COM_BTN_DOWN);
        break;
    case COM_THREAD_EVENT_BTN_BLACK_INC_UP:
        _COM_SendBtnCmd(COM_BTN_BLACK_INC, COM_BTN_UP);
        break;
    case COM_THREAD_EVENT_BTN_BLACK_INC_DOWN:
        _COM_SendBtnCmd(COM_BTN_BLACK_INC, COM_BTN_DOWN);
        break;
    case COM_THREAD_EVENT_BTN_REPLAY_UP:
        _COM_SendBtnCmd(COM_BTN_REPLAY, COM_BTN_UP);
        break;
    case COM_THREAD_EVENT_BTN_REPLAY_DOWN:
        _COM_SendBtnCmd(COM_BTN_REPLAY, COM_BTN_DOWN);
        break;
    default:
        return;
    }

    // Wait button command interval time
    osDelay(COM_BTN_INTERVAL_MS);
}

/**
 * @brief  COM_Thread - Goal start event callback function
 *
 * Function steps:
 * - Determine goal team identifier
 * - Lock goal detection and update goal statistics
 *
 * @param [in]	evtFlag		Event flag identifier
 * @return None
 */
static void _COM_TaskEvtGoalStart(COM_ThreadEvent_t evtFlag)
{
    COM_GoalTeam_t teamId = COM_GOAL_TEAM_BLACK;

    // Determine goal team identifier
    switch (evtFlag)
    {
    case COM_THREAD_EVENT_GOAL_YELLOW_DOWN:
        teamId = COM_GOAL_TEAM_YELLOW;
        break;
    case COM_THREAD_EVENT_GOAL_BLACK_DOWN:
        teamId = COM_GOAL_TEAM_BLACK;
        break;
    default:
        return;
    }

    // Lock goal detection and update goal statistics
    if (osMutexWait(COM_TaskCntxt.goalMutex, 0) == osOK)
    {
        COM_TaskCntxt.goalTeamId = teamId;
        COM_TaskCntxt.goalStat[COM_TaskCntxt.goalTeamId].goalTickTime = osKernelSysTick();
    }
}

/**
 * @brief  COM_Thread - Goal end event callback function
 *
 * Function steps:
 * - Determine goal team identifier
 * - Unlock goal detection, update goal statistics and send goal detection command
 *
 * @param [in]	evtFlag		Event flag identifier
 * @return None
 */
static void _COM_TaskEvtGoalEnd(COM_ThreadEvent_t evtFlag)
{
    COM_GoalTeam_t teamId = COM_GOAL_TEAM_BLACK;

    // Determine goal team identifier
    switch (evtFlag)
    {
    case COM_THREAD_EVENT_GOAL_YELLOW_UP:
        teamId = COM_GOAL_TEAM_YELLOW;
        break;
    case COM_THREAD_EVENT_GOAL_BLACK_UP:
        teamId = COM_GOAL_TEAM_BLACK;
        break;
    default:
        return;
    }

    // Unlock goal detection, update goal statistics and send goal detection command
    if ((teamId == COM_TaskCntxt.goalTeamId) && (osMutexWait(COM_TaskCntxt.goalMutex, 0) != osOK))
    {
        uint32_t now = osKernelSysTick();
        uint32_t usDuration = (now - COM_TaskCntxt.goalStat[teamId].goalTickTime) * configTICK_RATE_HZ;
        uint32_t usElapsed = (COM_TaskCntxt.goalStat[COM_TaskCntxt.goalTeamId].goalTickTime -
                              COM_TaskCntxt.goalStat[COM_TaskCntxt.goalTeamId].offTickTime) *
                             configTICK_RATE_HZ;
        _COM_SendGoalCmd(teamId, usDuration, usElapsed);

        COM_TaskCntxt.goalStat[COM_TaskCntxt.goalTeamId].offTickTime = now;
        osMutexRelease(COM_TaskCntxt.goalMutex);
    }
}

/**
 * @brief  COM_Thread - Ping timer callback function
 *
 * Function steps:
 * - Send COM_THREAD_EVENT_PING event to COM_Thread
 *
 * @param [in]  arg		Not used
 * @return None
 */
static void _COM_TaskPingTimerCallback(void const *arg)
{
    // Send event to COM_Thread
    COM_SendEvent(COM_THREAD_EVENT_PING);
}

//! \todo: to delete

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == B1_Pin)
    {
        if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
        { // check pin state
            COM_SendEvent(COM_THREAD_EVENT_GOAL_YELLOW_UP);
        }
        else
        {
            COM_SendEvent(COM_THREAD_EVENT_GOAL_YELLOW_DOWN);
        }
    }
}

/** @} */
