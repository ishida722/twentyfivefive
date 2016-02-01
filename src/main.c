#include <pebble.h>

const bool animated = true;
static Window *standby_window;



static void standby_window_load(Window *window)
{
}

static void standby_window_unload(Window *window)
{
}

/* WindowHandlers standby_window_handler */



static void init(void) {
	standby_window = window_create();
	window_set_window_handlers(standby_window, (WindowHandlers) {
			.load = standby_window_load,
			.unload = standby_window_unload,
			});
	window_stack_push(standby_window, animated);
}

static void deinit(void) {
	window_destroy(standby_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
