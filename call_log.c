#include "lvgl/lvgl.h"
#include <stdlib.h>

lv_obj_t * currentButton = NULL;
extern lv_obj_t *tab2;

typedef struct {
    char *name;           // Contact name
    char *time;           // Time of call
} CallLogEntry;

typedef struct CallLogNode {
    CallLogEntry data;             // Data of the node
    struct CallLogNode *next;      // Pointer to the next node
} CallLogNode;

CallLogNode *callLogHead = NULL;



void addToCallLog(const char *name, /*const char *number,*/ const char *time) {
    CallLogNode *newNode = (CallLogNode *)malloc(sizeof(CallLogNode));
    if (newNode == NULL) {
        // Handle memory allocation failure
        return;
    }
    newNode->data.name = strdup(name);
    // newNode->data.number = strdup(number);
    newNode->data.time = strdup(time);
    newNode->next = callLogHead;  // Set the next pointer of the new node to the current head
    callLogHead = newNode;        // Update the head to point to the new node
}


void freeCallLog() {
    CallLogNode *current = callLogHead;
    CallLogNode *next;
    while (current != NULL) {
        next = current->next;
        free(current->data.name);
        // free(current->data.number);
        free(current->data.time);
        free(current);
        current = next;
    }
    callLogHead = NULL;  // Reset the head pointer
}

extern void event_handler(lv_event_t * e);
extern void event_handler_up(lv_event_t * e);
extern void event_handler_dn(lv_event_t * e);
static void float_clear_cb(lv_event_t * e);

void call_log(lv_obj_t *parent)
{
	lv_obj_t *base = lv_obj_create(parent);
	lv_obj_set_size(base, 798, 405);
	lv_obj_align(base, LV_ALIGN_TOP_MID, 0, -25);
	lv_obj_clear_flag(base, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t * menu = lv_menu_create(base);
    lv_obj_set_size(menu, 798, 405);
    lv_obj_center(menu);
    lv_obj_clear_flag(menu, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t * cont;
    lv_obj_t * label;

    lv_obj_t * main_page = lv_menu_page_create(menu, NULL);

    
    CallLogNode *currentNode = callLogHead;

    while (currentNode != NULL)
    {
        cont = lv_menu_cont_create(main_page);
        lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_BOTTOM,0);

        label = lv_label_create(cont);
    	lv_label_set_text(label, currentNode->data.name);

    	lv_obj_t *label2 = lv_label_create(cont);
		lv_label_set_text(label2, currentNode->data.time);
		lv_obj_align(label2, LV_ALIGN_CENTER,0,0);


        if (callLogHead != NULL && currentNode == callLogHead)
        {
            currentButton = cont;
    	    lv_obj_add_state(currentButton, LV_STATE_CHECKED);
        }  
    currentNode = currentNode->next;
    }
    
	lv_menu_set_page(menu, main_page);
    
    lv_obj_t * base2 = lv_obj_create(base);
    lv_obj_set_size(base2, 50, 50 );
    lv_obj_align(base2, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_border_color(base2, lv_color_white(),0);
    lv_obj_clear_flag(base2, LV_OBJ_FLAG_SCROLLABLE);

    // lv_obj_t* btn = lv_list_add_btn(list2, LV_SYMBOL_UP, "Up");
    lv_obj_t* btn = lv_btn_create(base2);
    lv_obj_t* label2 = lv_label_create(btn);
    lv_label_set_text(label2, LV_SYMBOL_UP);
    lv_obj_set_size(btn, 50,50);
    lv_obj_align(btn, LV_ALIGN_CENTER,0,0);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0,0);

    lv_obj_add_event_cb(btn, event_handler_up, LV_EVENT_ALL, NULL);

    lv_group_remove_obj(btn);


	 lv_obj_t * base3 = lv_obj_create(base);
    lv_obj_set_size(base3, 50, 50 );
    lv_obj_align(base3, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_set_style_border_color(base3, lv_color_white(),0);
    lv_obj_clear_flag(base3, LV_OBJ_FLAG_SCROLLABLE);

    // lv_obj_t* btn = lv_list_add_btn(list2, LV_SYMBOL_UP, "Up");
    btn = lv_btn_create(base3);
    label2 = lv_label_create(btn);
    lv_label_set_text(label2, LV_SYMBOL_DOWN);
    lv_obj_set_size(btn, 50,50);
    lv_obj_align(btn, LV_ALIGN_CENTER,0,0);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0,0);

    lv_obj_add_event_cb(btn, event_handler_dn, LV_EVENT_ALL, NULL);
    lv_group_remove_obj(btn);

    /*Create floating btn*/
    lv_obj_t* float_btn2 = lv_btn_create(base);
    lv_obj_set_size(float_btn2, 50, 50);
    lv_obj_add_flag(float_btn2, LV_OBJ_FLAG_FLOATING);
    lv_obj_align(float_btn2, LV_ALIGN_BOTTOM_RIGHT, -50, -12);
    lv_obj_add_event_cb(float_btn2, float_clear_cb, LV_EVENT_CLICKED, menu);
    lv_obj_set_style_radius(float_btn2, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(float_btn2, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_bg_img_src(float_btn2, LV_SYMBOL_TRASH, 0);
    lv_obj_set_style_text_font(float_btn2, lv_theme_get_font_large(float_btn2), 0);
	
}
