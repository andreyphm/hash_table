#include <stdlib.h>

#include "hash_table.h"
#include "input_proc.h"
#include "font.h"

int main(const int argc, const char* const argv[])
{
    FILE* input_file = nullptr;
    FILE* output_file = nullptr;
    check_files(&input_file, &output_file, argc, argv);

    char* buffer = read_file_to_buffer(input_file);
    fclose(input_file);

    text_data text =
    {
        .array_of_pointers = nullptr,
        .number_of_words = 0
    };

    text.array_of_pointers = words_addresses_to_array(buffer, &text.number_of_words);

    ULL first_table_capacity = 503;
    hash_table_t hash_table = create_hash_table(text, ascii_sum_hash_func, first_table_capacity);

    hash_table_to_file(hash_table, output_file);

    free(buffer);
    free(text.array_of_pointers);
    destroy_hash_table(&hash_table);

    printf(MAKE_BOLD("COMMIT GITHUB\n"));
}
