#include <pebble.h>
#include "timer.h"
#include "common.h"

MODE mode;
time_t leftTime;


static void init(void) {
	mode = start;
	show_timer();
}

static void deinit(void) {
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
