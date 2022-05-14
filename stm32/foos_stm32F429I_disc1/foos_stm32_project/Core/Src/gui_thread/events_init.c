/**
 * @file events_init.c
 * @brief SW layer that allows the management of GUI events
 * @author fpenard
 *
 * @addtogroup GUI_EVT_INIT
 * @{
 *
 */

// --------------------------------- Includes ----------------------------------

#include "events_init.h"
#include "com_thread.h"
#include "lvgl/lvgl.h"
#include <stdio.h>

// ------------------------ Static function prototypes -------------------------

static void event_cb(lv_event_t *e);

// ------------------------ Extern function definitions -------------------------

/**
 * @brief  Event_init - LVGL button event management layer init
 *
 * Function steps:
 * - Connect callback function and specify callback arguments, to each button events
 *
 * @param [in]	ui			Pointer to LVGL GUI guider instance
 * @par Returns
 *    Nothing
 */
void events_init(lv_ui *ui)
{
    // Connect callback function and specify callback arguments, to each button events
    lv_obj_add_event_cb(ui->screen_imgbtn_1, event_cb, LV_EVENT_PRESSED, COM_THREAD_EVENT_BTN_YELLOW_INC_DOWN);
    lv_obj_add_event_cb(ui->screen_imgbtn_1, event_cb, LV_EVENT_RELEASED, COM_THREAD_EVENT_BTN_YELLOW_INC_UP);
    lv_obj_add_event_cb(ui->screen_imgbtn_2, event_cb, LV_EVENT_PRESSED, COM_THREAD_EVENT_BTN_BLACK_INC_DOWN);
    lv_obj_add_event_cb(ui->screen_imgbtn_2, event_cb, LV_EVENT_RELEASED, COM_THREAD_EVENT_BTN_BLACK_INC_UP);
    lv_obj_add_event_cb(ui->screen_imgbtn_3, event_cb, LV_EVENT_PRESSED, COM_THREAD_EVENT_BTN_YELLOW_DEC_DOWN);
    lv_obj_add_event_cb(ui->screen_imgbtn_3, event_cb, LV_EVENT_RELEASED, COM_THREAD_EVENT_BTN_YELLOW_DEC_UP);
    lv_obj_add_event_cb(ui->screen_imgbtn_4, event_cb, LV_EVENT_PRESSED, COM_THREAD_EVENT_BTN_BLACK_DEC_DOWN);
    lv_obj_add_event_cb(ui->screen_imgbtn_4, event_cb, LV_EVENT_RELEASED, COM_THREAD_EVENT_BTN_BLACK_DEC_UP);
    lv_obj_add_event_cb(ui->screen_imgbtn_5, event_cb, LV_EVENT_PRESSED, COM_THREAD_EVENT_BTN_REPLAY_DOWN);
    lv_obj_add_event_cb(ui->screen_imgbtn_5, event_cb, LV_EVENT_RELEASED, COM_THREAD_EVENT_BTN_REPLAY_UP);
}

// ------------------------ Static function definitions -------------------------

/**
 * @brief  Event_init - Button callback function
 *
 * Function steps:
 * - Get event identifier from callback argument
 * - Send event to COM_Thread
 *
 * @param [in]	e			Callback argument
 * @return None
 */
static void event_cb(lv_event_t *e)
{
    // Get event identifier from callback argument
    uint32_t user_data = lv_event_get_user_data(e);

    // Send event to COM_Thread
    COM_SendEvent(user_data);
}

/** @} */
