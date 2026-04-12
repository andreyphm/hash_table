#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define LIST_DUMP_PNG "source/dump/list_dump.txt"

unsigned long long first_hash_func(void);
unsigned long long second_hash_func(const char*);
unsigned long long third_hash_func(const char*);

#include "list.h"

struct hash_table_t
{
    unsigned long long capacity;
    list_t* lists_array;
    unsigned long long (*hash_func_pointer)(const list_t*);
};

#endif // HASH_TABLE_H
