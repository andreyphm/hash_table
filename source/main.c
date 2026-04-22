#include <stdlib.h>

#include "hash_table.h"
#include "input_proc.h"
#include "font.h"

#define VISUALIZATION_MODE 0
#define SEARCH_BENCHMARK_MODE 1

#ifndef PROGRAM_MODE
#define PROGRAM_MODE VISUALIZATION_MODE
#endif

const ULL SEARCH_REPEATS = 10000000;

int main(const int argc, const char* const argv[])
{
    ULL (*hash_func_array[])(const char*) = {return_zero_hash_func,
                                             first_letter_hash_func,
                                             strlen_hash_func,
                                             ascii_sum_hash_func,
                                             rol_hash_func,
                                             crc32_hash_func};
    FILE* input_file  = nullptr;
    FILE* output_file = nullptr;
    hash_func_num_t hash_func_num = CRC32;
    ULL hash_table_capacity = 4001;

    check_cmd(&input_file, &output_file, &hash_func_num, &hash_table_capacity, argc, argv);

    ULL (*hash_func)(const char*) = hash_func_array[hash_func_num];

    char* buffer = read_file_to_buffer(input_file);
    fclose(input_file);

    text_data text =
    {
        .array_of_pointers = nullptr,
        .number_of_words = 0
    };

    text.array_of_pointers = words_addresses_to_array(buffer, &text.number_of_words);

    hash_table_t hash_table = create_hash_table(text, hash_func, hash_table_capacity);

    if (PROGRAM_MODE == SEARCH_BENCHMARK_MODE)
    {
        ULL search_result = 0;

        for (size_t i = 0; i < SEARCH_REPEATS; i++)
            search_result += seek_word("apperceptionistic", hash_table);

        printf("search_result = %llu\n", search_result);
    }
    else
        hash_table_to_file(hash_table, output_file);

    free(buffer);
    free(text.array_of_pointers);
    destroy_hash_table(&hash_table);

    printf(MAKE_BOLD("COMMIT GITHUB\n"));
}
