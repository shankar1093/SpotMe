#include <pebble.h>


#define ACCEL_STEP_MS 100



static Window *window;
static TextLayer *text_layer;
//static TextLayer *accel_layer;

static bool send_message = true;
static const uint32_t SOME_STRING_KEY = 0xb00bf00b;


static AppTimer *timer;
enum {
  x_axis = 0,
  y_axis = 1,
  z_axis = 2
};
// const uint8_t key_count = 2;
// const uint32_t size = dict_calc_buffer_size(key_count, sizeof(data),strlen(string) + 1);
// uint8_t buffer[size];
// static const uint32_t SOME_STRING_KEY = 0xabbababe;
// static const char *string = "Hello World";




//This function is only sending zeroes. I think the problem might be the initialization of AccelData
// static void process_accel(AccelData data){
//   data = (AccelData) { .x = 0, .y = 0, .z = 0 };

//   Tuplet value1 = TupletInteger(x_axis, data.x);
//   Tuplet value2 = TupletInteger(y_axis, data.y);
//   Tuplet value3 = TupletInteger(z_axis, data.z);
//   // app_log(APP_LOG_LEVEL_DEBUG,"RCOS_accel.c",14,"X:%d Y:%d Z:%d",data.x,data.y,data.z);
  

//   DictionaryIterator *iter;
//   app_message_outbox_begin(&iter);
//   if(iter == NULL){
//     return;
//   }

//   //  text_layer_set_text(text_layer, "Up");
//   dict_write_tuplet(iter, &value1);
//   dict_write_tuplet(iter, &value2);
//   dict_write_tuplet(iter, &value3);
//   app_message_outbox_send();


// }

static void send_to_js(int x, int y, int z)
{
  
  Tuplet value_x = TupletInteger(x_axis, x);
  Tuplet value_y = TupletInteger(y_axis, y);
  Tuplet value_z = TupletInteger(z_axis, z);
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

   if(iter == NULL){
     return;
   }
    // Tuplet value3 = TupletInteger(3, (int)z);

  //  text_layer_set_text(text_layer, "Up");
 dict_write_tuplet(iter, &value_x);
 dict_write_tuplet(iter, &value_y);
 dict_write_tuplet(iter, &value_z);
 dict_write_end(iter);
//   // dict_write_tuplet(iter, &value3);
 app_message_outbox_send();
}


static void js_array_length(void){
  // Tuplet value1 = TupletCString(x_axis, "select");

  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  if(iter == NULL){
    return;
  }

  dict_write_cstring(iter, x_axis, "select");
  dict_write_end(iter);

  app_message_outbox_send();
}

void accel_data_handler(AccelData *data, uint32_t num_samples) {
  unsigned int i;
  app_log(APP_LOG_LEVEL_DEBUG,"RCOS_accel.c",14,"accel-data-handler: working");
  for(i=0;i<num_samples;i++)
  {
    // app_log(APP_LOG_LEVEL_DEBUG,"RCOS_accel.c",14,"X:%d Y:%d Z:%d",data[i].x,data[i].y,data[i].z);
    send_to_js(data[i].x, data[i].y, data[i].z);
  }

  return;
}

static void timer_callback(void *data) {
  //AccelData accel = (AccelData) { .x = 0, .y = 0, .z = 0 };
  AccelData accel;
  if(send_message){
    send_message = false;
  }

  accel_service_peek(&accel);
  app_log(APP_LOG_LEVEL_DEBUG,"RCOS_accel.c",14,"TIMER CALLBACK");
  // process_accel(accel);
  timer = app_timer_register(ACCEL_STEP_MS, timer_callback, NULL);

}


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  AccelData accel = (AccelData) { .x = 0, .y = 0, .z = 0 };
  text_layer_set_text(text_layer, "RCOS_ACCEL");
  js_array_length();
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


static void in_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Dropped!");
}

static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Failed to Send!");
}


static void in_received_handler(DictionaryIterator *iter, void *context) {
//   Tuple *value1 = dict_find(iter, 1);
    Tuple *value2 = dict_find(iter, 0x2);
//   Tuple *value3 = dict_find(iter, 3);

}

static void app_message_init(void) {
  // Register message handlers
  app_message_register_inbox_received(in_received_handler);
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_register_outbox_failed(out_failed_handler);
  // Init buffers
  //app_message_open(64, 64);
 // send_to_js();
   app_message_open(64, 64);
   // send_to_js();
}



static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
 

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  app_message_init();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);

  // timer = app_timer_register(ACCEL_STEP_MS, timer_callback, NULL);
  accel_data_service_subscribe(10, &accel_data_handler);

}

static void deinit(void) {
  window_destroy(window);
  accel_data_service_unsubscribe();
}


int main(void) {
  init();


  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);
  
  app_event_loop();
  deinit();
}
