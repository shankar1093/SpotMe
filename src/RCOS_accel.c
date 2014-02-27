#include <pebble.h>


#define ACCEL_STEP_MS 100



static Window *window;
static TextLayer *text_layer;
static TextLayer *accel_layer;

static bool send_message = true;
static const uint32_t SOME_DATA_KEY = 0xb00bf00b;


static AppTimer *timer;


static void process_accel(AccelData data){
  // app_log(APP_LOG_LEVEL_DEBUG,"RCOS_accel.c",14,"X:%d Y:%d X:%d",data.x,data.y,data.z);
  // DictionaryIterator *iter;

  // app_message_outbox_begin(&iter);

  //   Tuplet value1 = TupletInteger(1, data.x);
  //   Tuplet value2 = TupletInteger(2, data.y);
  //   Tuplet value3 = TupletInteger(3, data.z);

  // //  text_layer_set_text(text_layer, "Up");
  // dict_write_tuplet(iter, &value1);
  // dict_write_tuplet(iter, &value2);
  // dict_write_tuplet(iter, &value3);
  // app_message_outbox_send();


}

static void send_to_js(unsigned int x,unsigned int y,unsigned int z)
{
  DictionaryIterator *iter;

  app_message_outbox_begin(&iter);

    Tuplet value1 = TupletInteger(1, (int)x);
    Tuplet value2 = TupletInteger(2, (int)y);
    Tuplet value3 = TupletInteger(3, (int)z);

  //  text_layer_set_text(text_layer, "Up");
  dict_write_tuplet(iter, &value1);
  dict_write_tuplet(iter, &value2);
  dict_write_tuplet(iter, &value3);
  app_message_outbox_send();

}

void accel_data_handler(AccelData *data, uint32_t num_samples) {
  unsigned int i;
  // app_log(APP_LOG_LEVEL_DEBUG,"RCOS_accel.c",14,"accel-data-handler: herp");
  for(i=0;i<num_samples;i++)
  {
    app_log(APP_LOG_LEVEL_DEBUG,"RCOS_accel.c",14,"X:%d Y:%d Z:%d",data[i].x,data[i].y,data[i].z);
  }
  return;
}

static void timer_callback(void *data) {
  AccelData accel = (AccelData) { .x = 0, .y = 0, .z = 0 };

  if(send_message){
    send_message = false;
  }

  accel_service_peek(&accel);
  // app_log(APP_LOG_LEVEL_DEBUG,"RCOS_accel.c",14,"TIMER CALLBACK");
  process_accel(accel);
  timer = app_timer_register(ACCEL_STEP_MS, timer_callback, NULL);
}


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "RCOS_ACCEL");
  app_log(APP_LOG_LEVEL_DEBUG,"RCOS_accel.c",47,"SELECT");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "RCOS_ACCEL");
  app_log(APP_LOG_LEVEL_DEBUG,"RCOS_accel.c",47,"UP");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "RCOS_ACCEL");
  app_log(APP_LOG_LEVEL_DEBUG,"RCOS_accel.c",47,"DOWN");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void in_received_handler(DictionaryIterator *iter, void *context) {
  Tuple *value1 = dict_find(iter, 1);
  Tuple *value2 = dict_find(iter, 2);
  Tuple *value3 = dict_find(iter, 3);

  // if (value1 || value2 ||value3) {
  //   strncpy(&value1, value1->value->cstring, 5);
  //   strncpy(&value2, value2->value->cstring, 5);
  //   strncpy(&value3, value3->value->cstring, 5);
  //   //text_layer_set_text(accel_layer, symbol);
  // }
}


static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  AccelData accel = (AccelData) { .x = 0, .y = 0, .z = 0 };

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);

  timer = app_timer_register(ACCEL_STEP_MS, timer_callback, NULL);
  accel_data_service_subscribe(10, &accel_data_handler);
}

static void deinit(void) {
  window_destroy(window);
  accel_data_service_unsubscribe();
}

// static void process_pebble_accel(AccelData Data){
//   APP_LOG(APP_LOG_LEVEL_DEBUG, data.x %d, window);
//   APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);
//   APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

// }
int main(void) {
  init();


  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);
  
  app_event_loop();
  deinit();
}
