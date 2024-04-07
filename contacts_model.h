#ifndef CONTACTS_MODEL_H
#define CONTACTS_MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a contact
typedef struct {
    char *name;
    char *number;
    char *email;
} Contact;

// Structure for a linked list node
typedef struct ListNode {
    Contact data;
    struct ListNode *next;
} ListNode;

extern ListNode *contactList;
extern int count;

void addContact(const char *name, const char *number, const char *email);
void freeContactList(const char *names);

#endif // CONTACTS_MODEL_H
