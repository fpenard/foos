/**
 * @file gui_thread.c
 * @brief Thread that allows the management of GUI
 * @author fpenard
 *
 * @addtogroup GUI_THREAD
 * @{
 *
 */

// --------------------------------- Includes ----------------------------------

#include "gui_thread.h"
#include "events_init.h"
#include "gui_guider.h"
#include "lvgl/lvgl.h"
#include "lvgl_stm_hal/tft/tft.h"
#include "lvgl_stm_hal/touchpad/touchpad.h"

// ---------------------------------- Defines ----------------------------------

// --------------------------------- Structures --------------------------------

/** @brief GUI Thread - context structure */
typedef struct GUI_TaskContext
{
    osThreadId threadId; /**< GUI thread instance */
    lv_ui guiderUi;      /**< LVGL GUI guider instance */
} GUI_TaskContext_t;

// ------------------------ Static function prototypes -------------------------

static void _GUI_TaskMain(void const *argument);

// ----------------------------- Global variables ------------------------------

/** @brief GUI Thread - context declaration */
static GUI_TaskContext_t GUI_TaskCntxt;

// ------------------------ Extern function definitions -------------------------

/**
 * @brief  GUI_Thead - Create GUI_Thread
 *
 * Function steps:
 * - LVGL scheduler initilisation
 * - Touch-screen device initilisation
 * - LVGL UI instance initilisation
 * - Create timer for ping event
 * - Create thread
 *
 * @return thread instance
 */
osThreadId GUI_CreateThread(void)
{
    // LVGL scheduler initilisation
    lv_init();

    // Touch-screen device initilisation
    tft_init();
    touchpad_init();

    // LVGL UI instance initilisation
    setup_ui(&GUI_TaskCntxt.guiderUi);
    events_init(&GUI_TaskCntxt.guiderUi);

    // Create thread
    osThreadDef(guiTask, _GUI_TaskMain, osPriorityHigh, 0, 4096);
    GUI_TaskCntxt.threadId = osThreadCreate(osThread(guiTask), NULL);

    // Return thread instance
    return GUI_TaskCntxt.threadId;
}

// ------------------------ Static function definitions -------------------------

/**
 * @brief  GUI_Thead - main function
 *
 * Function steps:
 * - Start ping timer
 * - Infinite loop:
 * 		- Wait 3ms
 * 		- Refresh LGVL scheduler
 *
 * @param [in]	argument	Not used
 * @par Returns
 *    Nothing
 */
static void _GUI_TaskMain(void const *argument)
{

    // Infinite loop
    for (;;)
    {
        // Wait 3ms
        osDelay(3);

        //		Refresh LGVL scheduler
        lv_task_handler();
    }
}

/** @} */
