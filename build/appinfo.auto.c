#include "pebble_app_info.h"
#include "src/resource_ids.auto.h"

const PebbleAppInfo __pbl_app_info __attribute__ ((section (".pbl_header"))) = {
  .header = "PBLAPP",
  .struct_version = { APP_INFO_CURRENT_STRUCT_VERSION_MAJOR, APP_INFO_CURRENT_STRUCT_VERSION_MINOR },
  .sdk_version = { APP_INFO_CURRENT_SDK_VERSION_MAJOR, APP_INFO_CURRENT_SDK_VERSION_MINOR },
  .app_version = { 1, 0 },
  .load_size = 0xb6b6,
  .offset = 0xb6b6b6b6,
  .crc = 0xb6b6b6b6,
  .name = "RCOS_accel",
  .company = "PebbleFit",
  .icon_resource_id = DEFAULT_MENU_ICON,
  .sym_table_addr = 0xA7A7A7A7,
  .flags = 0,
  .num_reloc_entries = 0xdeadcafe,
  .uuid = { 0x18, 0xD2, 0xEF, 0x2B, 0x26, 0x9D, 0x4A, 0xE0, 0xBD, 0x0F, 0x1D, 0xBF, 0xC0, 0xE1, 0x79, 0x58 },
  .virtual_size = 0xb6b6
};
