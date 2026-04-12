#ifndef LIST_H
#define LIST_H

#include <stdio.h>

struct node_t
{
    const char* word;
    node_t* next;
};
    
struct list_t
{
    node_t* head;
    node_t* current;
    node_t* tail;
};

node_t* create_node (int value, list_t* const list);
node_t* list_push_back(int value, list_t* const list);
node_t* list_push_forward(int value, list_t* const list);
void list_dump(list_t* const list, const char* const txt_file_name, const char* const png_file_name);

#endif //LIST_H
