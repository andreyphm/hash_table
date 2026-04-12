#include "hash_table.h"

const int NUMBER_OF_LISTS = 4001;

int main()
{
    hash_table_t hash_table = 
    {
        .number_of_lists = NUMBER_OF_LISTS,
        .lists_array = nullptr,
        .hash_func_pointer = nullptr
    };
    
}
