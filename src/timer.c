#include <pebble.h>
#include "timer.h"
#include "common.h"

MODE mode;
time_t leftTime;
static time_t timeStamp;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_34_medium_numbers;
static TextLayer *left_time;

static void initialise_ui(void) {
	s_window = window_create();
	window_set_background_color(s_window, GColorClear);
#ifndef PBL_SDK_3
	window_set_fullscreen(s_window, false);
#endif

	s_res_bitham_34_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS);
	// left_time
	left_time = text_layer_create(GRect(45, 48, 51, 40));
	text_layer_set_background_color(left_time, GColorClear);
	text_layer_set_text(left_time, "00");
	text_layer_set_text_alignment(left_time, GTextAlignmentCenter);
	text_layer_set_font(left_time, s_res_bitham_34_medium_numbers);
	layer_add_child(window_get_root_layer(s_window), (Layer *)left_time);
}

static void destroy_ui(void) {
	window_destroy(s_window);
	text_layer_destroy(left_time);
}
// END AUTO-GENERATED UI CODE

static void set_timeStamp(uint8_t minuts)
{
	leftTime = 60 * minuts;
	timeStamp = time(NULL) + leftTime;
}

static void draw_timer(void)
{
	window_set_background_color(s_window, GColorGreen);
	text_layer_set_text(left_time, leftTime/60 + 1);

	window_stack_push(s_window, true);
}

static void mode_reverse(void)
{
	switch mode{
	case start:
		set_timeStamp(25);
		mode = work;
		break;
	case work:
		set_timeStamp(5);
		mode = rest;
		break;
	case rest:
		set_timeStamp(25);
		mode = work;
		break;
	/* default: */
	/* 	mode = start; */
	/* 	break; */
	}
	app_timer_register(0, timer_handler, NULL);
	draw_timer();
}

static void timer_handler(void *data) {
	leftTime = timeStamp - time(NULL);
	draw_timer();

	if(leftTime<1){
		vibes_double_pulse();
		mode_reverse();
	}else{
	// 1000ms後にまたこの関数を実行
	app_timer_register(1000, timer_handler, data);
	}
}

static void handle_window_unload(Window* window) {
	destroy_ui();
}


// click
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	if(mode==start) mode_reverse();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
}

static void click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

void show_timer(void) {
	initialise_ui();

	window_set_window_handlers(s_window, (WindowHandlers) {
			.unload = handle_window_unload,
			});

	window_set_click_config_provider(s_window, click_config_provider);

	set_timeStamp(25);
	draw_timer();
}

	void hide_timer(void) {
		window_stack_remove(s_window, true);
	}
