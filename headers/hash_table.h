#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "list.h"

#define LIST_DUMP_PNG "source/dump/list_dump.png"
#define LIST_DUMP_TXT "source/dump/list_dump.txt"

enum hash_func_num_t
{
    RETURN_ZERO     = 0,
    FIRST_LETTER    = 1,
    STRLEN          = 2,
    ASCII_SUM       = 3,
    ROL             = 4
};

struct text_data
{
    char** array_of_pointers;
    size_t number_of_words;
};

struct hash_table_t
{
    list_t* lists_array;
    ULL (*hash_func)(const char*);
    ULL capacity;
};

hash_table_t create_hash_table(text_data text, ULL (*hash_func)(const char*), ULL table_capacity);
void destroy_hash_table(hash_table_t* hash_table);
bool hash_table_verify(hash_table_t* const hash_table);
void hash_table_dump(hash_table_t* const hash_table, const char* const txt_file_name, const char* const png_file_name);
void hash_table_to_file(hash_table_t hash_table, FILE* output_file);

void fill_lists_array(text_data text, hash_table_t* hash_table);
void push_to_hash_table(ULL index, const char* word, ULL word_num, hash_table_t* hash_table);
ULL seek_word(const char* word, hash_table_t hash_table);

ULL return_zero_hash_func(const char* word);
ULL first_letter_hash_func(const char* word);
ULL strlen_hash_func(const char* word);
ULL ascii_sum_hash_func(const char* word);
ULL rol_hash_func(const char* word);

#include "list.h"

#endif // HASH_TABLE_H
