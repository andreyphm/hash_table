#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef unsigned long long ULL;

struct node_t
{
    const char* word;
    ULL word_num;
    node_t* next;
};
    
struct list_t
{
    node_t* head;
    node_t* current;
    node_t* tail;
};

list_t create_list(const char* word, ULL word_num);
node_t* create_node(const char* word, ULL word_num);
void list_push_back(const char* word, ULL word_num, list_t* const list);
void list_destroy(list_t* list);
bool list_verify(list_t* const list);
void list_dump(list_t* const list, const char* const txt_file_name, const char* const png_file_name);

#endif //LIST_H
