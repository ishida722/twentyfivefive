#include <pebble.h>
#include "work.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static TextLayer *modeName;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorClear);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // modeName
  modeName = text_layer_create(GRect(20, 20, 107, 35));
  text_layer_set_background_color(modeName, GColorClear);
  text_layer_set_text(modeName, "WORK");
  text_layer_set_text_alignment(modeName, GTextAlignmentCenter);
  text_layer_set_font(modeName, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)modeName);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(modeName);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_work(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_work(void) {
  window_stack_remove(s_window, true);
}
