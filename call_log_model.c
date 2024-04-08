#include "lvgl/lvgl.h"
#include <stdlib.h>
#include <stdio.h>
#include "call_log_model.h"

lv_obj_t *currentButton = NULL;

static int count_calllog = 0;

// typedef struct
// {
//     char *name; // Contact name
//     char *time; // Time of call
// } CallLogEntry;

// typedef struct CallLogNode
// {
//     CallLogEntry data;        // Data of the node
//     struct CallLogNode *next; // Pointer to the next node
// } CallLogNode;

CallLogNode *callLogHead = NULL;

void addToCallLog(const char *name, const char *time)
{

    // if(count_calllog==0)
    // {

    // }
    CallLogNode *newNode = (CallLogNode *)malloc(sizeof(CallLogNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        // Handle memory allocation failure
        return;
    }
    newNode->data.name = strdup(name);
    // newNode->data.number = strdup(number);
    newNode->data.time = strdup(time);

    newNode->next = NULL;
    // newNode->next = callLogHead;  // Set the next pointer of the new node to the current head
    // callLogHead = newNode;

    // no_of_contacts(newNode, name);

    CallLogNode *curr = callLogHead;

    if (callLogHead == NULL || strcmp(name, callLogHead->data.name) < 0)
    {
        printf("List is empty\n");

        newNode->next = callLogHead;
        callLogHead = newNode;
        count_calllog++;
        // printf("Number of call logs :%d \n", count_calllog);
        return;
    }

    while (curr->next != NULL && (strcmp(name, curr->next->data.name) > 0))
    {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    count_calllog++;

    printf("Number of call logs :%d \n", count_calllog);
}

void freeCallLog()
{
    CallLogNode *current = callLogHead;
    CallLogNode *next;
    while (current != NULL)
    {
        next = current->next;
        free(current->data.name);
        // free(current->data.number);
        free(current->data.time);
        free(current);
        current = next;
    }
    callLogHead = NULL; // Reset the head pointer
}

void no_of_contacts(CallLogNode *newNode, const char *name)
{
    CallLogNode *curr = callLogHead;

    if (callLogHead == NULL || strcmp(name, callLogHead->data.name) < 0)
    {
        printf("List is empty\n");

        newNode->next = callLogHead;
        callLogHead = newNode;
        count_calllog++;
        return;
    }

    while (curr->next != NULL && (strcmp(name, curr->next->data.name) > 0))
    {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    count_calllog++;
    return;
}


CallLogNode* get_head()
{
    return callLogHead;
}

int get_callLog_count()
{
    return count_calllog;
}