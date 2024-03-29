#ifndef CONTACTS_HANDLERS_H
#define CONTACTS_HANDLERS_H

#include "lvgl/lvgl.h"

extern lv_obj_t * currentbtn;
extern lv_obj_t * main_page;
extern lv_obj_t * base;
extern lv_obj_t *name_ta;
extern lv_obj_t *number_ta;
extern lv_obj_t *email_ta;
extern lv_obj_t * base4;


// Event Callback Function Declarations
void confirm_btn_event_handler(lv_event_t *e);
void screen_click_cb(lv_event_t *e);
void phone_ta_event_cb(lv_event_t *e);
void ta_event_cb(lv_event_t *e);
void float_button_event_cb(lv_event_t *e);
void event_handler2(lv_event_t *e);
void event_handler_up2(lv_event_t *e);
void event_handler_dn2(lv_event_t *e);

#endif /* CONTACTS_HANDLERS_H */
