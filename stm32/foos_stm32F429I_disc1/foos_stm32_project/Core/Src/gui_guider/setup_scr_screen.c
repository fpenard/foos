/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
//#include "custom.h"


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	lv_style_reset(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_main_main_default, 0);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_1
	ui->screen_img_1 = lv_img_create(ui->screen);
	lv_obj_set_pos(ui->screen_img_1, 0, 0);
	lv_obj_set_size(ui->screen_img_1, 240, 320);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_1_main_main_default
	static lv_style_t style_screen_img_1_main_main_default;
	lv_style_reset(&style_screen_img_1_main_main_default);
	lv_style_set_img_recolor(&style_screen_img_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_img_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_img_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_img_1, &style_screen_img_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_1,&_cc1_240x320);
	lv_img_set_pivot(ui->screen_img_1, 0,0);
	lv_img_set_angle(ui->screen_img_1, 0);

	//Write codes screen_imgbtn_1
	ui->screen_imgbtn_1 = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgbtn_1, 153, 7);
	lv_obj_set_size(ui->screen_imgbtn_1, 80, 80);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgbtn_1_main_main_default
	static lv_style_t style_screen_imgbtn_1_main_main_default;
	lv_style_reset(&style_screen_imgbtn_1_main_main_default);
	lv_style_set_text_color(&style_screen_imgbtn_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgbtn_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgbtn_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgbtn_1, &style_screen_imgbtn_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgbtn_1_main_main_pressed
	static lv_style_t style_screen_imgbtn_1_main_main_pressed;
	lv_style_reset(&style_screen_imgbtn_1_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgbtn_1_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_1_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_1_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgbtn_1, &style_screen_imgbtn_1_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgbtn_1_main_main_checked
	static lv_style_t style_screen_imgbtn_1_main_main_checked;
	lv_style_reset(&style_screen_imgbtn_1_main_main_checked);
	lv_style_set_text_color(&style_screen_imgbtn_1_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_1_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_1_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgbtn_1, &style_screen_imgbtn_1_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_plussign_alpha_80x80, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, &_plussign_circle_alpha_80x80, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_plussign_alpha_80x80, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_plussign_circle_alpha_80x80, NULL);
	lv_obj_add_flag(ui->screen_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_imgbtn_2
	ui->screen_imgbtn_2 = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgbtn_2, 153, 236);
	lv_obj_set_size(ui->screen_imgbtn_2, 80, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgbtn_2_main_main_default
	static lv_style_t style_screen_imgbtn_2_main_main_default;
	lv_style_reset(&style_screen_imgbtn_2_main_main_default);
	lv_style_set_text_color(&style_screen_imgbtn_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgbtn_2_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_2_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgbtn_2_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgbtn_2, &style_screen_imgbtn_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgbtn_2_main_main_pressed
	static lv_style_t style_screen_imgbtn_2_main_main_pressed;
	lv_style_reset(&style_screen_imgbtn_2_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgbtn_2_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_2_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_2_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgbtn_2, &style_screen_imgbtn_2_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgbtn_2_main_main_checked
	static lv_style_t style_screen_imgbtn_2_main_main_checked;
	lv_style_reset(&style_screen_imgbtn_2_main_main_checked);
	lv_style_set_text_color(&style_screen_imgbtn_2_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_2_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_2_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgbtn_2, &style_screen_imgbtn_2_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, &_plussign_alpha_80x78, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, &_plussign_circle_alpha_80x78, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_plussign_alpha_80x78, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_plussign_circle_alpha_80x78, NULL);
	lv_obj_add_flag(ui->screen_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_imgbtn_3
	ui->screen_imgbtn_3 = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgbtn_3, 7, 7);
	lv_obj_set_size(ui->screen_imgbtn_3, 80, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgbtn_3_main_main_default
	static lv_style_t style_screen_imgbtn_3_main_main_default;
	lv_style_reset(&style_screen_imgbtn_3_main_main_default);
	lv_style_set_text_color(&style_screen_imgbtn_3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgbtn_3_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_3_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgbtn_3_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgbtn_3, &style_screen_imgbtn_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgbtn_3_main_main_pressed
	static lv_style_t style_screen_imgbtn_3_main_main_pressed;
	lv_style_reset(&style_screen_imgbtn_3_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgbtn_3_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_3_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_3_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgbtn_3, &style_screen_imgbtn_3_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgbtn_3_main_main_checked
	static lv_style_t style_screen_imgbtn_3_main_main_checked;
	lv_style_reset(&style_screen_imgbtn_3_main_main_checked);
	lv_style_set_text_color(&style_screen_imgbtn_3_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_3_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_3_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgbtn_3, &style_screen_imgbtn_3_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, &_minussign_alpha_80x78, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, &_minussign_circle_alpha_80x78, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_minussign_alpha_80x78, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_minussign_circle_alpha_80x78, NULL);
	lv_obj_add_flag(ui->screen_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_imgbtn_4
	ui->screen_imgbtn_4 = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgbtn_4, 8, 235);
	lv_obj_set_size(ui->screen_imgbtn_4, 80, 78);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgbtn_4_main_main_default
	static lv_style_t style_screen_imgbtn_4_main_main_default;
	lv_style_reset(&style_screen_imgbtn_4_main_main_default);
	lv_style_set_text_color(&style_screen_imgbtn_4_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgbtn_4_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_4_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgbtn_4_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgbtn_4, &style_screen_imgbtn_4_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgbtn_4_main_main_pressed
	static lv_style_t style_screen_imgbtn_4_main_main_pressed;
	lv_style_reset(&style_screen_imgbtn_4_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgbtn_4_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_4_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_4_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgbtn_4, &style_screen_imgbtn_4_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgbtn_4_main_main_checked
	static lv_style_t style_screen_imgbtn_4_main_main_checked;
	lv_style_reset(&style_screen_imgbtn_4_main_main_checked);
	lv_style_set_text_color(&style_screen_imgbtn_4_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_4_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_4_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgbtn_4, &style_screen_imgbtn_4_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, &_minussign_alpha_80x78, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, &_minussign_circle_alpha_80x78, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_minussign_alpha_80x78, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_4, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_minussign_circle_alpha_80x78, NULL);
	lv_obj_add_flag(ui->screen_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_imgbtn_5
	ui->screen_imgbtn_5 = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgbtn_5, 87, 121);
	lv_obj_set_size(ui->screen_imgbtn_5, 80, 80);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgbtn_5_main_main_default
	static lv_style_t style_screen_imgbtn_5_main_main_default;
	lv_style_reset(&style_screen_imgbtn_5_main_main_default);
	lv_style_set_text_color(&style_screen_imgbtn_5_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor(&style_screen_imgbtn_5_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_5_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgbtn_5_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgbtn_5, &style_screen_imgbtn_5_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgbtn_5_main_main_pressed
	static lv_style_t style_screen_imgbtn_5_main_main_pressed;
	lv_style_reset(&style_screen_imgbtn_5_main_main_pressed);
	lv_style_set_text_color(&style_screen_imgbtn_5_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_5_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_5_main_main_pressed, 0);
	lv_obj_add_style(ui->screen_imgbtn_5, &style_screen_imgbtn_5_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgbtn_5_main_main_checked
	static lv_style_t style_screen_imgbtn_5_main_main_checked;
	lv_style_reset(&style_screen_imgbtn_5_main_main_checked);
	lv_style_set_text_color(&style_screen_imgbtn_5_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_5_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_5_main_main_checked, 0);
	lv_obj_add_style(ui->screen_imgbtn_5, &style_screen_imgbtn_5_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgbtn_5, LV_IMGBTN_STATE_RELEASED, NULL, &_replay_alpha_80x80, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_5, LV_IMGBTN_STATE_PRESSED, NULL, &_dots_vertical_alpha_80x80, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_5, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_replay_alpha_80x80, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_5, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_dots_vertical_alpha_80x80, NULL);
	lv_obj_add_flag(ui->screen_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
}
