﻿/**
 * File:   file_browser_view.c
 * Author: AWTK Develop Team
 * Brief:  文件管理/浏览/选择控件
 *
 * Copyright (c) 2020 - 2020 Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2020-01-08 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/utils.h"
#include "file_browser_view.h"

ret_t file_browser_view_set_init_dir(widget_t* widget, const char* init_dir) {
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);
  return_value_if_fail(file_browser_view != NULL, RET_BAD_PARAMS);

  file_browser_view->init_dir = tk_str_copy(file_browser_view->init_dir, init_dir);
  file_browser_set_cwd(file_browser_view->fb, init_dir);

  return RET_OK;
}

ret_t file_browser_view_set_file_icon(widget_t* widget, const char* file_icon) {
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);
  return_value_if_fail(file_browser_view != NULL, RET_BAD_PARAMS);

  file_browser_view->file_icon = tk_str_copy(file_browser_view->file_icon, file_icon);

  return RET_OK;
}

ret_t file_browser_view_set_folder_icon(widget_t* widget, const char* folder_icon) {
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);
  return_value_if_fail(file_browser_view != NULL, RET_BAD_PARAMS);

  file_browser_view->folder_icon = tk_str_copy(file_browser_view->folder_icon, folder_icon);

  return RET_OK;
}

ret_t file_browser_view_set_return_up_icon(widget_t* widget, const char* return_up_icon) {
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);
  return_value_if_fail(file_browser_view != NULL, RET_BAD_PARAMS);

  file_browser_view->return_up_icon =
      tk_str_copy(file_browser_view->return_up_icon, return_up_icon);

  return RET_OK;
}

static ret_t file_browser_view_get_prop(widget_t* widget, const char* name, value_t* v) {
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);
  return_value_if_fail(file_browser_view != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

  if (tk_str_eq(FILE_BROWSER_VIEW_PROP_INIT_DIR, name)) {
    value_set_str(v, file_browser_view->init_dir);
    return RET_OK;
  } else if (tk_str_eq(FILE_BROWSER_VIEW_PROP_FILE_ICON, name)) {
    value_set_str(v, file_browser_view->file_icon);
    return RET_OK;
  } else if (tk_str_eq(FILE_BROWSER_VIEW_PROP_FOLDER_ICON, name)) {
    value_set_str(v, file_browser_view->folder_icon);
    return RET_OK;
  } else if (tk_str_eq(FILE_BROWSER_VIEW_PROP_RETURN_UP_ICON, name)) {
    value_set_str(v, file_browser_view->return_up_icon);
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static ret_t file_browser_view_set_prop(widget_t* widget, const char* name, const value_t* v) {
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);
  return_value_if_fail(widget != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

  if (tk_str_eq(FILE_BROWSER_VIEW_PROP_INIT_DIR, name)) {
    file_browser_view_set_init_dir(widget, value_str(v));
    return RET_OK;
  } else if (tk_str_eq(FILE_BROWSER_VIEW_PROP_FILE_ICON, name)) {
    file_browser_view_set_file_icon(widget, value_str(v));
    return RET_OK;
  } else if (tk_str_eq(FILE_BROWSER_VIEW_PROP_FOLDER_ICON, name)) {
    file_browser_view_set_folder_icon(widget, value_str(v));
    return RET_OK;
  } else if (tk_str_eq(FILE_BROWSER_VIEW_PROP_RETURN_UP_ICON, name)) {
    file_browser_view_set_return_up_icon(widget, value_str(v));
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static ret_t file_browser_view_on_destroy(widget_t* widget) {
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);
  return_value_if_fail(widget != NULL && file_browser_view != NULL, RET_BAD_PARAMS);

  file_browser_destroy(file_browser_view->fb);

  return RET_OK;
}

static ret_t file_browser_view_on_paint_self(widget_t* widget, canvas_t* c) {
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);

  (void)file_browser_view;

  return RET_OK;
}

static ret_t file_browser_view_reload(widget_t* widget) {
  widget_t* container = NULL;
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);
  container = file_browser_view->container;

  return RET_OK;
}

static ret_t file_browser_view_init_ui(widget_t* widget) {
  widget_t* template = NULL;
  widget_t* container = NULL;
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);

  container = widget_lookup(widget, FILE_BROWSER_VIEW_CONTAINER, TRUE);
  return_value_if_fail(container != NULL, RET_BAD_PARAMS);

  template = widget_lookup(container, FILE_BROWSER_VIEW_FILE_TEMPLATE, TRUE);
  return_value_if_fail(template != NULL, RET_BAD_PARAMS);
  file_browser_view->file_template = template;
  widget_remove_child(template->parent, template);

  template = widget_lookup(container, FILE_BROWSER_VIEW_FOLDER_TEMPLATE, TRUE);
  return_value_if_fail(template != NULL, RET_BAD_PARAMS);
  file_browser_view->folder_template = template;
  widget_remove_child(template->parent, template);

  template = widget_lookup(container, FILE_BROWSER_VIEW_RETURN_UP_TEMPLATE, TRUE);
  return_value_if_fail(template != NULL, RET_BAD_PARAMS);
  file_browser_view->return_up_template = template;
  widget_remove_child(template->parent, template);

  return file_browser_view_reload(widget);
}

static ret_t file_browser_view_on_event(widget_t* widget, event_t* e) {
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);
  return_value_if_fail(widget != NULL && file_browser_view != NULL, RET_BAD_PARAMS);

  switch (e->type) {
    case EVT_WINDOW_LOAD: {
      file_browser_view_init_ui(widget);
      break;
    }
  }

  return RET_OK;
}

const char* s_file_browser_view_properties[] = {
    FILE_BROWSER_VIEW_PROP_INIT_DIR, FILE_BROWSER_VIEW_PROP_FILE_ICON,
    FILE_BROWSER_VIEW_PROP_FOLDER_ICON, FILE_BROWSER_VIEW_PROP_RETURN_UP_ICON, NULL};

TK_DECL_VTABLE(file_browser_view) = {.size = sizeof(file_browser_view_t),
                                     .type = WIDGET_TYPE_FILE_BROWSER_VIEW,
                                     .clone_properties = s_file_browser_view_properties,
                                     .persistent_properties = s_file_browser_view_properties,
                                     .parent = TK_PARENT_VTABLE(widget),
                                     .create = file_browser_view_create,
                                     .on_paint_self = file_browser_view_on_paint_self,
                                     .set_prop = file_browser_view_set_prop,
                                     .get_prop = file_browser_view_get_prop,
                                     .on_event = file_browser_view_on_event,
                                     .on_destroy = file_browser_view_on_destroy};

widget_t* file_browser_view_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h) {
  widget_t* widget = widget_create(parent, TK_REF_VTABLE(file_browser_view), x, y, w, h);
  file_browser_view_t* file_browser_view = FILE_BROWSER_VIEW(widget);
  return_value_if_fail(file_browser_view != NULL, NULL);

  file_browser_view->fb = file_browser_create(os_fs());

  return widget;
}

widget_t* file_browser_view_cast(widget_t* widget) {
  return_value_if_fail(WIDGET_IS_INSTANCE_OF(widget, file_browser_view), NULL);

  return widget;
}

#include "base/widget_factory.h"

ret_t file_browser_view_register(void) {
  return widget_factory_register(widget_factory(), WIDGET_TYPE_FILE_BROWSER_VIEW,
                                 file_browser_view_create);
}
