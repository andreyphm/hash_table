#include "hash_table.h"
#include "input_proc.h"
#include "font.h"

int main(const int argc, const char* const argv[])
{
    FILE* input_file = nullptr;
    FILE* output_file = nullptr;
    check_files(&input_file, &output_file, argc, argv);

    unsigned long long first_table_capacity = 4001;

    hash_table_t hash_table = create_hash_table(input_file, return_zero_hash_func, first_table_capacity);

    destroy_hash_table(&hash_table);

    printf(MAKE_BOLD("COMMIT GITHUB\n"));
}
