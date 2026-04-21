#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "hash_table.h"
#include "input_proc.h"
#include "list.h"
#include "font.h"

hash_table_t create_hash_table(text_data text, ULL (*hash_func)(const char*), ULL table_capacity)
{
    assert(hash_func);

    hash_table_t hash_table = {};
    hash_table.hash_func = hash_func;
    hash_table.capacity = table_capacity;
    hash_table.lists_array = (list_t*) calloc(table_capacity, sizeof(list_t));
    fill_lists_array(text, &hash_table);

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

    for (size_t i = 0; i < hash_table->capacity; i++)
        list_destroy(&hash_table->lists_array[i]);
    
    free(hash_table->lists_array);
}

void hash_table_dump(hash_table_t* const hash_table, const char* const txt_file_name, const char* const png_file_name)
{
    for (size_t i = 0; list_verify(&hash_table->lists_array[i]) && i < hash_table->capacity; i++)
        list_dump(hash_table->lists_array, txt_file_name, png_file_name);

    printf(MAKE_BOLD_GREEN("Hash table visualization saved to %s\n"), png_file_name);
}

bool hash_table_verify(hash_table_t* const hash_table)
{
    if (!hash_table) return false;
    if (!hash_table->lists_array) return true;

    for (size_t i = 0; i < hash_table->capacity; i++)
        if (!list_verify(&hash_table->lists_array[i])) return false;

    return true;
}

void fill_lists_array(text_data text, hash_table_t* hash_table)
{
    for (size_t word_num = 0; word_num < text.number_of_words; word_num++)
    {
        ULL hash_value = hash_table->hash_func(text.array_of_pointers[word_num]);
        push_to_hash_table(hash_value, text.array_of_pointers[word_num], word_num, hash_table);
    }
}

void push_to_hash_table(ULL list_index, const char* word, ULL word_num, hash_table_t* hash_table)
{
    list_index %= hash_table->capacity;

    if (hash_table->lists_array[list_index].head)
    {
        list_push_back(word, word_num, &hash_table->lists_array[list_index]);
        return;
    }
    
    hash_table->lists_array[list_index] = create_list(word, word_num);
}

void hash_table_to_file(hash_table_t hash_table, FILE* output_file)
{
    fprintf(output_file, "%llu\n", hash_table.capacity);
    for (size_t i = 0; i < hash_table.capacity; i++)
    {
        if (hash_table.lists_array[i].head)
        {
            fprintf(output_file, "%lu ", i);
            while (hash_table.lists_array[i].current)
            {
                fprintf(output_file, "%s ", hash_table.lists_array[i].current->word);
                hash_table.lists_array[i].current = hash_table.lists_array[i].current->next;
            }
            fprintf(output_file, "\n");
        }
    }
}

ULL seek_word(const char* word, hash_table_t hash_table)
{
    ULL list_index = hash_table.hash_func(word) % hash_table.capacity;

    node_t* current = hash_table.lists_array[list_index].head;

    while(current)
    {
        if (!strcmp(word, current->word))
            return current->word_num;

        current = current->next;
    }

    return hash_table.capacity;
}

ULL return_zero_hash_func(const char* word)
{
    (void) word;
    return 0;
}

ULL first_letter_hash_func(const char* word)
{
    return (ULL)*word;
}

ULL strlen_hash_func(const char* word)
{
    return strlen(word);
}

ULL ascii_sum_hash_func(const char* word)
{
    ULL sum = 0;
    while (*word != '\0')
    { 
        sum += (ULL)*word;
        word++;
    }
    return sum;
}

ULL rol_hash_func(const char* word)
{
    ULL value = 0;
    while (*word != '\0')
    {
        value = (value << 1) | (value >> (sizeof(ULL) * 8 - 1));
        value = value ^ (ULL)*word;
        word++;
    }
    return value;
}
