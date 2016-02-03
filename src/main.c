#include <pebble.h>

const bool animated = true;
static Window *standby_window;
static Window *rest_window;
static Window *work_window;



static void standby_window_load(Window *window)
{
}

static void standby_window_unload(Window *window)
{
}

static void work_window_load(Window *window)
{
}

static void work_window_unload(Window *window)
{
}

static void rest_window_load(Window *window)
{
}

static void rest_window_unload(Window *window)
{
}

/* WindowHandlers standby_window_handler */

static void up_click_handler(ClickRecognizerRef recognizer, void *context)
{
	window_stack_push(standby_window, animated);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
	window_stack_push(work_window, animated);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
	window_stack_push(rest_window, animated);
}

static void click_config_provider(void *context)
{
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}


static void init(void) {
	standby_window = window_create();
	window_set_window_handlers(standby_window, (WindowHandlers) {
			.load = standby_window_load,
			.unload = standby_window_unload,
			});
	window_set_window_handlers(work_window, (WindowHandlers) {
			.load = work_window_load,
			.unload = work_window_unload,
			});
	window_set_window_handlers(rest_window, (WindowHandlers) {
			.load = rest_window_load,
			.unload = rest_window_unload,
			});
	window_set_background_color(standby_window, GColorRed);
	window_set_background_color(work_window, GColorBlue);
	window_set_background_color(rest_window, GColorGreen);
	window_set_click_config_provider(standby_window, click_config_provider);
	window_set_click_config_provider(work_window, click_config_provider);
	window_set_click_config_provider(rest_window, click_config_provider);
	window_stack_push(standby_window);
}

static void deinit(void) {
	window_destroy(standby_window);
	window_destroy(work_window);
	window_destroy(rest_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
