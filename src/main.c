#include <pebble.h>
#include "timer.h"
#include "common.h"

MODE mode;
time_t leftTime;

static timeStamp;

static void timer_handler(void *data) {
	leftTime = timestamp - time(NULL);
	snprintf(s_countdown_text, sizeof(s_countdown_text), "%d", countdown/60+1);
	text_layer_set_text(text_time, s_countdown_text);

	if(countdown<1){
		vibes_double_pulse();
		show_rest();
		hide_working();
	}else{
	// 1000ms後にまたこの関数を実行
	app_timer_register(1000, timer_handler, data);
	}
}

static void init(void) {
	app_timer_register(0, timer_handler, NULL);
	mode = start;
	leftTime = 25*60;
	show_timer();
}

static void deinit(void) {
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
