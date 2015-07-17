#include <pebble.h>
#include "timer.h"

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

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_timer(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_timer(void) {
  window_stack_remove(s_window, true);
}
