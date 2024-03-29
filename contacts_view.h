// contacts_view.h
#ifndef CONTACTS_VIEW_H
#define CONTACTS_VIEW_H

#include "lvgl/lvgl.h"
#include "contacts_model.h"

void contacts(lv_obj_t* parent);
void add_contact_ui(lv_obj_t *parent);
void createContactLabels(lv_obj_t *parent);
int create_contact_profile(lv_obj_t *parent, char *name[]);
lv_obj_t* create_phone_keypad(lv_obj_t* parent); 

#endif // CONTACTS_VIEW_H
