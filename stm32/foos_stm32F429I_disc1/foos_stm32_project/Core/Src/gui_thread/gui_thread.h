/**
 * @file gui_thread.h
 * @brief Thread that allows the management of GUI
 * @author fpenard
 *
 * @addtogroup GUI_THREAD
 * @{
 *
 */

#ifndef SRC_GUI_THREAD_H_
#define SRC_GUI_THREAD_H_

// --------------------------------- Includes ----------------------------------

#include "cmsis_os.h"

// ----------------------- External function prototypes ------------------------

extern osThreadId GUI_CreateThread(void);

#endif /* SRC_GUI_THREAD_H_ */

/** @} */
