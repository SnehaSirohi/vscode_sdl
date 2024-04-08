#include "lvgl/lvgl.h"

extern lv_obj_t *tab2;

typedef struct {
    char *name;           // Contact name
    char *time;           // Time of call
} CallLogEntry;

typedef struct CallLogNode {
    CallLogEntry data;             // Data of the node
    struct CallLogNode *next;      // Pointer to the next node
} CallLogNode;

extern CallLogNode *callLogHead; 

void addToCallLog(const char *name, /*const char *number,*/ const char *time) ;

void freeCallLog() ;
int get_callLog_count();