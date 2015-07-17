#include <pebble.h>
#include "timer.h"
#include "common.h"

static void init(void) {
	show_timer();
}

static void deinit(void) {
	hide_timer();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
