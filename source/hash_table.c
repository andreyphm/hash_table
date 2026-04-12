#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "hash_table.h"
#include "font.h"

hash_table_t* create_hash_table(list_t* lists_array, unsigned long long capacity,
                                unsigned long long (*hash_func_ptr)(const list_t*))
{
    assert(lists_array);
    assert(hash_func_ptr);

    hash_table_t* hash_table = (hash_table_t*) calloc(1, sizeof(hash_table_t*));
    hash_table->capacity = capacity;
    hash_table->lists_array = lists_array;
    hash_table->hash_func_pointer = hash_func_ptr;

    return hash_table;
}

void destroy_hash_table(hash_table_t* hash_table)
{
    if (!hash_table) return;
    if (!hash_table->lists_array) 
    {
        free(hash_table);
        return;
    }
    free(hash_table->lists_array);
    free(hash_table);
}

void hash_table_dump(hash_table_t* const hash_table, const char* const txt_file_name, const char* const png_file_name)
{
    assert(hash_table);

    for (size_t i = 0; list_verify(hash_table->lists_array[i]) && i != hash_table->capacity; i++)
    {
        list_dump(hash_table->lists_array);
    }

    printf(MAKE_BOLD_GREEN("Hash table visualization saved to %s\n"), LIST_DUMP_PNG);
}

unsigned long long return_0_hash_func(void)
{
    return 0;
}

unsigned long long first_letter_hash_func(const char* word)
{
    return *word;
}

unsigned long long strlen_hash_func(const char* word)
{
    return strlen(word);
}
