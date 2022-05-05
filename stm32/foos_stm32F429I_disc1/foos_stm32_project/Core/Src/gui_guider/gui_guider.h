/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *screen;
	lv_obj_t *screen_img_1;
	lv_obj_t *screen_imgbtn_1;
	lv_obj_t *screen_imgbtn_1_label;
	lv_obj_t *screen_imgbtn_2;
	lv_obj_t *screen_imgbtn_2_label;
	lv_obj_t *screen_imgbtn_3;
	lv_obj_t *screen_imgbtn_3_label;
	lv_obj_t *screen_imgbtn_4;
	lv_obj_t *screen_imgbtn_4_label;
	lv_obj_t *screen_imgbtn_5;
	lv_obj_t *screen_imgbtn_5_label;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);
LV_IMG_DECLARE(_replay_alpha_80x80);
LV_IMG_DECLARE(_minussign_circle_alpha_80x78);
LV_IMG_DECLARE(_plussign_alpha_80x80);
LV_IMG_DECLARE(_cc1_240x320);
LV_IMG_DECLARE(_plussign_circle_alpha_80x80);
LV_IMG_DECLARE(_dots_vertical_alpha_80x80);
LV_IMG_DECLARE(_plussign_alpha_80x78);
LV_IMG_DECLARE(_plussign_circle_alpha_80x78);
LV_IMG_DECLARE(_minussign_alpha_80x78);

#ifdef __cplusplus
}
#endif
#endif
