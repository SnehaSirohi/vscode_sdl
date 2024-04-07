#include "lvgl/lvgl.h"
#include <stdlib.h>
#include <stdio.h>
#include "contacts_view.h"
#include "call_log_model.h"

extern void event_handler(lv_event_t *e);
extern void event_handler_up(lv_event_t *e);
extern void event_handler_dn(lv_event_t *e);
void float_clear_cb(lv_event_t *e);

lv_obj_t *call_log_menu;

extern lv_obj_t *currentButton;

void dialer_screen(lv_obj_t *parent, CallLogNode *dat)
{
    static lv_style_t dialer_style;

    lv_style_init(&dialer_style);
    lv_style_set_shadow_width(&dialer_style, 40);
	lv_style_set_shadow_color(&dialer_style, lv_color_mix(lv_palette_main(LV_PALETTE_GREY), lv_color_white(), LV_OPA_40));
	lv_style_set_shadow_opa(&dialer_style, LV_OPA_50);
	lv_style_set_shadow_ofs_x(&dialer_style, 10);

	lv_obj_t *profile_cont = lv_obj_create(parent);
	lv_obj_set_size(profile_cont, 700, 480);
	lv_obj_set_style_border_color(profile_cont, lv_color_white(), LV_PART_MAIN);
	
    lv_obj_t* container = lv_obj_create(profile_cont);
	lv_obj_set_size(container, 350, 275);
	lv_obj_align(container, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_bg_color(container, lv_color_mix(lv_palette_main(LV_PALETTE_GREY), lv_color_white(), LV_OPA_10), NULL);

    lv_obj_t *name_label = lv_label_create(container);
	lv_label_set_text(name_label, "Calling...");
	lv_obj_align(name_label, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_t *contact_label = lv_label_create(container);

    lv_label_set_text_fmt(contact_label, "%s", dat->data.name);
	lv_obj_align(contact_label, LV_ALIGN_TOP_MID, 0, 50);


    lv_obj_t *call_btn = lv_btn_create(container);
    lv_obj_t *call_label = lv_label_create(call_btn);
    lv_label_set_text(call_label, LV_SYMBOL_CLOSE);
    lv_obj_align(call_btn, LV_ALIGN_BOTTOM_MID, 0, 0);











}


// int dialer_screen(lv_obj_t* parent, CallLogNode *dat)
// {
//     static const char* btns[] = {LV_SYMBOL_CLOSE, LV_SYMBOL_MUTE, LV_SYMBOL_VOLUME_MAX, ""};

//     // lv_obj_t * mbox1 = lv_obj_create(parent);
//     lv_obj_t* mbox1 = lv_msgbox_create(parent, dat->data.name, dat->data.time, NULL, false);
    
//     lv_obj_set_size(mbox1, 800, 250);
//     lv_obj_align(mbox1, LV_ALIGN_CENTER, 0, 0);

//     lv_obj_t* label_txt = lv_msgbox_get_text(mbox1);
//     // lv_obj_set_align(label_txt, LV_ALIGN_CENTER);
	
// 	// lv_obj_set_style_text_align(mbox1, LV_ALIGN_BOTTOM_MID,0);

//     // lv_obj_t* btn = lv_msgbox_get_btns(mbox1);
//     // lv_obj_set_style_pad_bottom(btn, 100, NULL);


//     // lv_msgbox_add_title(mbox1, "Hello");

//     // lv_msgbox_add_text(mbox1, "This is a message box with two buttons.");
//     // lv_msgbox_add_close_button(mbox1);

//     return;
// }

void createCallogLabels(lv_obj_t *parent)
{
    // CallLogNode *currentNode = callLogHead;
    printf("inside create call log Labels\r\n");
    // printContactList();
    // bubbleSort();

    CallLogNode *current = callLogHead;
    // if(call_log_count>0)
    // printf("CALL LOG HEAD: %d\n", current->data.name);
    int index = 0;
    lv_obj_t *cont;
    lv_obj_t *label;
    lv_obj_t *sub_page;

    while (current != NULL)
    {

        // printf("Creating sub pages\n");

        sub_page = lv_menu_page_create(call_log_menu, current->data.name);
        // printf("Sub page created\n");
        cont = lv_menu_cont_create(sub_page);
        lv_obj_set_size(cont, 744, 310);
        dialer_screen(cont, current);

        printf("Profile successfully created\n");
        cont = lv_menu_cont_create(parent);

        printf("Cont page for label create\n");
        // Create an LVGL label for each contact name
        lv_obj_t *label = lv_label_create(cont);
        printf("Data that is to be displayed: %d\n", current->data.name);
        lv_label_set_text(label, current->data.name);
        lv_obj_set_user_data(label, current);
        lv_menu_set_load_page_event(parent, cont, sub_page);

        lv_obj_add_event_cb(cont, event_handler, LV_EVENT_CLICKED, NULL);

        current = current->next;
        if (index == 0)
        {
            current = cont;
            lv_obj_add_state(current, LV_STATE_CHECKED);
        }
    }
    printf("outside createContactLabels\r\n");
}

void call_log(lv_obj_t *parent)
{

    int call_log_count = get_callLog_count();
    printf("No. of call logs:%d\n", call_log_count);
    static lv_style_t style2;
    lv_obj_t *main_page;
    lv_style_init(&style2);
    lv_style_set_border_color(&style2, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_border_width(&style2, 2);
    lv_style_set_border_opa(&style2, LV_OPA_40);
    lv_style_set_border_side(&style2, LV_BORDER_SIDE_FULL);
    lv_obj_t *base = lv_obj_create(parent);
    lv_obj_set_size(base, 798, 405);
    lv_obj_align(base, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_clear_flag(base, LV_OBJ_FLAG_SCROLLABLE);
    int inx = 0;
    call_log_menu = lv_menu_create(base);
    lv_obj_set_size(call_log_menu, 798, 405);
    lv_obj_center(call_log_menu);
    lv_obj_clear_flag(call_log_menu, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *cont;
    lv_obj_t *label;

    lv_obj_t *sub_page[call_log_count];

    // lv_obj_t *back_btn = lv_menu_get_main_header_back_btn(call_log_menu);
    // lv_obj_t *back_button_label = lv_label_create(back_btn);
    // lv_obj_align(back_button_label, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_add_style(back_btn, &style2, 0);

    // lv_label_set_text(back_button_label, "Back");
    
    CallLogNode *currentNode = callLogHead;
    main_page = lv_menu_page_create(call_log_menu, NULL);

    

    // if(call_log_count>0)
    // createCallogLabels(main_page);

    // while(currentNode != NULL && index<= call_log_count)
    // {
    //     sub_page[index] = lv_menu_page_create(call_log_menu, currentNode->data.name);
    //     cont = lv_menu_cont_create(sub_page[index]);
    //     lv_obj_set_size(cont, 744, 310);
    //     create_contact_profile(cont, currentNode);

    //     cont = lv_menu_cont_create(parent);
    //     lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_BOTTOM,0);

    //     label = lv_label_create(cont);
    // 	lv_label_set_text(label, currentNode->data.name);

    // 	lv_obj_t *label2 = lv_label_create(cont);
    // 	lv_label_set_text(label2, currentNode->data.time);
    // 	lv_obj_align(label2, LV_ALIGN_CENTER,0,0);

    //     lv_menu_set_load_page_event(call_log_menu, cont, sub_page[index]);

    //     // lv_obj_add_event_cb(cont, event_handler2, LV_EVENT_CLICKED, NULL);

    //     currentNode = currentNode->next;
    //     if (callLogHead != NULL && currentNode == callLogHead)
    //     {
    //         currentButton = cont;
    //         lv_obj_add_state(currentButton, LV_STATE_CHECKED);
    //     }
    //     index++;

    // currentNode = currentNode->next;
    // }

    while (currentNode != NULL && inx<=call_log_count)
    {

        sub_page[inx] = lv_menu_page_create(call_log_menu, currentNode->data.name);
        cont = lv_menu_cont_create(sub_page[inx]);
        lv_obj_set_size(cont, 744, 310);
        dialer_screen(cont, currentNode);

        printf("Profile successfully created\n");

        cont = lv_menu_cont_create(parent);
        // Create an LVGL label for each contact name
        // lv_obj_t *label = lv_label_create(cont);
        // lv_label_set_text(label, currentNode->data.name);
        // lv_obj_set_user_data(label, currentNode);
        

        cont = lv_menu_cont_create(main_page);
        lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_BOTTOM, 0);

        label = lv_label_create(cont);
        lv_label_set_text(label, currentNode->data.name);
        // printf("CALL LOG INFO:%d\n", currentNode->data.name);

        lv_obj_t *label2 = lv_label_create(cont);
        lv_label_set_text(label2, currentNode->data.time);
        lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);
        lv_menu_set_load_page_event(call_log_menu, cont, sub_page[inx]);

        if (callLogHead != NULL && currentNode == callLogHead)
        {
            currentButton = cont;
            lv_obj_add_state(currentButton, LV_STATE_CHECKED);
        }

        inx++;
        currentNode = currentNode->next;
    }

    lv_menu_set_page(call_log_menu, main_page);

    lv_obj_t *base2 = lv_obj_create(base);
    lv_obj_set_size(base2, 50, 50);
    lv_obj_align(base2, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_border_color(base2, lv_color_white(), 0);
    lv_obj_clear_flag(base2, LV_OBJ_FLAG_SCROLLABLE);

    // lv_obj_t* btn = lv_list_add_btn(list2, LV_SYMBOL_UP, "Up");
    lv_obj_t *btn = lv_btn_create(base2);
    lv_obj_t *label2 = lv_label_create(btn);
    lv_label_set_text(label2, LV_SYMBOL_UP);
    lv_obj_set_size(btn, 50, 50);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_event_cb(btn, event_handler_up, LV_EVENT_ALL, NULL);

    lv_group_remove_obj(btn);

    lv_obj_t *base3 = lv_obj_create(base);
    lv_obj_set_size(base3, 50, 50);
    lv_obj_align(base3, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_set_style_border_color(base3, lv_color_white(), 0);
    lv_obj_clear_flag(base3, LV_OBJ_FLAG_SCROLLABLE);

    // lv_obj_t* btn = lv_list_add_btn(list2, LV_SYMBOL_UP, "Up");
    btn = lv_btn_create(base3);
    label2 = lv_label_create(btn);
    lv_label_set_text(label2, LV_SYMBOL_DOWN);
    lv_obj_set_size(btn, 50, 50);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_event_cb(btn, event_handler_dn, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);

    /*Create floating btn*/
    lv_obj_t *float_btn2 = lv_btn_create(base);
    lv_obj_set_size(float_btn2, 50, 50);
    lv_obj_add_flag(float_btn2, LV_OBJ_FLAG_FLOATING);
    lv_obj_align(float_btn2, LV_ALIGN_BOTTOM_RIGHT, -50, -12);
    lv_obj_add_event_cb(float_btn2, float_clear_cb, LV_EVENT_CLICKED, call_log_menu);
    lv_obj_set_style_radius(float_btn2, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(float_btn2, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_bg_img_src(float_btn2, LV_SYMBOL_TRASH, 0);
    lv_obj_set_style_text_font(float_btn2, lv_theme_get_font_large(float_btn2), 0);
}
