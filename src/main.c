#include <pebble.h>
#include "standby.h"

const bool animated = true;

static void init(void) {
	show_standby();
}

static void deinit(void) {
	
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
