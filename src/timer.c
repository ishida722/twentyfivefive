#include <pebble.h>
#include "timer.h"

#define WAKEUP_REASON 0

enum { PERSIST_TIME_STAMP,
	   PERSIST_MODE,
	   WAKEUP_ID_KEY
};

typedef enum{start, work, rest}MODE;

static StatusBarLayer *s_status_bar;

static MODE mode = start;
static int leftTime;
static time_t timeStamp;
static _Bool timerEnable = false;
static GColor bgColor;
static Wakeupid s_wakeup_id;

// prottype

static void mode_reverse(void);
static void mode_change(MODE nextMode);
static void draw_timer(void);

//////////////////////////////////////////////////////////////////////////////////
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_34_medium_numbers;
static TextLayer *left_time;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorClear);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, 0);
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
//////////////////////////////////////////////////////////////////////////////////

static void timeout(void)
{
	vibes_double_pulse();
	if(persist_exists(PERSIST_TIME_STAMP))
		persist_delete(PERSIST_TIME_STAMP);
	mode_reverse();
}

static void timer_handler(void *data) {
    if(!timerEnable) return;
	leftTime = timeStamp - time(NULL);
	draw_timer();

	if(leftTime<1){
		timeout();
	}else{
	app_timer_register(1000, timer_handler, data);
	}
}

static void set_timeStamp(uint8_t minuts)
{
    if(!persist_exists(PERSIST_TIME_STAMP)){
        timerEnable = true;
        leftTime = 60 * minuts - 1;
        timeStamp = time(NULL) + leftTime;
        persist_write_int(PERSIST_TIME_STAMP, timeStamp);
    }
}

static void start_timer(void)
{
	timerEnable = true;
	app_timer_register(0, timer_handler, NULL);
}

static void stop_timer(void)
{
	timerEnable = false;
	if(persist_exists(PERSIST_TIME_STAMP))
		persist_delete(PERSIST_TIME_STAMP);
}

static void draw_timer(void)
{
	static char time_text[]="00";
	char leftMinuts;

	window_set_background_color(s_window, bgColor);
	leftMinuts = leftTime/60 + 1;
	snprintf(time_text, sizeof(time_text), "%d", leftMinuts);
	text_layer_set_text(left_time, time_text);
}


static void mode_change(MODE nextMode)
{
	switch(nextMode){
	case start:
        leftTime = 60*25-1;
		bgColor = GColorBlue;
		stop_timer();
		break;
	case rest:
		set_timeStamp(5);
		bgColor = GColorGreen;
		start_timer();
		break;
	case work:
		set_timeStamp(25);
		bgColor = GColorRed;
		start_timer();
		break;
	}
	mode = nextMode;
	persist_write_int(PERSIST_MODE, nextMode);
	draw_timer();
}

static void mode_reverse(void)
{
	switch(mode){
    case start:
        break;
	case work:
		mode_change(rest);
		break;
	case rest:
		mode_change(work);
		break;
	}
}

// click
//////////////////////////////////////////////////////////////////////////////////
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    if(mode==work || mode==rest) mode_change(start);
	else mode_change(work);
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
//////////////////////////////////////////////////////////////////////////////////

static void handle_window_unload(Window* window) {
	destroy_ui();
}

void check_persist(void)
{
	if(!persist_exists(PERSIST_MODE)){
		mode = start;
		persist_write_int(PERSIST_MODE, mode);
	}else{
		mode = persist_read_int(PERSIST_MODE);
		if(persist_exists(PERSIST_TIME_STAMP))
				timeStamp = persist_read_int(PERSIST_TIME_STAMP);
	}
}

void show_timer(void) {
	initialise_ui();
	s_status_bar = status_bar_layer_create();
	layer_add_child(window_get_root_layer(s_window), status_bar_layer_get_layer(s_status_bar));

	window_set_window_handlers(s_window, (WindowHandlers) {
			.unload = handle_window_unload,
			});

	window_set_click_config_provider(s_window, click_config_provider);

	window_stack_push(s_window, true);
	mode_change(mode);
}

void hide_timer(void) {
	window_stack_remove(s_window, true);
}
