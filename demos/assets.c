#include "awtk.h"
#include "base/assets_manager.h"

#include "assets_default.inc"
#include "assets_dark.inc"

#ifndef APP_THEME
#define APP_THEME "default"
#endif /*APP_THEME*/

ret_t assets_init_internal(const char* theme) {
  assets_manager_t* am = assets_manager();
  return_value_if_fail(theme != NULL && am != NULL, RET_BAD_PARAMS);

  assets_manager_set_theme(am, theme);

  if (tk_str_eq(theme, "default")) {
    return assets_init_default();
  } else if (tk_str_eq(theme, "dark")) {
    return assets_init_dark();
  } else {
    log_debug("%s not support.\n", theme);
    return RET_NOT_IMPL;
  }
}

ret_t assets_init(void) {
  return assets_init_internal(APP_THEME);
}

ret_t widget_set_theme_without_file_system(widget_t* widget, const char* name) {
#ifndef WITH_FS_RES
  const asset_info_t* info = NULL;
  event_t e = event_init(EVT_THEME_CHANGED, NULL);
  widget_t* wm = widget_get_window_manager(widget);
  font_manager_t* fm = widget_get_font_manager(widget);
  image_manager_t* imm = widget_get_image_manager(widget);
  assets_manager_t* am = widget_get_assets_manager(widget);
  locale_info_t* locale_info = widget_get_locale_info(widget);

  font_manager_unload_all(fm);
  image_manager_unload_all(imm);
  assets_manager_clear_all(am);
  widget_reset_canvas(widget);

  assets_init_internal(name);
  locale_info_reload(locale_info);

  info = assets_manager_ref(am, ASSET_TYPE_STYLE, "default");
  theme_init(theme(), info->data);
  assets_manager_unref(assets_manager(), info);

  widget_dispatch(wm, &e);
  widget_invalidate_force(wm, NULL);

  log_debug("theme changed: %s\n", name);

  return RET_OK;
#else
  return RET_NOT_IMPL;
#endif /*WITH_FS_RES*/
}
