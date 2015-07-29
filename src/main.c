#include <pebble.h>
#include "timer.h"

static void init(void) {
    check_persist();
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
