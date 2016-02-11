#include <pebble.h>
#include "PomoTimer.h"

static time_t s_wakeup_timestamp = 0;
static uint8_t coutdownText;

static void timer_start(uint8_t time)
{

}

static void timer_handler(void *data)
{
	if (s_wakeup_timestamp == 0) {
		// get the wakeup timestamp for showing a countdown
		/* wakeup_query(s_wakeup_id, &s_wakeup_timestamp); */
	}
	int countdown = s_wakeup_timestamp - time(NULL);
	/* snprintf(s_countdown_text, sizeof(s_countdown_text), "%d seconds", countdown); */
	/* layer_mark_dirty(text_layer_get_layer(s_countdown_text_layer)); */
	app_timer_register(1000, timer_handler, data);
}
